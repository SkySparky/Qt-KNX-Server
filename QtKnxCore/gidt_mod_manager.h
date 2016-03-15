/*
 * gidt_mod_manager.h
 *
 *  Created on: 22 Δεκ 2010
 *      Author: Administrator
 */

#ifndef GIDT_MOD_MANAGER_H_
#define GIDT_MOD_MANAGER_H_

//#define IS_WIN 1

#include <QtCore>
#include <QCoreApplication>
#include <QSettings>
#include <QProcess>
#include <QTimer>
#include <QFile>
#include "ModuleDB.h"
#include "../KnxCommon/common.h"

#define PROT_PARAM_MODULE_NAME 		1
#define PROT_PARAM_TYPE 			2
#define PROT_PARAM_NUM_OF_PARAMS 	3
#define PROT_PARAM_CMD_TYPE 		3

#define HB_TIME_SHIFT	3	//give 3 secs time shift for the heartbeat


typedef enum {
	MOD_MANAGER_ERR_NO_MODULES_FOUND = -1,
	MOD_MANAGER_ERR_MODULE_PATH_NOT_FOUND = -2,
	MOD_MANAGER_ERR_WRONG_PARAM_DECLARATION = -3
} modManagerErrors_en;

struct modParams_t {
	QString name;
	int type;
};

class ModuleManager  : public QObject {
	Q_OBJECT
private:
	enum modState_en{
		MOD_STATE_INIT,
		MOD_STATE_DISABLED,
		MOD_STATE_ENABLED,
		MOD_STATE_ERROR
	};

	struct modStats_t {
		QString 	name;		//module's name
		QString		inbox;
		QString 	iniFile;	//ini file (including path)
		QString		path;
		QString		exec;		//run command
		QList<modParams_t> params;
		uint		numOfParms;
		uint		hbPeriod;	//heartbeat period (secs)
		uint		hbCntr;
		uint		testPeriod;	//test module every secs
		uint		testCntr;
		modState_en modState;	//module's state
		QProcess	*proc;
		qint64		pid;
	};

	QString 	m_iniFile;				//conf file to look for init
	//QTimer		*m_timer;				//generic timer
	QList<modStats_t> m_modules;		//found modules
	uint		m_hbPolling;
	uint		m_psPeriod;				//check running processes period;
	uint		m_psCntr;				// counter for trigger PS
	QString 	m_version;				// module manager version
	QByteArray 	m_runningProcs;
	QCoreApplication * m_app;
	QDir		m_inbox;
	bool		m_quit;
	bool		m_init;
	QString		m_dbName;
	QString		m_dbHostName;
	QString		m_dbUserName;
	QString		m_dbPassword;
	QString		m_moduleName;

	bool LoadIniFile(void);
	int LoadModIniFile(modStats_t &module);
	bool StartModule(modStats_t &module);
	bool StopModule(modStats_t &module);
	bool GetRunningProcs(void);
	bool IsProcAlive(QString procName);
    void AddLog(QString logMsg);
	void OnTimer(void);

public:
	ModuleManager(QCoreApplication * app, QString &iniFile);
	~ModuleManager();
	void CleanAll();
	int Begin(void);

signals:
	void Log(QString logString);
	void Output(QString);

public slots:
	void ManagerThread(void);
	void Input(QString);
	void AllQuit();
};

#endif /* GIDT_MOD_MANAGER_H_ */
