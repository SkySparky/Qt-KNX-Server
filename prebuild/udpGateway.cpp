#include "udpGateway.h"

#define ACK_SEARCH  "ACK_SEARCH"
#define ACK_IDENTIFY "ACK_IDENTIFY"
#define ACK_CONNECT "ACK_CONNECT"
#define ACK_DISCONNECT "ACK_DISCONNECT"
#define ACK_HEARTBEAT "ACK_HEARTBEAT"
#define ACK_CMD "ACK_CMD"

UdpGateway::UdpGateway(QString conf) : m_conf(conf)
{

    QSettings settings(m_conf, QSettings::IniFormat);
    bool ok;
    QString tmpstr = settings.value("Gateway/gwIp").toString();
    m_serverAddress.setAddress(tmpstr);
    m_dataPort = m_serverPort = settings.value("Gateway/ugw_port").toInt(&ok);

    m_heartBeat.setInterval(60000);
    QObject::connect(&m_heartBeat, SIGNAL(timeout()), this, SLOT(onHeartBeat()));

    m_dataTimeout.setInterval(2000);
    QObject::connect(&m_dataTimeout, SIGNAL(timeout()), this, SLOT(onDataTimeout()));


    // UDP Control socket
    //
    QObject::connect(&m_udpControl, SIGNAL(readyRead()), this, SLOT(onUdpControl()));
    if (!m_udpControl.bind()) {
        ChangeStateTo(KnxGateway::KNXIP_STATE_ERROR);
        emit Msg(Common::MSG_TYPE_ERROR, tr("[KnxGateway::Search] bind err: ") + m_udpControl.errorString());
    }
    else {
        m_controlPort = m_udpControl.localPort();
        ChangeStateTo(KnxGateway::KNXIP_STATE_DISCONNECTED);
    }

    //UDP Data socket (for incoming only)
    //
    QObject::connect(&m_udpData, SIGNAL(readyRead()), this, SLOT(onUdpData()));
    if (!m_udpData.bind(m_dataPort, QUdpSocket::ShareAddress)) {
        emit Msg(Common::MSG_TYPE_ERROR, tr("[UdpGateway::Data] bind err: ") + m_udpData.errorString());
    }
    else {
        m_dataPort = m_udpData.localPort();
    }
}

// [CMD],[SOURCE],[TARGET],[DATA],...,[DATA]
void UdpGateway::onUdpControl()
{
    while (m_udpControl.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpControl.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpControl.readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        QString strdata(datagram.data());

        qDebug() << "[UdpGateway::onUdpControl] strdata: " << strdata;

        if (Common::GetParam(strdata, Common::PARAM_CMD).contains("CMD")) {
            if (Common::GetParam(strdata, Common::PARAM_SENDER).contains(UDP_GATEWAY_ALLOWED_SENDER) &&
                Common::GetParam(strdata, Common::PARAM_DEST).contains(UDP_GATEWAY_DEST_NAME)) {

                QString tmpstr = Common::GetParam(strdata, Common::PARAM_DATA_START);  //get data
                if (tmpstr.contains(ACK_SEARCH)) {
                    QString notifydata = "ip=" +sender.toString()
                            + ",descr=" + Common::GetParam(strdata, Common::PARAM_DATA_START+1);;

                    ChangeStateTo(KnxGateway::KNXIP_STATE_FOUND_GW);
                    emit Notify(Common::NOTIFY_KNX_SEARCH_RESULT, notifydata);
                }
                else if (tmpstr.contains(ACK_IDENTIFY)) {
                    ChangeStateTo(KnxGateway::KNXIP_STATE_IDENTIFY);
                }
                else if (tmpstr.contains(ACK_CONNECT)) {
                    ChangeStateTo(KnxGateway::KNXIP_STATE_CONNECTED);
                }
                else if (tmpstr.contains(ACK_DISCONNECT)) {
                    ChangeStateTo(KnxGateway::KNXIP_STATE_DISCONNECTED);
                }
                else if (tmpstr.contains(ACK_HEARTBEAT)) {

                }
                else if (tmpstr.contains(ACK_CMD)) {

                }
                else return; //return without reset timeout
                m_dataTimeout.stop();
            }
        }

        m_dataTimeout.stop();
    }
}


