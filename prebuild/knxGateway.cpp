/*
 * knxGateway.cpp
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */


//using namespace std;

#define KNXIP_VERSION 0x10   //knxip protocol version 1.0
#define KNXIP_HEADER_SIZE 6           // knxip header size for version 1.0
#define KNXIP_TP1_DATA_LEN  16

// Knxip services
#define KNXIP_SEARCH_REQ            0x201   // Sent by EIBnet/IP client to search available EIBnet/IP servers.
#define KNXIP_SEARCH_RESP           0x202   // Sent by EIBnet/IP server when receiving an EIBnet/IP SEARCH_REQUEST.
#define KNXIP_DESCRIPTION_REQ       0x203   // sent by EIBnet/IP client to an EIBnet/IP server to retrieve information about capabilities and supported services
#define KNXIP_DESCRIPTION_RESP      0x204   // Sent by EIBnet/IP server in response to a DESCRIPTION_REQUEST to provide information about the server implementation.
#define KNXIP_CONNECT_REQ           0x205   // Sent by EIBnet/IP client for establishing a communication channel to an EIBnet/IP server.
#define KNXIP_CONNECT_RESP          0x206   // Sent by EIBnet/IP server as answer to CONNECT_REQUEST telegram.
#define KNXIP_CONNECTION_STATE_REQ  0x207   // Sent by EIBnet/IP client for requesting the connection state of an established connection to an EIBnet/IP server.
#define KNXIP_CONNECTION_STATE_RESP 0x208   // CONNECTIONSTATE_REQUEST for an established connection.
#define KNXIP_DISCONNECT_REQ        0x209   // Sent by EIBnet/IP device, typically the client, to terminate an established connection.
#define KNXIP_DISCONNECT_RESP       0x20A   // Sent by EIBnet/IP device, typically the server, in response to a DISCONNECT_REQUEST.

// KNXIP TUNNELING SERVICES AND TYPES
#define KNXIP_TUNNELING_REQ         0x420   // Used for sending and receiving single EIB / KNX telegrams between EIBnet/IP client and server.
#define KNXIP_TUNNELING_ACK         0x421   // Sent by an EIBnet/IP device to confirm the reception of the TUNNELING_REQUEST.
#define KNXIP_TUNNELLING_CONNECTION 0x04    // Data connection used to forward EIB telegrams between two EIBnet/IP devices.

// PROTOCOL TYPES
#define KNXIP_PROTOCOL_IPV4_UDP     0x01    // Identifies an Internet Protocol version 4 address and port number for UDP communication.
#define KNXIP_PROTOCOL_IPV4_TCP     0x02    // Identifies an Internet Protocol version 4 address and port number for TCP communication.

// KNXIP COMMON ERRORS
#define KNXIP_ERR_NO_ERROR          0       // Operation successful
#define KNXIP_ERR_HOST_PROTOCOL_TYPE 1      // The requested host protocol is not supported by the EIBnet/IP
#define KNXIP_ERR_VERSION_NOT_SUPPORTED 2   // The requested protocol version is not supported
#define KNXIP_ERR_SEQUENCE_NUMBER   4       // Wrong sequense number in protocol detected. disconnect
#define KNXIP_ERR_CONNECTION_ID     0x21    // The requested host protocol is not supported by the EIBnet/IP
#define KNXIP_ERR_NO_MORE_CONNECTIONS	0x24	//Theres someone already connected or false disconnection and wait state
#define KNXIP_ERR_DATA_CONNECTION   0x26    // The requested protocol version is not supported
#define KNXIP_ERR_KNX_CONNECTION        0x27    // The received sequence number is out of order
#define KNXIP_ERR_TUNNELING_LAYER   0x29    // Error in knxip tunneling layer

