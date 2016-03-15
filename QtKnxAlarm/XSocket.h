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
	QTimer * m_timeout;
	uint m_reconnectTimer;
	uint m_timeoutTmr;

	xport_t m_xport;
	QTcpSocket m_socket;
	QTimer * m_cmdTimer;
	bool Connect();
	bool Disconnect(void);

public:
	XSocket(const xport_t &tvSet);
	~XSocket();

public slots:
	void Input(QString data, uint preDelay = 0, uint postDelay = 0);
	void OnTimeout();
	void OnCmdTimer();
	void OnClientData();
	void OnClientDisconnection();
	void OnClientError(QAbstractSocket::SocketError err);

signals:
	void Output(QByteArray);
};

#endif /* XSOCKET_H_ */
