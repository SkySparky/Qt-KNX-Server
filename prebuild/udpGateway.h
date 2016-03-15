#ifndef UDPGATEWAY_H
#define UDPGATEWAY_H

#include <QObject>
#include <QtNetwork>
#include "knxGateway.h"
#include "cemi.h"
#include "common.h"

#define UDP_GATEWAY_DEST_NAME       "UDP"
#define UDP_GATEWAY_ALLOWED_SENDER  "KNX"

class UdpGateway : public QObject {
    Q_OBJECT

public:
    UdpGateway(QString conf);
    int Search();
    int Identify();
    int Connect();
    void Disconnect(int channel = -1);
    bool IsConnected();

private:

    QUdpSocket  m_udpControl;
    QUdpSocket  m_udpData;
    QString     m_conf;
    quint16     m_serverPort;
    quint16     m_controlPort;
    quint16     m_dataPort;
    QHostAddress m_serverAddress;
    KnxGateway::en_knxGatewayState m_state;
    QTimer      m_heartBeat;
    bool        m_heartBeatAck;
    QTimer      m_dataTimeout;
    int         m_dataRetries;

    void ChangeStateTo(KnxGateway::en_knxGatewayState state);

public slots:
    void onUdpControl();
    void onUdpData();
    void onHeartBeat();
    void onDataTimeout();
    void onQuit();
    void onSendData(QString groupAddr, QString data, cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);

signals:
    void DataFromUdp(QString evtData);
    void UdpState(KnxGateway::en_knxGatewayState state);
    void Notify(int notifyType, QString notifyData);
    void error(int socketError, const QString &message);
    void Log(QString logString);
    void Msg(int msgType, QString msg);
};

#endif // UDPGATEWAY_H