// TIMEOUT CONSTS
#define KNXIP_CONNECT_REQUEST_TIMEOUT               10  // EIBnet/IP client SHALL wait for 10 seconds for a CONNECT_RESPONSE frame from EIBnet/IP server.
#define KNXIP_CONNECTIONSTATE_REQUEST_TIMEOUT       10  // EIBnet/IP client SHALL wait for 10 seconds for a CONNECTIONSTATE_RESPONSE frame from EIBnet/IP server.
#define KNXIP_DEVICE_CONFIGURATION_REQUEST_TIMEOUT  10  // EIBnet/IP client SHALL wait for 10 seconds for a DEVICE_CONFIGURATION_RESPONSE frame from EIBnet/IP server.

// INTERNET PROTOCOL CONSTS
#define KNXIP_EIBNET_MULTICAST_IP   "224.0.23.12"
#define KNXIP_EIBNET_MULTICAST_PORT 3671


// CUSTOM ERROR CODES
#define KNXIP_ERR_NOT_VALID_KNXIP_PACKET    101
#define KNXIP_ERR_NOT_VALID_KNXIP_PROTOCOL  102
#define KNXIP_ERR_UNKNOWN_SERVICE           103
#define KNXIP_ERR_WRONG_DATA_LENGTH         104

#define KNXIP_DATA_BUFFER	300

#include "knxGateway.h"

KnxGateway::KnxGateway(QString iniFile) : m_iniFile(iniFile)
{
	//Read ini file
    QSettings settings(m_iniFile, QSettings::IniFormat);
    bool ok;
    m_knxipStatus.gwip = settings.value("Gateway/gwIp").toString();
    m_knxipStatus.lastChannel = settings.value("Gateway/lastChannel").toInt(&ok);

    //Get interface
    m_interface = GetNetworkInterface();

    QObject::connect(&m_udpData, SIGNAL(readyRead()), this, SLOT(onUdpData()));
    QObject::connect(&m_udpControl, SIGNAL(readyRead()), this, SLOT(onUdpControl()));

    m_heartBeat.setInterval(60000);
    QObject::connect(&m_heartBeat, SIGNAL(timeout()), this, SLOT(onHeartBeat()));

    m_dataTimeout.setInterval(2000);
    QObject::connect(&m_dataTimeout, SIGNAL(timeout()), this, SLOT(onDataTimeout()));

    m_sendTimer.stop();
    m_sendTimer.setInterval(200);
    QObject::connect(&m_sendTimer, SIGNAL(timeout()), this, SLOT(onSendTimer()));

    m_client.localControlPort = m_client.localDataPort = 0;

    //Create CONTROL socket
    //if (!m_udpControl.bind(m_interface.ip(), 0)) {
    if (!m_udpControl.bind()) {
        ChangeStateTo(KNXIP_STATE_ERROR);
        emit Msg(Common::MSG_TYPE_ERROR, tr("[KnxGateway::Control] bind err: ") + m_udpControl.errorString());
    }
    else {
        m_client.localControlPort = m_udpControl.localPort();
        ChangeStateTo(KNXIP_STATE_DISCONNECTED);
    }
    //Create DATA socket
    //if (!m_udpData.bind(m_interface.ip(), 0)) {
    if (!m_udpData.bind()) {
        ChangeStateTo(KNXIP_STATE_ERROR);
        emit Msg(Common::MSG_TYPE_ERROR, tr("[KnxGateway::Data] bind err: ") + m_udpControl.errorString());
    }
    m_client.localDataPort = m_udpData.localPort();

//    qDebug() << "control: " << m_client.localControlPort << "data: " << m_client.localDataPort;
}


void KnxGateway::AddLog(QString logMsg)
{
    emit Log("[KnxGateway::" + logMsg);
}


void KnxGateway::onQuit()
{
    Disconnect();
}


QNetworkAddressEntry KnxGateway::GetNetworkInterface()
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if ((!(interface.flags() & QNetworkInterface::IsLoopBack))
                && QNetworkInterface::IsRunning && QNetworkInterface::CanBroadcast
                && QNetworkInterface::IsUp && QNetworkInterface::IsPointToPoint) {

            foreach(QNetworkAddressEntry entry, interface.addressEntries())
            {
                QString ip = entry.ip().toString();
                if (!ip.contains("::") && !ip.contains("169")) {
//                    qDebug() << "Found interface: " <<ip;
                    return entry;
                }
            }
        }
    }
    return QNetworkAddressEntry();
}


