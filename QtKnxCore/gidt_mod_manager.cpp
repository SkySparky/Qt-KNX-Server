/*
 * gidt_mod_manager.cpp
 *
 *  Created on: 22 Δεκ 2010
 *      Author: Administrator
 */
#include "gidt_mod_manager.h"

#define VERSION "0.1"


ModuleManager::ModuleManager(QCoreApplication * app, QString &iniFile)
{
	m_app = app;
	m_version = VERSION;
	m_iniFile = iniFile;
	m_quit = false;
	m_init = false;
	m_moduleName = "ModuleManager";
}

ModuleManager::~ModuleManager() {
	CleanAll();
}


void ModuleManager::CleanAll()
{
	if (!m_modules.isEmpty()) {
		qDebug() << "cleaner";
		for (int i = 0; i<m_modules.count(); i++) {
			StopModule(m_modules[i]);
		}
	}
}

void ModuleManager::AddLog(QString logMsg)
{
	emit Log("[ModManager]: " + logMsg);
}


int ModuleManager::Begin(void)
{
	int resp = -1;
	bool bResp = false;
	GetRunningProcs();

	//read config file and retrieve module list
	if ( QFile::exists(m_iniFile)) {
		LoadIniFile();
		for (int i = 0; i<m_modules.count(); i++) {
			//read modules ini file
			resp = LoadModIniFile(m_modules[i]);
			if (resp < 0) return(resp);
			bResp = StartModule(m_modules[i]);
			if (!bResp) {
				AddLog("Failed to load " + m_modules[i].name);
				return(-1);
			}
		}
	}
	if (m_modules.isEmpty()) {
		resp = 0;
	}
	else {
		resp = 1;
	}
	return(resp);
}

void ModuleManager::OnTimer()
{
	for (int i=0; i<m_modules.count(); i++) {
		if ((m_modules[i].hbCntr++) >= m_modules[i].hbPeriod+30) {
			m_modules[i].hbCntr = 0;	//reset counter
			//No heartbeat received
			StopModule(m_modules[i]);	//ensure stop module
			StartModule(m_modules[i]);	//restart module
			AddLog("Restarting module: " + m_modules[i].name);
		}
	}
	if ((m_psCntr++) >= m_psPeriod) {
		m_psCntr = 0;
		//qDebug() << "Refresh running processes";
		GetRunningProcs();
	}
}


void ModuleManager::Input(QString data)
{
	//Check if module name exists
    QString dest = GetParam(data, Common::PARAM_DEST);

	for (int i=0; i<m_modules.count(); i++) {
		if (m_modules[i].name == dest) {
			//Get module folder
			QString fName = m_modules[i].inbox + "/" + QUuid::createUuid() + ".txt";
			QFile file(fName);
			if (!file.open(QIODevice::ReadWrite | QIODevice::Text)) {
				AddLog("[::SendEvent]: Could not open file: " + m_modules[i].inbox);
				//qDebug() << "[GidtModule::run] Could not open file: " << list[i].fileName();
				file.close();
			}
			else {
				QTextStream stream(&file);
				AddLog("[::SendEvent]: " + data);
				stream << data;
				stream.flush();
				file.close();
			}
			return;
		}
	}
}

void ModuleManager::AllQuit()
{
	m_quit = true;
}

void ModuleManager::ManagerThread(void)
{
	QFileInfoList list;

	qDebug() << "MadManager Thread id: " << QThread::currentThreadId();

	QMutex dummy;
	QWaitCondition waitCondition;
	quint16 timerCntr = 0;


	//Create DB connection
	ModuleDB dbMod(m_dbName, m_dbHostName, m_dbUserName, m_dbPassword, m_moduleName);
	dbMod.Connect();

	while(!m_quit) {
		dummy.lock();
		waitCondition.wait(&dummy, m_hbPolling);
		dummy.unlock();
		if ((timerCntr++) == 10) {	//10*100msec = 1sec
			timerCntr = 0;
			OnTimer();
		}
		//usleep(m_hbPolling * 100);	//polling time for dir

		list = m_inbox.entryInfoList(QDir::Files | QDir::Modified | QDir::Readable, QDir::Time | QDir::Reversed);
		//qDebug() << m_hbDir.path();
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
							AddLog("[ModuleManager::ManagerThread]: Could not open file: " + list[i].absoluteFilePath());
							//qDebug() << "[GidtModule::run] Could not open file: " << list[i].fileName();
							file.close();
						}
						else {
							QTextStream stream(&file);
							QString line = stream.readLine();
							while (!line.isNull()) {
								//Search for params
								for (int i=0; i<m_modules.count(); i++) {
                                    if ( m_modules[i].name == GetParam(line, Common::PARAM_SENDER) ) {
										//Check if this module name exists
                                        if (!GetParam(line,Common::PARAM_CMD).contains("HB")) {	//CMD doesn't contains HB. It's not heartbeat
											emit Output(line);
										}
										else {
											//reset timer
											m_modules[i].hbCntr = 0;
											qDebug() << "[ModuleManager::ManagerThread]: received HB from " << m_modules[i].name;
										}
									}
								}
								line = stream.readLine();
							};
							//delete file
							file.close();
							if (file.remove() == false) {
								AddLog("[ModuleManager::ManagerThread] Could not remove file: " + list[i].absoluteFilePath());
								//qDebug() << "[Watcher]: could not remove file.";
							}
						}
					}
					else
						file.close();
				} //~ Check that file is not empty
			} //~ search each file
		} //~ Check if any files are found
	} //~ while loop
	//exec();
}

