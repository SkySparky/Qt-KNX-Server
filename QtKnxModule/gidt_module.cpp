/*
 * gidt_module.cpp
 *
 *  Created on: 10 Δεκ 2010
 *      Author: Administrator
 */

#include "gidt_module.h"


GidtModule::GidtModule(QCoreApplication * parent, QString moduleIniFile)
{
	m_app = parent;
	m_parent = NULL;
	Init(moduleIniFile);
}

GidtModule::GidtModule(QObject * parent, QString moduleIniFile)
{
	m_parent = parent;
	m_app = NULL;
	Init(moduleIniFile);
}

GidtModule::~GidtModule() {
	if (m_state == MOD_STATE_ENABLED) Log("quiting");
}

void GidtModule::SelfDestroy(void)
{
	if (m_app != NULL) {
		m_app->exit(-1);
	}
	else if (m_parent) {
		m_parent->~QObject();
		exit(-1);
	}
	else {
		exit(-1);
	}
}

void GidtModule::Init(QString moduleIniFile) {

	m_state = MOD_STATE_INIT;
	m_localLog = LOCAL_LOG;

	//check inifile
	if (!QFile::exists(moduleIniFile)) {
		Log("Could not find ini file!");
		SelfDestroy();
	}
	m_iniFile = moduleIniFile;
	//else open inifile and read
	if ( LoadIniFile() ) {
		m_state = MOD_STATE_DISABLED;
		m_timer = new QTimer(this);
		connect(m_timer, SIGNAL(timeout()), this, SLOT(OnTimer()));
	}
	else {
		Log(" An error occured while reading the ini file.");
		SelfDestroy();
	}
}

void GidtModule::Log(QString msg)
{
	//sign error
	QFile log(m_localLog);
	if (!log.open(QIODevice::Append | QIODevice::Text)) {
		//Double fail
		qDebug() << "[GidtModule] Couldn't even write a log file. WTF man?";
		SelfDestroy();
	}
	QTextStream w_stream(&log);
	QString logEvent = QDateTime::currentDateTime().toString() + " : [GidtModule] : " + msg + "\n";
	//w_stream << QDateTime::currentDateTime().toString() << " : [GidtModule] : " << msg << "\n";
	w_stream << logEvent;
	qDebug() << logEvent;
	w_stream.flush();
	log.flush();
	log.close();
}


bool GidtModule::LoadIniFile(void)
{
	bool resp = false;
	bool ok;
	QString tmpStr;

	QSettings settings(m_iniFile, QSettings::IniFormat);

	m_version = VERSION;

	m_name = settings.value("Module/mod_name").toString();
	m_path = settings.value("Module/mod_path").toString();
	m_inbox = settings.value("Module/mod_inbox").toString();
	m_outbox = settings.value("Module/mod_outbox").toString();
	m_inboxPolling = settings.value("Module/mod_inbox_polling_ms").toInt(&ok);
	if (!ok) {
		Log("m_inboxPolling in ini file is invalid.");
		exit(-1);
	}
	m_execCmd = settings.value("Module/mod_exec").toString();
	m_hb_period = settings.value("Module/mod_hb_per").toInt(&ok);
	if (!ok) {
		Log("m_hb_period in ini file is invalid.");
		exit(-1);
	}

	resp = true;
	return(resp);
}

bool GidtModule::Enable(void)
{
	m_state = MOD_STATE_ENABLED;
	m_watchDir = QDir(m_inbox);

	m_hb_counter = m_hb_period;
	m_timer->start(1000);

	this->start();
	return(this->isRunning());
}

bool GidtModule::Disable(void)
{
	bool resp=true;
	m_state = MOD_STATE_DISABLED;
	return(resp);
}

const bool GidtModule::IsEnabled(void)
{
	bool resp = false;
	if (m_state == MOD_STATE_ENABLED) resp = true;
	return(resp);
}

const int GidtModule::GetState(void)
{
	return((int) m_state);
}

void GidtModule::PerformTest(void)
{
	//Do self test and report to outbox
	QString resp = "OK";

}

void GidtModule::Write(QString data)
{
	//write to outbox
	QString fileName = m_outbox + "/" + QUuid::createUuid() + ".txt";
	
	QFile file(fileName);
	if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
		Log("[GidtModule::run] Could not open file for wrte: " + fileName);
		file.close();
	}
	else {
		QTextStream w_stream(&file);
		//w_stream << m_name << "," << param << "=" << strValue << "\0";
		w_stream << data;
		w_stream.flush();
		file.close();
	}
	
}

void GidtModule::OnTimer()
{
	QDateTime now = QDateTime::currentDateTime();
	if (m_hb_period != 0) {
		if (!(m_hb_counter--)) {
			m_hb_counter = m_hb_period;
			Write("HB," + m_name + ",DB,"+QString::number(now.toTime_t()));
		}
	}
}

void GidtModule::run()
{
	QFileInfoList list;
	Log("[GidtModule::Enabled]");
	while(m_state == MOD_STATE_ENABLED) {
		usleep(m_inboxPolling);	//polling time for dir
		list = m_watchDir.entryInfoList(QDir::Files | QDir::Modified | QDir::Readable, QDir::Time | QDir::Reversed);
		//Check if any files are found
		if (!list.isEmpty()) {
			//search each file
			for (int i = 0; i<list.length(); i++) {
				//Check that file is not empty
				if (list[i].size() > 0) {
					QFile file(list[i].absoluteFilePath());
					//Check file is not already opened
					if (!file.isOpen()) {
						if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
							Log("[GidtModule::run] Could not open file: " + list[i].absoluteFilePath());
							qDebug() << "[GidtModule::run] Could not open file: " << list[i].fileName();
							file.close();
						}
						else {
							QTextStream stream(&file);
							stream.setCodec("ISO 8859-7");
							QString line = stream.readLine();
							while (!line.isNull()) {
								emit Output(line);
								line = stream.readLine();
							};
							//delete file
							file.close();
							if (file.remove() == false) {
								Log("[GidtModule::run] Could not remove file: " + list[i].absoluteFilePath());
								qDebug() << "[Watcher]: could not remove file.";
							}
						}
					}
					else
						file.close();
				} //~ Check that file is not empty
			} //~ search each file
		} //~ Check if any files are found
	} //~ while loop
	Log("[GidtModule::Disabled]");
}