bool KnxGateway::IsConnected()
{
    bool resp = false;
    if (m_knxipStatus.state == KNXIP_STATE_CONNECTED) {
        //qDebug() << "[KnxGateway::IsConnected]";
        resp = true;
    }
    return(resp);
}


int KnxGateway::Search()
{
    char buffer[KNXIP_DATA_BUFFER];

    size_t headerLen = GetServiceHeader(KNXIP_SEARCH_REQ, &buffer[0]);
    QString localIP = m_interface.ip().toString();


//    qDebug() << "[KnxGateway::Search] send search request from : "
//             << m_interface.ip().toString() << ", " << m_client.localControlPort;

    Hpai hpai(localIP, m_client.localControlPort, HPAI_IP_PROTOCOL_IPV4_UDP);
    hpai.GetHpaiData((unsigned char*)&buffer[6]);

    quint64 dlen;
    dlen = m_udpControl.writeDatagram((char*)buffer, headerLen,
                                      QHostAddress("224.0.23.12"), KNXIP_EIBNET_MULTICAST_PORT);
    ChangeStateTo(KNXIP_STATE_SEARCHING);
    m_dataTimeout.start();
    return(dlen);
}


int KnxGateway::Identify(QString ip)
{
    char buffer[KNXIP_DATA_BUFFER];

    size_t headerLen = GetServiceHeader(KNXIP_DESCRIPTION_REQ, &buffer[0]);
    QString localIP;
    if (ip.isEmpty())
        localIP = m_interface.ip().toString();
    else
        localIP = ip;


//    qDebug() << "[KnxGateway::Search] send search to: " << m_knxipStatus.gwip << ", " << KNXIP_EIBNET_MULTICAST_PORT
//             << ", from : " << m_interface.ip().toString() << ", " << m_client.localControlPort;

    Hpai hpai(localIP, m_client.localControlPort, HPAI_IP_PROTOCOL_IPV4_UDP);
    hpai.GetHpaiData((unsigned char*)&buffer[6]);

    quint64 dlen = m_udpControl.writeDatagram((char*)buffer, headerLen,
                                QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);
    ChangeStateTo(KNXIP_STATE_IDENTIFY);
    return(dlen);
}


int KnxGateway::Connect()
{
    char buffer[KNXIP_DATA_BUFFER];

    //Create connection packet
    size_t headerLen = GetServiceHeader(KNXIP_CONNECT_REQ, &buffer[0]);
    QString localip = m_interface.ip().toString();
    Hpai hpai_control(localip,
              m_client.localControlPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);
    Hpai hpai_data(localip,
              m_client.localDataPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);

    hpai_control.GetHpaiData((unsigned char*) &buffer[6]);
    hpai_data.GetHpaiData((unsigned char*) &buffer[14]);
    //fill CRI data
    buffer[22] = 4;	//cri length
    buffer[23] = KNXIP_TUNNELLING_CONNECTION;
    buffer[24] = 2;	//link layer
    buffer[25] = 0;

    ChangeStateTo(KNXIP_STATE_CONNECTING);

    quint64 dlen = m_udpControl.writeDatagram((const char*)buffer, headerLen,
                                              QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);

    m_dataTimeout.start();
    return(dlen);
}


void KnxGateway::Disconnect(int channel)
{
//    qDebug() << "[KnxGateway::Disconnect]: Sending disconnect";

    //Create packet header
    char buffer[KNXIP_DATA_BUFFER];

    //Prepare disconnect data
    int dataLen = GetServiceHeader(KNXIP_DISCONNECT_REQ, &buffer[0]);
    if (channel < 0)
        buffer[6] = m_knxipStatus.commChannelId;
    else
        buffer[6] = (unsigned char) (channel & 0xFF);
    buffer[7] = 0;
    QString localip = m_interface.ip().toString();
    Hpai hpai(localip,
              m_client.localDataPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);
    hpai.GetHpaiData((unsigned char*) &buffer[8]);

    ChangeStateTo(KNXIP_STATE_DISCONNECTING);

    //send data
    m_udpControl.writeDatagram((const char*)buffer, dataLen,
                               QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);
    m_knxipStatus.state = KNXIP_STATE_DISCONNECTING;

    m_dataTimeout.start();
    m_heartBeat.stop();
}