bool ModuleManager::LoadIniFile(void)
{
	bool resp = false;
	bool ok;
	//QString tmpStr;

	QSettings settings(m_iniFile, QSettings::IniFormat);

	m_hbPolling = settings.value("Modules/hb_polling_ms").toString().toInt(&ok);
	m_inbox = QDir( settings.value("Modules/inbox").toString() );
	m_psPeriod = settings.value("Modules/ps_polling_sec").toString().toInt(&ok);
	m_psCntr = 0;

	m_dbName = settings.value("Database/dbName").toString();
	m_dbHostName = settings.value("Database/dbServer").toString();
	m_dbUserName = settings.value("Database/dbUser").toString();
	m_dbPassword = settings.value("Database/dbPassword").toString();

	//qDebug() << "[ModuleManager::LoadIniFile]: m_hbDir: " << m_hbDir.path() << ", m_hbPolling: " << m_hbPolling;

	int size = settings.beginReadArray("Modules");
	AddLog("Number of modules found: " + QString::number(size));
	if (size > 0) {
		for (int i = 0; i < size; ++i) {
			//fill modules list
			modStats_t tmpMod;

			settings.setArrayIndex(i);
			tmpMod.name = settings.value("module").toString();
			AddLog("tmpMod.name: " + tmpMod.name);
			tmpMod.iniFile = settings.value("module_conf").toString();
			//qDebug() << "tmpMod.iniFile: " << tmpMod.iniFile;
			m_modules << tmpMod;
		}
		settings.endArray();
	}

	resp = true;
	return(resp);
}

int ModuleManager::LoadModIniFile(modStats_t &module)
{
	int resp = 0;
	bool ok = false;
	if (QFile::exists(module.iniFile)) {
		QSettings settings(module.iniFile, QSettings::IniFormat);
		module.inbox = settings.value("Module/mod_inbox").toString();
		module.path = settings.value("Module/mod_path").toString();
		module.exec = settings.value("Module/mod_exec").toString();
		module.hbPeriod = settings.value("Module/mod_hb_per").toInt(&ok) + HB_TIME_SHIFT;	//
		if (!ok) {
			Log("mod_hb_per in ini file (" + module.iniFile + "is invalid.");
			exit(-1);
		}
		module.pid = 0;
		module.hbCntr = 0;
		module.testCntr = 0;
		module.modState = MOD_STATE_INIT;
	}
	else {
		resp = MOD_MANAGER_ERR_MODULE_PATH_NOT_FOUND;
	}
	//resp = 0;
	return(resp);
}


bool ModuleManager::StartModule(modStats_t &module)
{
	bool resp = true;
	if (!IsProcAlive(module.exec)) {
		resp = false;
		QString proc = module.path + "/" + module.exec;
		module.proc = new QProcess(this);

		QStringList env = QProcess::systemEnvironment();
		QString appPath = module.path.replace("/", "\\");
		env.replaceInStrings(QRegExp("^PATH=(.*)", Qt::CaseInsensitive), "PATH=\\1;"+appPath);
		//qDebug() << env;
		module.proc->setEnvironment(env);
		module.proc->setWorkingDirectory(module.path);
		qint64 pid = 0;
		module.proc->startDetached(proc, QStringList() << "", module.path, &pid);
		if (pid < 1) {
			qDebug() << "FAILED";
			Log("Failed to start module: " + module.exec);
			resp = false;
			//m_app->exit(-1);
		}
		else {
			module.hbCntr = 0;
			module.testCntr = 0;
			module.pid = pid;
			module.modState = MOD_STATE_ENABLED;
			resp = true;
			qDebug() << "started process: " << module.exec << "," << pid;
		}
	}
	else {
		module.proc = NULL;
	}
	return(resp);
}


bool ModuleManager::StopModule(modStats_t &module)
{
	bool resp = false;
	QProcess process;

	qDebug() << "[ModuleManager::StopModule] " + module.exec;
	process.start("cmd.exe", QStringList() << "/C" << "taskkill" << "/F" << "/PID" << QString::number(module.pid)); //taskkill /PID %1 /T").arg(pinfo->dwProcessId
	process.waitForStarted(1000);
	process.waitForFinished(1000);
	if (module.proc != NULL) {
		module.proc->close();
		module.proc->deleteLater();
	}
	return(resp);
}


bool ModuleManager::GetRunningProcs(void)
{
	bool resp = true;
	m_runningProcs.clear();

	QProcess process;
	process.setReadChannel(QProcess::StandardOutput);
	process.setReadChannelMode(QProcess::MergedChannels);

    //process.start("cmd.exe /C echo test");
	process.start("cmd", QStringList() << "/C" << "echo" << "process" << "get" << "caption" << "|" << "wmic");
	//m_psProc->start("notepad.exe");
	process.waitForStarted(1000);
	process.waitForFinished(1000);
	m_runningProcs = process.readAll();

	//qDebug() << m_runningProcs;
	if (m_runningProcs.isEmpty()) resp = false;

	return(resp);
}


bool ModuleManager::IsProcAlive(QString procName)
{
	bool resp = false;
	if (!m_runningProcs.isEmpty()) {
		if (m_runningProcs.contains(procName.toLatin1())) resp = true;
	}
	return(resp);
}
