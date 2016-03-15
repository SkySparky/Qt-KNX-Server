#ifndef UDPSERVER_H_
#define UDPSERVER_H_

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include <QMutex>
#include <QMap>
#include "../KnxCommon/common.h"

#define BROADCAST_PORT 8989


class UdpServer : public QObject 
{
	Q_OBJECT

	typedef enum {
		UDP_STATE_DISCONNECTED,	/*!< Disconnected */
		UDP_STATE_CONNECTING,		/*!< Server is trying to connect on a gateway */
		UDP_STATE_CONNECTED,		/*!< Server is connected on a gateway */
		UDP_STATE_DISCONNECTING	/*!< Server is disconnecting from a gateway */
	} tp_udpState;

	typedef struct {
		quint16	port;
		uint lastTime;
	} tp_clients;

	QMap<QString,tp_clients> m_udpClients;
	tp_udpState m_state;
	QString m_localIp;
	quint16	m_port;

	void	AddLog(QString logMsg);
	QString GetParam(QString &inString, int param);

signals:
	void SendEvent(QString moduleName, QString params);	//command to modules
	void Output(QString knxCmd);						//read from knx gateway
	void Log(QString logString);
	//void LogicUnitEvent(QString dbParamName, QString dbParamValue, int dbParamType);

public slots:
	void Input(QString);
	void OnUdpData(void);
	void AllQuit(void);

public:
	UdpServer(QString & localIp, quint16 port);
	void BroadcastData(QString data);	//broadcast data to port

};



#endif //UDPSERVER_H_