void KnxGateway::onUdpControl()
{
    while (m_udpControl.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpControl.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        unsigned int serviceType = 0;

        m_udpControl.readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

       // qDebug() << "[KnxGateway::onUdpControl] ip: " << sender.toString() << ", port: " << senderPort;
        int dataStartPos = ValidateData(datagram.data(), datagram.size(), &serviceType);
       // qDebug() << "[KnxGateway::onUdpControl] serviceType: " << serviceType;
        if (dataStartPos >= 0) {
            //Control services
            if (serviceType == KNXIP_SEARCH_RESP) {

                Hpai knxipHpai((unsigned char*) &datagram.data()[dataStartPos], 8);

                QString knxipIP = knxipHpai.GetAddr();
                QByteArray descr(&datagram.data()[32 +dataStartPos ], 21);
                QString knxipDescr(descr);
                QString notifydata = "ip=" +knxipIP + ",descr=" + knxipDescr;

                ChangeStateTo(KNXIP_STATE_FOUND_GW);
                emit Notify(Common::NOTIFY_KNX_SEARCH_RESULT, notifydata);
                m_dataTimeout.stop();
            }
            if (serviceType == KNXIP_DESCRIPTION_RESP) {
                ChangeStateTo(KNXIP_STATE_FOUND_GW);

                QByteArray descr(&datagram.data()[dataStartPos+24], 20);
                QString knxipDescr(descr);
                QString notifydata = "descr=" + knxipDescr;

                emit Notify(Common::NOTIFY_KNX_DESCR_RESULT, notifydata);
                m_dataTimeout.stop();
            }
            else if (serviceType == KNXIP_CONNECT_RESP) {

                //qDebug() << "Connection resp: " << QString::number(datagram.data()[dataStartPos+1]);
                if (datagram.data()[dataStartPos+1] == KNXIP_ERR_NO_ERROR) {
                    m_knxipStatus.commChannelId = datagram.data()[dataStartPos];
                    m_knxipStatus.lastChannel = m_knxipStatus.commChannelId;
                    m_knxipStatus.clientSeqCntr = 255;
                    m_knxipStatus.serverSeqCntr = 255;
                    m_knxipStatus.state = KNXIP_STATE_CONNECTED;
                    m_knxipStatus.cmdState = CMD_STATE_IDLE;
                    m_knxipStatus.timeout.setHMS(0,0,0,0);

                    Hpai server((unsigned char*)&datagram.data()[dataStartPos+2],
                                datagram.size()-(dataStartPos+2));

                    m_knxipStatus.gwDataPort = server.GetPort();
                    //qDebug() << "[KnxGateway::Connect]: Connected to data port: " << m_knxipStatus.gwDataPort;

                    InitSlots();
                    m_heartBeat.start(); m_heartBeatAck = true;
                    ChangeStateTo(KNXIP_STATE_CONNECTED);
                    m_dataTimeout.stop();
                    m_sendTimer.start();
                }
                else if (datagram.data()[dataStartPos+1] == KNXIP_ERR_NO_MORE_CONNECTIONS ){
                    //qDebug() << "No more connections!";
                    emit Msg(Common::MSG_TYPE_ERROR, tr("[KnxGateway::Connect]: No more connections are available. Retrying..."));
                    //Get last used channel that may be not properly closed
                    if (m_knxipStatus.lastChannel != 0) {
                        //qDebug() << "Last channel: " << m_knxipStatus.lastChannel;
                        Disconnect(m_knxipStatus.lastChannel);
                    }
                    QMutex dummy;
                    dummy.lock();
                    QWaitCondition waitCondition;
                    waitCondition.wait(&dummy, 2000);
                    dummy.unlock();
                    m_dataTimeout.stop();
                    m_sendTimer.stop();
                }
            }
            else if (serviceType == KNXIP_DISCONNECT_RESP) {
                ChangeStateTo(KNXIP_STATE_DISCONNECTED);
                m_dataTimeout.stop();
                m_sendTimer.stop();
            }
            else if (serviceType == KNXIP_CONNECTION_STATE_RESP) {
                if (datagram.data()[dataStartPos+1] == KNXIP_ERR_NO_ERROR) {
                    m_heartBeatAck = true;
                    //qDebug() << "[KnxGateway::UdpThread]: Got Heartbeat resp";
                }
            }
        } //datastart pos
    }
}





