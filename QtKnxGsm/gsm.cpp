/*
 * gsm.cpp
 *
 *  Created on: 29 Ïêô 2010
 *      Author: Administrator
 */
#include "gsm.h"

#define PARAM_CMD		1
#define PARAM_SENDER	2
#define PARAM_DEST		3
#define PARAM_DATA_START	4

#define GSM_RCV_DEFAULT_TIMEOUT	100

Gsm::Gsm(GidtModule * mod, QString ComPort, QStringList smsTel)
{
	m_comport = ComPort;
	m_rcvTimeout = GSM_RCV_DEFAULT_TIMEOUT;
	m_smsList.clear();
	m_module = mod;

	//Get valid users
	m_validTel = smsTel;
	//qDebug() << m_validTel;

	//QString test = "07910396539900F0240C9103966099117700000111809174158004E8329BFD4697D9EC37";
	//test = "hellohello";
	//qDebug() << "EncodeTo7bit: " << EncodeTo7bit(test);

	/*
	sms_t msg;
	msg.smsText = "SET LIGHT (%50)";
	QString tmpVal = msg.smsText.mid(msg.smsText.indexOf("(%")+2, msg.smsText.length() - msg.smsText.indexOf(")")+1);
	qDebug() << "tmpVal:" << tmpVal;
	*/

	m_state.state = STATE_UNREGISTERED;
	//m_state.state = STATE_IDLE;
}

Gsm::~Gsm()
{
	//Do nothing
}

