/*
 * gidt_module.h
 *
 *  Created on: 10 Δεκ 2010
 *      Author: Administrator
 */

#ifndef GIDT_MODULE_H_
#define GIDT_MODULE_H_

#include <QtCore>
#include <QCoreApplication>
#include <QObject>
#include <QThread>
#include <QTextStream>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QString>
#include <QStringList>
#include <QTimer>
#include <QSettings>
#include <QMap>
#include <QList>
#include <QDateTime>
#include <QUuid>
#include "../KnxCommon/common.h"

#define VERSION "0.1"
#define LOCAL_LOG "error_log.txt"


typedef struct {
	QString ga;
	QString value;
	int type;
} tp_groupAddr;

class GidtModule : public QThread {
	Q_OBJECT
private:
	typedef enum {
		MOD_STATE_INIT,
		MOD_STATE_DISABLED,
		MOD_STATE_ENABLED,
		MOD_STATE_ERROR
	} modState_en;

	typedef enum {
		DATA_TYPE_CMD,
		DATA_TYPE_ERROR,
		DATA_TYPE_EVENT
	} modDataType_en;

	QCoreApplication * m_app;
	QObject * m_parent;
	QString m_localLog;
	QString m_version;		//module version
	QString m_name;
	QString m_path;
	QString m_inbox;
	QString m_outbox;
	int m_inboxPolling;		//polling time in ms
	QString m_execCmd;
	int m_hb_period;
	int m_hb_counter;
	QTextCodec *m_codec; 

	modState_en 	m_state;
	QString 		m_iniFile;
	QDir 			m_watchDir;

	QTimer		*m_timer;	//module timer

	void Init(QString moduleIniFile);
	bool LoadIniFile(void);	//checks sanity and loads the inifile
	void SelfDestroy(void);
	void PerformTest(void);				//performs internal test

protected:
	void run(void);						//initiates module thread

public:
	GidtModule(QObject * parent, QString moduleIniFile);
	GidtModule(QCoreApplication * parent, QString moduleIniFile);
	~GidtModule();
	void Write(QString data);			//writes to inbox
	bool Enable(void);			//Enables module
	bool Disable(void);			//Disabled module
	const bool IsEnabled(void);	//returns whether the module is enabled or disabled
	const int GetState(void);	//returns the current state of the module
	void Log(QString msg);

signals:
	void Output(QString);

public slots:
	void OnTimer();
};


#endif /* GIDT_MODULE_H_ */