void KnxGateway::onUdpData()
{
    while (m_udpData.hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_udpData.pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        unsigned int serviceType = 0;

        m_udpData.readDatagram(datagram.data(), datagram.size(),
                                &sender, &senderPort);

        int dataStartPos = ValidateData(datagram.data(), datagram.size(), &serviceType);

        if (dataStartPos >= 0) {
            int seqNum = datagram.data()[dataStartPos+2];
            //Control services
            if (serviceType == KNXIP_TUNNELING_REQ) {
                m_knxipStatus.serverSeqCntr = GetNextServerSeqNum();
                if (seqNum != m_knxipStatus.serverSeqCntr) {
//                    qDebug() << "[KnxGateway::onUdpData] seq error. inc: "
//                             << (int) seqNum
//                             << ", int: " << m_knxipStatus.serverSeqCntr;
                    m_knxipStatus.error = KNXIP_ERR_WRONG_SEQ_NUMBER;
                    ChangeStateTo(KNXIP_STATE_ERROR);
                }

                cEMI cemi((unsigned char*) &datagram.data()[dataStartPos+4],
                          datagram.size() - (dataStartPos+4));

                if (cemi.cemi.l_data == cEMI::L_DATA_CON) {	//confirmation that server sent the packet
                    //
                }
                else if (cemi.cemi.l_data == cEMI::L_DATA_IND) {
                    //Store indication to database
                    cemi.cemi.data[1] &= 0x0f;
                    QString tmpGroupAddr = cemi.groupAddr;
                    QString tmpData = Common::ByteValueToString(cemi.cemi.data+1, (int)cemi.cemi.dataLen);

                    QString knxEvt = "EVENT,KNX,DB:UDP,"+tmpGroupAddr+","+tmpData;
                    emit DataFromKnx(knxEvt);

                    qDebug() << "[KnxGateway::onUdpData] " << knxEvt;
                }

                qDebug() << "Sending ACK to: " << m_knxipStatus.gwDataPort << ", l_data: " << cemi.cemi.l_data;
                // Send ACK
                char buffer[KNXIP_DATA_BUFFER];

                int len = GetServiceHeader(KNXIP_TUNNELING_ACK, &buffer[0]);
                buffer[6] = 4;
                buffer[7] = m_knxipStatus.commChannelId;
                buffer[8] = m_knxipStatus.serverSeqCntr;
                buffer[9] = KNXIP_ERR_NO_ERROR;

                m_udpData.writeDatagram((const char*)buffer, len,
                                     QHostAddress(m_knxipStatus.gwip), m_knxipStatus.gwDataPort);

            }
            else if (serviceType == KNXIP_TUNNELING_ACK) {
//                qDebug() << "ACKED: " << seqNum;
                m_dataTimeout.stop();
                for(int i=0; i<NUM_OF_CMDS; i++) {
                    if (m_cmdPool[i].sequense == seqNum) {
//                        qDebug() << "TUNNELING ACKED: " << seqNum;
                        ReleaseSlot(i);
                        break;
                    }
                }
                //Check for other packets to send
                //SendNextData();

            }   //~: serviceType == KNXIP_TUNNELING_ACK

        }   //:~ Valid packet (dataStartPos >= 0)
    }   //:~ pending packets
}


