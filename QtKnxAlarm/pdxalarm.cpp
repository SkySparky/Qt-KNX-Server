#include "pdxalarm.h"

int counter = 0;

PdxAlarm::PdxAlarm(QString &iniFile, GidtModule *mod) : m_mod(mod), m_inifile(iniFile)
{

    LoadIni(m_inifile);
    //copy all data
    m_cmdTimer = new QTimer(this);
    connect(m_cmdTimer, SIGNAL(timeout()), this, SLOT(CmdTimer()));
    m_cmdTimer->start(1000);
}

//PdxAlarm::~PdxAlarm() {}


void PdxAlarm::AlrmInput(QByteArray data)
{
	m_buffer.append(data);
	int index = m_buffer.indexOf('\r');

	//qDebug() << "[Alarm::Input] data: " << data;

	if (index > 0) {
		QString cmd = m_buffer.mid(0, index).constData();
		m_buffer = m_buffer.mid(index+1, m_buffer.length()-(index+1));
		
		if (cmd.contains("COMM&")) {	//response
			qDebug() << "[PdxAlarm::AlrmInput] resp: " << cmd;
		}
		else {
			QString cmdToSend = GetCommandToSend(cmd);
			if (!cmdToSend.isEmpty()) SendCommand(cmdToSend);
		}

		qDebug() << "[Alarm::Input] cmd: " << cmd; // << ", buffer: " << m_buffer;
	}
}

void PdxAlarm::SendCommand(QString cmd)
{
	QString buffer =  "WRITE,ALARM," + m_destination + "," + cmd;
	m_mod->Write(buffer);

	qDebug() << "[PdxAlarm::SendCommand] : " << buffer; 
}


int PdxAlarm::GetCommandToSendByIndex(QString &cmd, tp_cmd &tmpCmd, int index)
{
	int retVal = -1;
	int otherindex = 1;

	if (index == 1) otherindex = 0;

	if (tmpCmd.alarmCmd[index].contains(cmd)) {	//cmd 0 found
		qDebug() << "Found: " << cmd << ", with index: " << QString::number(index);
		if (tmpCmd.sendAlways == 1) {		//send always?
			retVal = index;						//send 0
			qDebug() << "Always sent";
		}
		else {								//don't send always
			if (tmpCmd.lastsent == index) {		//was the last sent?
				qDebug() << "I was last, don't resend";
				if (tmpCmd.cancelOther > 0) {
					tmpCmd.sent[otherindex] = true;		//cancel other
					tmpCmd.cntr[otherindex] = 0;			//and reset it's counter
				}
			}
			else {
				qDebug() << "Send because I was not the last";
				retVal = index;
			}
		}
		if (retVal >= 0) {				//is flagged to be sent?
			tmpCmd.sent[index] = true;
			if (tmpCmd.delay[index] > 0) {	//is delayed?
				qDebug() << "It's delayed";
				tmpCmd.cntr[index] = 0;		//reset counter
				tmpCmd.sent[index] = false;
			}
			if (tmpCmd.cancelOther > 0) {	//cancel each other?
				qDebug() << "Cancels the other";
				tmpCmd.sent[otherindex] = true;		//cancel other
				tmpCmd.cntr[otherindex] = 0;			//and reset it's counter
			}
		}
	}
	return(retVal);
}


QString PdxAlarm::GetCommandToSend(QString cmd)
{
	QString retCmd;
	
	tp_cmd tmpCmd;
	for (int i=0; i<m_cmd.length(); i++ ) {			//search all commands
	
		if (GetCommandToSendByIndex(cmd, m_cmd[i], 0) >= 0) {
			if (m_cmd[i].sent[0] == true ) {
				retCmd = m_cmd[i].groupAddr + ",00";
				m_cmd[i].lastsent = 0;
			}
			break;
		}
		else if (GetCommandToSendByIndex(cmd,m_cmd[i], 1) > 0) {
			if (m_cmd[i].sent[1] == true)  {
				retCmd = m_cmd[i].groupAddr + ",01";
				m_cmd[i].lastsent = 1;
			}
			break;
		}
	}
	return(retCmd);
}

//Data input from module
void PdxAlarm::Input(QString data)
{
    QString dest = Common::GetParam(data, Common::PARAM_DEST);
    QString cmd = Common::GetParam(data, Common::PARAM_CMD);
	if (cmd == "CMD") {
		if (dest == "ALARM") {
            if (Common::GetParam(data, Common::PARAM_DATA_START) == "RELOAD") {	//reload conf
				LoadIni(m_inifile);
			}
		}
	}
	else if (cmd == "WRITE") {
		if (dest == "ALARM") {
            QString sendStr = Common::GetParam(data, Common::PARAM_DATA_START);
			sendStr.append(QChar('\r'));	//alarm protocol needs it
			emit Output(sendStr, 0, 0);
		}
	}


}