void UdpGateway::onUdpData()
{
    while (m_udpControl.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpControl.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;

        m_udpControl.readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        QString strdata(datagram.data());

        if (Common::GetParam(strdata, 1) == "WRITE") {

        }

        qDebug() << "[UdpGateway::onUdpData] strdata: " << strdata;
        m_dataTimeout.stop();

    }
}


int UdpGateway::Search()
{
    QString tmpstr = "CMD,UDP,KNX,SEARCH";

    QByteArray datagram;
    datagram.append(tmpstr);

    quint64 dlen = m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                                      QHostAddress::Broadcast, m_serverPort);
    ChangeStateTo(KnxGateway::KNXIP_STATE_SEARCHING);
    m_dataTimeout.start();
    return(dlen);
}


int UdpGateway::Identify()
{
    QString tmpstr = "CMD,UDP,KNX,IDENTIFY";

    QByteArray datagram;
    datagram.append(tmpstr);

    quint64 dlen = m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                                      m_serverAddress, m_serverPort);
    ChangeStateTo(KnxGateway::KNXIP_STATE_IDENTIFY);
    m_dataTimeout.start();
    return(dlen);
}


int UdpGateway::Connect()
{
    QString tmpstr = "CMD,UDP,KNX,CONNECT";

    QByteArray datagram;
    datagram.append(tmpstr);

    quint64 dlen = m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                                      m_serverAddress, m_serverPort);
    ChangeStateTo(KnxGateway::KNXIP_STATE_CONNECTING);
    m_dataTimeout.start();
    return(dlen);
}


void UdpGateway::Disconnect(int channel)
{
    QString tmpstr = "CMD,UDP,KNX,DISCONNECT";

    QByteArray datagram;
    datagram.append(tmpstr);

    m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                        m_serverAddress, m_serverPort);
    ChangeStateTo(KnxGateway::KNXIP_STATE_DISCONNECTED);
}


bool UdpGateway::IsConnected()
{
    return((m_state == KnxGateway::KNXIP_STATE_CONNECTED) ? true : false);
}


void UdpGateway::ChangeStateTo(KnxGateway::en_knxGatewayState state)
{
    m_state = state;
    emit UdpState(m_state);
}



void UdpGateway::onHeartBeat()
{
    if (m_heartBeatAck == false) {
        //No connection
        emit Msg(Common::MSG_TYPE_ERROR, tr("Heartbeat timeout."));
        Disconnect();
        return;
    }
    QString tmpstr = "CMD,UDP,KNX,HEARTBEAT";
    QByteArray datagram;
    datagram.append(tmpstr);

    m_dataTimeout.start();
    m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                        m_serverAddress, m_serverPort);
}


void UdpGateway::onDataTimeout()
{
    m_dataTimeout.stop();
    Msg(Common::MSG_TYPE_ERROR, tr("Command timeout."));
    if (m_dataRetries++ >= 3) {
        //Try to reconnect
        if ((m_state != KnxGateway::KNXIP_STATE_SEARCHING) ||
                (m_state != KnxGateway::KNXIP_STATE_IDENTIFY)) {
            Disconnect();
            Connect();
        }
        m_dataRetries = 0;
    }
}


void UdpGateway::onQuit()
{

}


void UdpGateway::onSendData(QString groupAddr, QString data, cEMI::en_cemiAction action)
{
    QString tmpstr = "WRITE,";
    if (action == cEMI::CEMI_ACTION_WRITE) tmpstr = "WRITE,";
    else if (action == cEMI::CEMI_ACTION_READ) tmpstr = "READ,";
    else return;

    tmpstr += "UDP,KNX," + groupAddr + "," + data;
    QByteArray datagram;
    datagram.append(tmpstr);

    m_dataTimeout.start();
    m_udpControl.writeDatagram(datagram.data(), datagram.size(),
                        m_serverAddress, m_serverPort);
}