void KnxGateway::SendNextData()
{
    int next = GetNextWaitSlot();
    if (next >= 0) {

        char buffer[KNXIP_DATA_BUFFER];

        buffer[6] = 4;
        buffer[7] = m_knxipStatus.commChannelId;
        buffer[9] = KNXIP_ERR_NO_ERROR;

        int len = GetServiceHeader(KNXIP_TUNNELING_REQ, &buffer[0]) + 4;

        buffer[8] = GetNextClientSeqNum();

        len += m_cmdPool[next].cemi->FillBuffer((unsigned char*)&buffer[10]);	//Fill buffer with cEMI data

        m_cmdPool[next].state = CMD_STATE_WAIT_ACK;

        //Write total packet length
        buffer[4] = static_cast<unsigned char>(len >> 8);
        buffer[5] = static_cast<unsigned char>(len & 0xFF);

        m_udpData.writeDatagram((const char*)buffer, len,
                           QHostAddress(m_knxipStatus.gwip), m_knxipStatus.gwDataPort);
        m_dataRetries = 0;
        m_dataTimeout.start();
    }
}


void KnxGateway::onDataTimeout()
{
    m_dataTimeout.stop();
    Msg(Common::MSG_TYPE_ERROR, tr("Command timeout."));
    if (m_dataRetries++ >= 3) {
        //Try to reconnect
        Disconnect();
        Connect();
        m_dataRetries = 0;
    }
}

void KnxGateway::onSendTimer()
{
    m_sendTimer.stop();
    SendNextData();
    m_sendTimer.start();
}


void KnxGateway::onHeartBeat()
{
    char buffer[20];

    if (m_heartBeatAck == false) {
        //No connection
        emit Msg(Common::MSG_TYPE_ERROR, tr("Heartbeat timeout."));
        Disconnect();
        return;
    }

    quint64 len = GetServiceHeader(KNXIP_CONNECTION_STATE_REQ, &buffer[0]);

    buffer[6] = m_knxipStatus.commChannelId;
    buffer[7] = 0;

    QString localip = m_interface.ip().toString();
    Hpai hpai(localip,
              m_client.localControlPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);
    hpai.GetHpaiData((unsigned char*) &buffer[8]);

    m_udpControl.writeDatagram((const char*)buffer, len,
                               QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);
    m_heartBeatAck = false;
//    qDebug() << "[KnxGateway::run] Heartbeat";
}


void KnxGateway::onSendData(QString groupAddr, QString data, cEMI::en_cemiAction action)
{

    if (m_knxipStatus.state == KNXIP_STATE_CONNECTED) {
        if (groupAddr.isEmpty()) return;
        cEMI cemi(groupAddr, data, action);
        AddToSlot(action, &cemi.cemi);
        //SendNextData();
        qDebug() << "[KnxGateway::onSendData] ga: " << groupAddr << ", val: " << data << ", act: " << ((action == 0) ? "R" : "W");
    }
    else {
        Msg(Common::MSG_TYPE_ERROR, tr("No connection with gateway"));
    }
}


KnxGateway::en_knxGatewayError KnxGateway::GetError()
{
    return(m_knxipStatus.error);
}


void KnxGateway::ChangeStateTo(en_knxGatewayState state)
{
    m_knxipStatus.state = state;
    emit KnxIpState(state);
}


int KnxGateway::GetServiceHeader(unsigned int service, char * data)
{
    tp_knxipHeader knxipHeader;

    knxipHeader.headerSize = KNXIP_HEADER_SIZE;
    knxipHeader.protocolVersion = KNXIP_VERSION;
    knxipHeader.service = (unsigned char)(service & 0xFF);
    knxipHeader.service <<= 8;
    knxipHeader.service += (unsigned char)(service >> 8);

    int len = 0;
    if (service == KNXIP_SEARCH_REQ) {
        len = 14;
    }
    else if (service == KNXIP_DESCRIPTION_REQ) {
        len = 26;
    }
    else if (service == KNXIP_CONNECT_REQ) {
        len = sizeof(tp_knxipHeader) + sizeof(tp_HPAI) + sizeof(tp_HPAI) + 4;
    }
    else if (service == KNXIP_CONNECTION_STATE_REQ) {
        len = sizeof(tp_knxipHeader) + sizeof(tp_HPAI) + 2;
    }
    else if (service == KNXIP_DISCONNECT_REQ) {
        len = sizeof(tp_knxipHeader) + sizeof(tp_HPAI) + sizeof(tp_HPAI) + 4;
    }
    else if (service == KNXIP_TUNNELING_ACK) {
        len = sizeof(tp_knxipHeader) + 4;
    }
    else if (service == KNXIP_TUNNELING_REQ) {
        len = sizeof(tp_knxipHeader);	//+ cEMI length
    }

    knxipHeader.svrDataLen = (unsigned char)(len);
    knxipHeader.svrDataLen <<= 8;
    knxipHeader.svrDataLen += (unsigned char)(len >> 8);

    if (data != NULL)
        memcpy(data, (unsigned char*)&knxipHeader, sizeof(tp_knxipHeader));

    return(len);
}


