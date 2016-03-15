/*
 * XSocket.h
 *
 *  Created on: 03 Δεκ 2010
 *      Author: Dimitris
 */

#ifndef XSOCKET_H_
#define XSOCKET_H_

#include <QtCore>
#include <QTcpSocket>
#include <QObject>
#include <QSettings>
#include <QTimer>

typedef struct {
	QString	id;
	QString remoteHost;
	quint64 remotePort;
	QString iniFile;
} xport_t;


class XSocket : public QObject {
	Q_OBJECT

private:
	typedef struct {
		QString	cmd;
		int preDelay;
		int postDelay;
		bool sent;
	} cmd_t;
	QList<cmd_t> m_commandList;

	xport_t m_xport;
	QTcpSocket m_socket;
	QMap<QString, QString> m_commands;
	QTimer * m_cmdTimer;
	bool Connect();
	bool Disconnect(void);
	QString m_inBuffer;
	QTimer * m_timeout;

public:
	XSocket(const xport_t &tvSet);
	~XSocket();
	quint64 SendData(QString &cmd, QString &data, uint preDelay = 0, uint postDelay = 0);

public slots:
	void OnTimeout();
	void OnCmdTimer();
	void OnClientData();
	void OnClientDisconnection();
	void OnClientError(QAbstractSocket::SocketError err);
};

#endif /* XSOCKET_H_ */