void Gsm::Start(void)
{
	QT_TRY {
		m_port = new AbstractSerial();
		m_port->setDeviceName(m_comport);
		if (m_port->open(AbstractSerial::ReadWrite) ) {
			qDebug() << "[Gsm::Start] Port opened.";
			m_port->setBaudRate(AbstractSerial::BaudRate115200);
			m_port->setDataBits(AbstractSerial::DataBits8);
			m_port->setParity(AbstractSerial::ParityNone);
			m_port->setStopBits(AbstractSerial::StopBits1);
			m_port->setFlowControl(AbstractSerial::FlowControlHardware);
		}
		else {
			qDebug() << "[Gsm::Start] Port failed to open! Exiting...";
			abort();
		}

		m_timer = new QTimer(this);
		connect(m_timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
		m_timer->start(1000);	//10secs
	}
	QT_CATCH (...) {
		exit(0);
	}
	start();

}

void Gsm::OnTimer()
{
	//qDebug() << "[Gsm::OnTimer]";
	if (m_state.state != STATE_IDLE) {
		if (m_watchdog.elapsed() > 20000) {
			m_state.state = STATE_UNREGISTERED;
			qDebug() << "[Gsm::OnTimer] reseting...";
		}
	}
}


QString Gsm::GetParam(QString inString, int param, QString separator)
{
	QString strResult;
	strResult.clear();

	QT_TRY {
		QStringList params = inString.split(separator);
		//QString retString = params.at(param+1);
		if (params.isEmpty() == false) {
			//qDebug() << "inString: " << inString;
			if (param <= params.length())
				strResult = params.at(param-1);
		}
	}
	QT_CATCH(...) {
		m_module->Log("Gsm::GetParam error with: " + inString);
	}
	return(strResult);
}

void Gsm::Input(QString data)
{
	if ( (GetParam(data,PARAM_CMD)=="EVENT") && (GetParam(data,PARAM_DEST)=="SMS") ) {
		QString smsTel = GetParam(data,PARAM_DATA_START);
		QString smsText = GetParam(data,PARAM_DATA_START+1);

		qDebug() << "smsTel: " << smsTel << ", smsText: " << smsText;

		SendSMS(smsTel,smsText);
	}
}

void Gsm::run()
{
	QByteArray rcvData; //received data
	//qint64 dataLen = 0; //bytes received


	QT_TRY {
		while(1) {
			//Check responses
			SmsSendHandler();

			if ( m_port->waitForReadyRead(m_rcvTimeout) ) {
				rcvData.clear();
				rcvData = m_port->readAll(); //(100);
				qDebug() << "[Gsm::run] Data(" << rcvData.size() << "): " << rcvData.data();
				m_rcvBuffer.append(rcvData);
				if (m_rcvBuffer.contains("+CMTI: \"SM\"")) {
					//QString currStr =

					int startPos = m_rcvBuffer.indexOf("+CMTI: \"SM\",");
					QString currStr = m_rcvBuffer.mid(startPos, m_rcvBuffer.length() - startPos);
					int endPos = currStr.indexOf("\r");
					qDebug() << "New message arrived = [" << currStr.mid(12, endPos-1).toInt() << "]";
					m_inbox.push_back(currStr.mid(12, endPos).toInt());
				}
			}
		}
	}
	QT_CATCH (...) {
		qDebug() << "[Gsm::run] Error.";
		exit(0);
	}
}

int Gsm::SendSMS(QString smsTel, QString smsText)
{
	sms_t tmpSms;
	QString pduText;
	int seperationLen = 0;	//160 for 7bit, 70 for unicode

	if (smsTel.length() == 0) {
		if (m_smsTel.length() != 0) {
			tmpSms.smsTel = m_smsTel;
		}
		else {
			qDebug() << "[Gsm::SendSMS] Error: no sms tel is given.";
			return(-1);
		}
	}
	else {
		tmpSms.smsTel = smsTel;	//get telephone
	}

	tmpSms.smsType = SMS_TYPE_7BIT;
	for (int i=0; i<smsText.length(); i++) {
		if (smsText.at(i) > 127) {
			tmpSms.smsType = SMS_TYPE_UNICODE;
			//qDebug() << "[Gsm::SendSMS] found unicode character at pos(" << QString::number(i) << "): " << smsText.at(i);
		}
	}

	if (tmpSms.smsType == SMS_TYPE_UNICODE) {
		seperationLen = 70;
	}
	else {
		seperationLen = 160;
	}

	if (smsText.length() > seperationLen) {
		int numOfChars = seperationLen;
		int startIndex = 0;
		int charsLeft = smsText.length();
		QString tmpStr;
		while (charsLeft) {
			tmpStr = smsText.mid(startIndex, numOfChars);
			if (tmpSms.smsType == SMS_TYPE_UNICODE)
				tmpSms.smsText = EncodeToUnicode(tmpStr);
			else
				tmpSms.smsText = EncodeTo7bit(tmpStr);
			//tmpSms.smsText = pduText.mid(startIndex, numOfChars - 1);
			startIndex += numOfChars;
			charsLeft -= numOfChars;
			if (charsLeft > seperationLen) numOfChars = seperationLen;
			else numOfChars = charsLeft;
			//qDebug() << "[Gsm::SendSMS]: sms len= " << tmpStr.length();
			tmpSms.smsLength = tmpStr.length();
			m_smsList.push_back(tmpSms);		//add to list
		}
	}
	else {
		tmpSms.smsLength = smsText.length();
		if (tmpSms.smsType == SMS_TYPE_UNICODE)
			tmpSms.smsText = EncodeToUnicode(smsText);
		else
			tmpSms.smsText = EncodeTo7bit(smsText);
		m_smsList.push_back(tmpSms);		//add to list
	}

	return( m_smsList.length());
}

void Gsm::SmsSendHandler(void)
{
	QByteArray tmpData; //received data
	//qint64 dataLen = 0; //bytes received

	//_currentState = _state.state;
	if (m_state.state == STATE_UNREGISTERED) {
		m_rcvBuffer.clear();
		if (m_port->write("AT+CFUN=1\r\n")) {
			qDebug() << "[Gsm::SmsSendHandler]: Starting...";
			m_state.state = STATE_WAIT_REGISTRATION;
			m_watchdog.start();
		}
		else
			qDebug() << "[Gsm::SmsSendHandler]: failed in STATE_UNREGISTERED";
	}
	else if (m_state.state == STATE_WAIT_REGISTRATION) {
		if (m_rcvBuffer.contains("+WIND: 4")) {
			m_rcvBuffer.clear();
			qDebug() << "[Gsm::SmsSendHandler]: Started";
			if (m_port->write("ATE0\r\n")) {
				m_previousState = m_state.state;
				m_state.state = STATE_WAIT_ATE0;
				m_watchdog.start();
			}
		}
	}
	else if (m_state.state == STATE_WAIT_ATE0) {
		if (m_rcvBuffer.contains("OK")) {
			m_rcvBuffer.clear();
			qDebug() << "[Gsm::SmsSendHandler]: Echo canceled.";
			if (m_port->write("AT+CMGF=0\r\n")) {
				m_previousState = m_state.state;
				m_state.state = STATE_WAIT_CMGF;
				m_watchdog.start();
			}
		}
	} //STATE_WAIT_CMGF
	else if (m_state.state == STATE_WAIT_CMGF) {
		if (m_rcvBuffer.contains("OK")) {
			m_rcvBuffer.clear();
			qDebug() << "[Gsm::SmsSendHandler]: Enabled PDU sms format.";
			if (m_port->write("AT+CMGD=1,4\r\n")) {
				m_previousState = m_state.state;
				m_state.state = STATE_WAIT_DELETE_ALL_SMS;
				m_watchdog.start();
			}
		}
	}
	else if (m_state.state == STATE_WAIT_DELETE_ALL_SMS) {
		if (m_rcvBuffer.contains("OK")) {
			qDebug() << "[Gsm::SmsSendHandler]: Deleted SMS. Going IDLE...";
			m_rcvBuffer.clear();
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			m_watchdog.start();
		}
		else if (m_rcvBuffer.contains("ERROR")) {
			qDebug() << "[Gsm::SmsSendHandler]: No SMS to delete.";
			m_rcvBuffer.clear();
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			m_watchdog.start();
		}
	}
	else if (m_state.state == STATE_IDLE) {
		if (m_inbox.isEmpty() == false) {
			m_previousState = m_state.state;
			m_state.state = STATE_READ_SMS;
			m_watchdog.start();
		}
		else if (m_smsList.isEmpty() == false) {
			m_previousState = m_state.state;
			m_state.state = STATE_SEND_SMS_FROM_LIST;
			m_watchdog.start();
		}
	}
	else if (m_state.state == STATE_SEND_SMS_FROM_LIST) {
		m_currSms = m_smsList.first();
		tmpData.clear();
		//tmpData.append("AT+CMGS=\"" + _currSms.smsTel + "\"\r");
		m_currPDU = EncodeToPDU(m_currSms);
		tmpData.append("AT+CMGS=\"" + QString::number((m_currPDU.length()-2)/2) + "\"\r");
		m_rcvBuffer.clear();
		if (m_port->write(tmpData)) {
			m_previousState = m_state.state;
			qDebug() << "[Gsm::SmsSendHandler]: Preparing (" + QString::number(m_currPDU.length()/2-1) + "," + m_currSms.smsTel + "," + m_currSms.smsText + ")." ;
			m_state.state = STATE_WAIT_SMS_INPUT;
			m_watchdog.start();
		}
		else {
			m_rcvBuffer.clear();
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			m_watchdog.start();
			qDebug() << "[Gsm::SmsSendHandler]: failed to send SMS";
		}
	}
	else if (m_state.state == STATE_WAIT_SMS_INPUT) {
		if (m_rcvBuffer.contains(">")) {
			tmpData.clear();
			//tmpData.append(_currSms.smsText);
			m_currPDU.append(char(26));
			//tmpData.append(char(26));
			tmpData.append(m_currPDU);
			m_rcvBuffer.clear();
			if (m_port->write(tmpData)) {
				qDebug() << "[Gsm::SmsSendHandler]: Sending SMS..." << m_currPDU;
				m_previousState = m_state.state;
				m_state.state = STATE_SENDING_SMS;
				m_watchdog.start();
			}
		}
		else if (m_rcvBuffer.contains("ERROR")) {
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			m_smsList.pop_front();
			qDebug() << "[Gsm::SmsSendHandler]: ERROR sending SMS...";
			m_rcvBuffer.clear();
			m_watchdog.start();
		}
	}
	else if (m_state.state == STATE_SENDING_SMS) {
		if (m_rcvBuffer.contains("+CMGS:")) {
			qDebug() << "[Gsm::SmsSendHandler]: SMS send succesfully...";
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			m_smsList.pop_front();
			m_rcvBuffer.clear();
			m_watchdog.start();
		}
		else if (m_rcvBuffer.contains("ERROR")) {
			m_previousState = m_state.state;
			m_state.state = STATE_IDLE;
			qDebug() << "[Gsm::SmsSendHandler]: ERROR sending SMS...";
			m_rcvBuffer.clear();
			m_watchdog.start();
		}
	}
	else if (m_state.state == STATE_READ_SMS) {
		m_rcvBuffer.clear();
		tmpData.clear();
		m_readSmsIndex = m_inbox.first();
		tmpData.append("AT+CMGR=");
		tmpData.append(QString::number(m_readSmsIndex));
		tmpData.append("\r\n");
		if (m_port->write(tmpData)) {
			qDebug() << "[Gsm::SmsSendHandler]: Reading SMS...";
			m_previousState = m_state.state;
			m_state.state = STATE_WAIT_READ_RESP;
			m_watchdog.start();
		}
	}
	else if (m_state.state == STATE_WAIT_READ_RESP) {
		//if (m_rcvBuffer.contains("+CMGR: \"REC UNREAD\"")) {
		if (m_rcvBuffer.contains("+CMGR: ")) {
			int startPos = m_rcvBuffer.indexOf("+CMGR:");
			QString tmpStr = m_rcvBuffer.mid(startPos, m_rcvBuffer.length() - startPos);
			startPos = tmpStr.indexOf("\n") + 1;
			int endPos = tmpStr.indexOf("\r\n\r\nOK");
			QString pduContex = tmpStr.mid(startPos, endPos-startPos);
			sms_t msg = DecodePDU(pduContex);

			QString tmpVal;
			bool hasVal = false;

			if (m_validTel.contains(msg.smsTel)) {

				QString sendMsg = "EVENT,GSM,DB," + msg.smsTel + "," + msg.smsText;
				m_module->Write(sendMsg);

				qDebug() << "[Gsm::SmsSendHandler]: " + sendMsg;
				//qDebug() << "[Gsm::SmsSendHandler]: incoming text=" + tmpStr.mid(startPos, endPos-startPos);
			}
			else {
				qDebug() << "[Gsm::SmsSendHandler]: invalid tel number: " << msg.smsTel << "," << msg.smsText;
			}
		}
		else {
			qDebug() << "[Gsm::SmsSendHandler]: already read that message?";
		}
		m_rcvBuffer.clear();
		m_inbox.pop_front();
		m_previousState = m_state.state;
		m_state.state = STATE_IDLE;
		m_watchdog.start();
	}
}


QString Gsm::SwapBytes(QString &bytes)
{
	QString result = "";
	for (int i=0; i<bytes.length(); i+=2) {
		result.append( bytes.mid(i+1,1));
		result.append( bytes.mid(i,1));
	}

	return(result);
}

QString Gsm::EncodeToPDU(sms_t &sms) //, QString &pdu)
{
	QString pdu;
	QString tmpStr;
	QString tmpStr2 = "00";
	tmpStr.setNum(sms.smsTel.length()+2, 16);
	tmpStr2.append(tmpStr);
	pdu = "001100";
	pdu.append(tmpStr2.right(2).toUpper());
	pdu.append("9103");
	pdu.append(SwapBytes(sms.smsTel));
	if (sms.smsType == SMS_TYPE_7BIT)
		pdu.append("0000AA");
	else
		pdu.append("0008AA");

	tmpStr2 = "00";
	tmpStr.clear();
	//qDebug() << "[Gsm::EncodeToPDU]: sms len= " << sms.smsLength;
	if (sms.smsType == SMS_TYPE_7BIT)
		tmpStr.setNum(sms.smsLength, 16);	//tmpStr.setNum(sms.smsText.length()/2, 16);
	else
		tmpStr.setNum(sms.smsLength * 2, 16);
	tmpStr2.append(tmpStr);
	pdu.append(tmpStr2.right(2).toUpper());
	pdu.append(sms.smsText);

	return(pdu.toUpper());
}

QString Gsm::EncodeTo7bit(QString &text)
{
	QString result = "";
	QString strByte;
	int curr;
	int next;
	bool ok;
	int hex;
	int j = 0;
	int mask = 0;

	for (int i=0; i<text.length(); i+=1) {
		curr = text.mid(i, 1).toUtf8().toHex().toInt(&ok,16);
		next = text.mid(i+1, 1).toUtf8().toHex().toInt(&ok,16);
		curr >>= j;
		mask |= (1 << j);
		hex = mask & next;
		curr |= hex << (7-j);
		if (j == 7) {
			mask = 0;
			j=0;
			curr |= hex;
		}
		else {
			j++;
			strByte = "00";
			strByte.append(QString::number(curr, 16));
			result.append(strByte.right(2));
		}
	}
	return(result.toUpper());
}

QString Gsm::EncodeToUnicode(QString &text)
{
	QString result = "";
	QString tmpc;

	//qDebug() << "[Gsm::EncodeToUnicode] length: " << QString::number(text.length());
	for (int i=0; i<text.length(); i+=1) {
		//qDebug() << text.mid(i, 1) << ": " << text.mid(i, 1).toUtf8().toHex();
		tmpc = text.mid(i, 1).toUtf8().toHex().right(2);
		if (text.mid(i, 1).toUtf8().toHex().length() < 4) {
			result.append("00");
			result.append(tmpc);
		}
		else {
			result.append("03");
			if (tmpc.mid(0, 1) == "8") {
				tmpc.replace(0,1,'C');
			}
			result.append(tmpc);
		}
		//result.append( text.mid(i+2, 1).toUtf8().toHex());
	}
	return(result);
}

QString PrintBin(int num)
{
	QString res;
	for (int i=7; i>=0; i--) {
		if (num & (1 << i)) res.append("1");
		else res.append("0");
	}
	return(res);
}

sms_t Gsm::DecodePDU(QString &pduSms)
{
	sms_t tmpSms;
	QString tmpStr;
	QByteArray tmpBytes;
	tmpStr = pduSms.mid(24, 10);
	tmpSms.smsTel = SwapBytes(tmpStr);

	tmpStr = pduSms.mid(54, pduSms.length() - 54);
	tmpStr.replace("\r", "");
	tmpStr.replace("\n", "");
	bool ok;
	int hex;
	if (pduSms.mid(37,1) == "8") {
		//utf-8
		for (int i=0; i<tmpStr.length(); i+=4) {
			hex = tmpStr.mid(i,4).toInt(&ok, 16);
			tmpSms.smsText.append(QChar(hex));
		}
	}
	else {
		//7-bit // http://www.dreamfabric.com/sms/hello.html
		int initial = 0;
		int head = 0;
		int mask = 0;
		int j=7;
		for (int i=0; i<tmpStr.length(); i+=2) {
			initial = tmpStr.mid(i,2).toInt(&ok, 16);
			hex = initial;
			mask |= (1 << j);
			hex &= ~mask;
			hex <<= (7-j);
			hex |= head;
			head = initial >> j;
			tmpSms.smsText.append(QChar(hex));
			if (j == 1) {
				mask = head = 0;
				hex = initial >> 1;
				tmpSms.smsText.append(QChar(hex));
				j = 7;
			}
			else {
				j--;
			}
		}
	}
	return(tmpSms);
}