int KnxGateway::ValidateData(const char * data, int datalen, unsigned int * serviceType)
{
    int ret = -1;	//by default return error

    for (int i=0; i<datalen; i++) {
        if ( (data[i] == KNXIP_HEADER_SIZE) && (data[i+1] == KNXIP_VERSION)) {
            //check data length
            int len = data[4];
            len <<= 8;
            len += data[5];
            if (len == (datalen - i)) {
                //valid data found
                *serviceType = data[i+2];
                *serviceType <<= 8;
                *serviceType += data[i+3];

                //return the position of real data
                ret = i+6;
            }

        }
    }
    return(ret);
}


unsigned char KnxGateway::GetNextServerSeqNum(void)
{
    if ( m_knxipStatus.serverSeqCntr == 255) {
            m_knxipStatus.serverSeqCntr = 0;
    }
    else ++m_knxipStatus.serverSeqCntr;
    return(m_knxipStatus.serverSeqCntr);
}


unsigned char KnxGateway::GetNextClientSeqNum(void)
{
    if ( m_knxipStatus.clientSeqCntr == 255) {
            m_knxipStatus.clientSeqCntr = 0;
    }
    else ++m_knxipStatus.clientSeqCntr;
    return(m_knxipStatus.clientSeqCntr);
}


void KnxGateway::InitSlots(void)
{
    for(int i=0; i<NUM_OF_CMDS; i++) {
        m_cmdPool[i].slotId = i;
        m_cmdPool[i].sequense = -1;
        m_cmdPool[i].state = CMD_STATE_IDLE;
        m_cmdPool[i].cmdType = cEMI::CEMI_ACTION_WRITE;
        m_cmdPool[i].cemi = new cEMI();
    }
}


int KnxGateway::GetNextFreeSlot(void)
{
    int index = -1;
    for(int i=0; i<NUM_OF_CMDS; i++) {
        if (m_cmdPool[i].state == CMD_STATE_IDLE) {
            index = i;
            break;
        }
    }
    //qDebug() << "[KnxGateway::GetNextFreeSlot] index= " + QString::number(index);
    return(index);
}


int KnxGateway::AddToSlot(cEMI::en_cemiAction action, cEMI::tp_cEMI * cemiData)
{
    int nextSlot;
    if ( (nextSlot = GetNextFreeSlot()) >= 0 ) {
        m_cmdPool[nextSlot].cmdType = action;
        m_cmdPool[nextSlot].cemi->RenewcEMI(cemiData);
        m_cmdPool[nextSlot].state = CMD_STATE_WAIT;
    }
    return(nextSlot);
}


int KnxGateway::GetNextWaitSlot(void)
{
    int index = -1;
    m_cmdMutex.lock();

    for(int i=0; i<NUM_OF_CMDS; i++) {
        if (m_cmdPool[i].state == CMD_STATE_WAIT) {
            index = i;
            break;
        }
    }
    m_cmdMutex.unlock();

    return(index);
}


void KnxGateway::ReleaseSlot(int slotId)
{
    m_cmdMutex.lock();
    m_cmdPool[slotId].state = CMD_STATE_IDLE;
    m_cmdPool[slotId].cmdType = cEMI::CEMI_ACTION_WRITE;
    m_cmdPool[slotId].sequense = -1;
    m_cmdMutex.unlock();
}

