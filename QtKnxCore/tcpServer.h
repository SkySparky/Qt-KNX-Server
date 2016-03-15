/*
 * tcpServer.h
 *
 *  Created on: 02 Αυγ 2010
 *      Author: Administrator
 */

#ifndef TCPSERVER_H_
#define TCPSERVER_H_

#include <QtCore>
#include <QtNetwork>
#include <QObject>
#include "common.h"
#include "conf.h"
#include "cemi.h"
//#include "xmlParser.h"
//#include "calendar.h"
#include "HttpResponse.h"
#include "knxdb.h"

class TcpServer : public QObject {
	Q_OBJECT

public:
	TcpServer();
	//~TcpServer();
	bool Start(void);
	bool Stop(void);
	QTcpServer server;

public slots:
	void OnClientConnection();
	void OnClientData();
	void OnClientDisconnection();
	void OnClientError(QAbstractSocket::SocketError err);

private:
	QHostAddress svrAddr;
	quint16 svrPort;
	int	maxConnections;
	QMutex descrMutex;
	//bool justConnected;

	void DataHandler(QString incomingData, QString & response);
	void CalendarDataHandler(QString incomingData, QString & response);
	void KnxDataHandler(QString incomingData, QString & response);
	void RoomDataHandler(QString incomingData, QString & response);
signals:
	void TcpServerData(int action, int groupAddr, QString data);

};
#endif /* TCPSERVER_H_ */
