/*
 * main.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QList>
#include <QUuid>
#include <QSettings>
#include "consoleCapture.h"
#include "cemi.h"
//#include "conf.h"
#include "../KnxCommon/common.h"
#include "knxGateway.h"
#include "knxdb.h"
//#include "tcpServer.h"
#include "gidt_mod_manager.h"
#include "logger.h"
#include "udpServer.h"

#include "ModuleDB.h"

typedef struct {
	QString inbox;
	QString hbbox;
	QString logbox;
	//DB
	QString dbName;
	QString dbServer;
	QString dbUser;
	QString dbPassword;
} knxCore_t;


class MainSignalHandler : public QObject {
	Q_OBJECT
signals:
	void AllQuit();
	void MainQuit();

public slots:
	void ConsoleMsg(QString msg);
	void TimerMainQuit() {
		emit MainQuit();
	}
	/*
	void ExecuteDB(QString cmd, QString param);
	void ModuleAlert(QString target, QString result);
	void KnxDataHandler(int action, int groupAddr, QString data);
	void WebServerConnection();
	*/
};


#endif /* MAIN_H_ */