void PdxAlarm::CheckDelay(int index, int boolIndex)
{
	if ((m_cmd.at(index).delay[boolIndex] > 0) && (m_cmd.at(index).sent[boolIndex] == false) ) {
		if ( (m_cmd[index].cntr[boolIndex]++) >= m_cmd[index].delay[boolIndex]) {
			m_cmd[index].cntr[boolIndex] = 0;
			m_cmd[index].sent[boolIndex] = true;
			m_cmd[index].lastsent = 0;
			SendCommand(m_cmd[index].groupAddr + ",0" + QString::number(boolIndex));
		}
	}
}

void PdxAlarm::CmdTimer(void)
{
	for (int i=0; i<m_cmd.length(); i++ ) {
		CheckDelay(i, 0);
		CheckDelay(i, 1);
	}
}

//Format:	16\cmd=G000N008A001,10/1/8,0,30
//			index\cmd=[ALARM CMD],[GROUPADDR],[VALUE],[DELAY]
void PdxAlarm::LoadIni(QString iniFile)
{
	QSettings settings(iniFile, QSettings::IniFormat);
	QString tmpStr = settings.value("GroupAddresses/destination").toString();
	if (!tmpStr.isEmpty()) m_destination = tmpStr;

	QStringList list = LoadAlarmValues(iniFile);
    if (list.size() > 0) {
        int tmpInt;
        bool ok;
        for (int i = 0; i < list.size(); ++i) {

            QString cmd = list[i];
            tp_cmd tmpCommand;
            tmpStr = Common::GetParam(cmd, 1);	//get group address
            if (!tmpStr.isEmpty()) {
                tmpCommand.groupAddr = tmpStr;
            }
            else
                continue;

            tmpStr = Common::GetParam(cmd, 2);	//get command for 0
            if (!tmpStr.isEmpty()) {
                tmpCommand.alarmCmd[0] = tmpStr;
            }
            else
                continue;

            tmpStr = Common::GetParam(cmd, 3);	//get command for 1
            if (!tmpStr.isEmpty()) {
                tmpCommand.alarmCmd[1] = tmpStr;
            }
            else
                continue;

            tmpInt = Common::GetParam(cmd, 4).toInt(&ok);	//send always or on changes
            if (ok)
                tmpCommand.sendAlways = tmpInt;
            else
                continue;

            tmpInt = Common::GetParam(cmd, 5).toInt(&ok);	//get delay for 0
            if (ok)
                tmpCommand.delay[0] = tmpInt;
            else
                tmpCommand.delay[0] = 0;

            tmpInt = Common::GetParam(cmd, 6).toInt(&ok);	//get delay for 0
            if (ok)
                tmpCommand.delay[1] = tmpInt;
            else
                tmpCommand.delay[1] = 0;


            tmpInt = Common::GetParam(cmd, 7).toInt(&ok);	//get delay for 0
            if (ok)
                tmpCommand.cancelOther = tmpInt;
            else
                tmpCommand.cancelOther = 0;

            tmpCommand.cntr[0] = tmpCommand.cntr[1] = 0;
            tmpCommand.sent[0] = tmpCommand.sent[1] = true;
            tmpCommand.lastsent = -1;	//noone is sent

            m_cmd << tmpCommand;
        }
        qDebug() << "commands found: " << QString::number(m_cmd.length());
    }
}

void PdxAlarm::AddLog(QString msg)
{
	m_mod->Log("[PdxAlarm::" + msg);
}


QStringList PdxAlarm::LoadAlarmValues(QString iniFile)
{
	QStringList retList;
	QFile file(iniFile);
	//Check file is not already opened
	if (!file.isOpen()) {
		if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
			AddLog("LoadAlarmValues] Could not open file: " + iniFile);
			qDebug() << "[GidtModule::run] Could not open file: " << iniFile;
			file.close();
			//exit(-1);
		}
		else {
			bool startOk = false;
			QTextStream stream(&file);
			stream.setCodec("ISO 8859-7");
			QString line = stream.readLine();
			while (!line.isNull()) {
				line = stream.readLine();
				if (startOk) retList << line;
				if (line == "[GroupAddresses]") {
					startOk = true;
				}
			};
			//delete file
			file.close();
		}
	}
	else
		file.close();

	return(retList);
}
