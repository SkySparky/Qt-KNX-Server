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

#define KNXIP_DEFAULT_UDP_PORT      4551

#define KNXIP_WATCHDOG_TIMER        5   //seconds

#define KNXIP_DATA_BUFFER	300


#include "knxGateway.h"

KnxGateway::KnxGateway(QString iniFile) : m_iniFile(iniFile)
{
	//Read ini file
	QSettings settings(m_iniFile, QSettings::IniFormat);
    bool ok;
    m_knxipStatus.gwip = settings.value("Gateway/gwIp").toString();
    m_knxipStatus.lastChannel = settings.value("Gateway/lastChannel").toInt(&ok);

    m_clientData.interface = GetNetworkInterface();
    m_clientData.localIp = m_clientData.interface.ip().toString();

	QString tmpStr = settings.value("Gateway/sendDateTime").toString();

    m_clientData.db.dbName = settings.value("Database/dbName").toString();
    m_clientData.db.dbHostName = settings.value("Database/dbServer").toString();
    m_clientData.db.dbUserName = settings.value("Database/dbUser").toString();
    m_clientData.db.dbPassword = settings.value("Database/dbPassword").toString();

	if (tmpStr == "yes") {
        m_clientData.dateTime.sendDateTime = true;
        m_clientData.dateTime.sendDateTimePeriod = settings.value("Gateway/sendDateTimePeriod").toInt(&ok);
        m_clientData.dateTime.dateGroupAddr = settings.value("Gateway/dateGroupAddr").toString();
        m_clientData.dateTime.timeGroupAddr = settings.value("Gateway/timeGroupAddr").toString();
	}
	else {
        m_clientData.dateTime.sendDateTime = false;
        m_clientData.dateTime.sendDateTimePeriod = 0;
        m_clientData.dateTime.dateGroupAddr.clear();
        m_clientData.dateTime.timeGroupAddr.clear();
	}

    //Init timers
    //
    m_heartBeat.setInterval(60000);
    QObject::connect(&m_heartBeat, SIGNAL(timeout()), this, SLOT(onHeartBeat()));

    m_dataTimeout.setInterval(2000);
    QObject::connect(&m_dataTimeout, SIGNAL(timeout()), this, SLOT(onDataTimeout()));

    //Create control socket
    //
    if (!m_udpControl.bind()) {
        ChangeStateTo(KNXIP_STATE_ERROR);
        AddLog(tr("[KnxGateway::Control] bind err: ") + m_udpControl.errorString());
    }
    else {
        m_clientData.localControlPort = m_udpControl.localPort();
        ChangeStateTo(KNXIP_STATE_DISCONNECTED);
    }
    //Create DATA socket
    //
    if (!m_udpData.bind()) {
        ChangeStateTo(KNXIP_STATE_ERROR);
        AddLog(tr("[KnxGateway::Data] bind err: ") + m_udpControl.errorString());
    }
    else
        m_clientData.localDataPort = m_udpData.localPort();

}

void KnxGateway::ChangeStateTo(en_knxGatewayState state)
{
    m_knxipStatus.state = state;
    emit KnxIpState(state);
}

void KnxGateway::AddLog(QString logMsg)
{
	emit Log("[KnxGW::" + logMsg);
}

bool KnxGateway::IsConnected(void)
{
    return(m_knxipStatus.state == KNXIP_STATE_CONNECTED);
}

void KnxGateway::AllQuit() 
{
    Disconnect();
	m_knxipStatus.state = KNXIP_STATE_DISCONNECTING;
}

int KnxGateway::Search()
{
    char buffer[KNXIP_DATA_BUFFER];

    size_t headerLen = GetServiceHeader(KNXIP_SEARCH_REQ, &buffer[0]);

    Hpai hpai(m_clientData.localIp, m_clientData.localControlPort, HPAI_IP_PROTOCOL_IPV4_UDP);
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
        localIP = m_clientData.localIp;
    else
        localIP = ip;

    Hpai hpai(localIP, m_clientData.localControlPort, HPAI_IP_PROTOCOL_IPV4_UDP);
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
    Hpai hpai_control(m_clientData.localIp,
              m_clientData.localControlPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);
    Hpai hpai_data(m_clientData.localIp,
              m_clientData.localDataPort,
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
    //Create packet header
    char buffer[KNXIP_DATA_BUFFER];

    //Prepare disconnect data
    int dataLen = GetServiceHeader(KNXIP_DISCONNECT_REQ, &buffer[0]);
    if (channel < 0)
        buffer[6] = m_knxipStatus.commChannelId;
    else
        buffer[6] = (unsigned char) (channel & 0xFF);
    buffer[7] = 0;
    Hpai hpai(m_clientData.localIp,
              m_clientData.localDataPort,
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

                    //Save last channel
                    QSettings settings(m_iniFile, QSettings::IniFormat);
                    settings.setValue("Gateway/lastChannel", QString::number(m_knxipStatus.lastChannel));
                    settings.sync();

                    //Initialize slots
                    InitSlots();
                    m_heartBeat.start(); m_heartBeatAck = true;
                    ChangeStateTo(KNXIP_STATE_CONNECTED);
                    m_dataTimeout.stop();

                    //Read all addresses from db and read from bus
                    //
                    UpdateGroupAddresses();
                }
                else if (datagram.data()[dataStartPos+1] == KNXIP_ERR_NO_MORE_CONNECTIONS ){
                    //qDebug() << "No more connections!";
                    AddLog(tr("[KnxGateway::Connect]: No more connections are available. Retrying..."));
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
                }
            }
            else if (serviceType == KNXIP_DISCONNECT_RESP) {
                ChangeStateTo(KNXIP_STATE_DISCONNECTED);
                m_dataTimeout.stop();
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
                    for(int i = 0; i < NUM_OF_CMDS; i++) {
                        if ( (m_cmdPool[i].cemi->cemi.destAddr == cemi.cemi.destAddr) &&
                                (m_cmdPool[i].cemi->cemi.data[1] == cemi.cemi.data[1]) ) {
                            m_cmdPool[i].state = CMD_STATE_ACK_CONF;
                            ReleaseSlot(m_cmdPool[i].slotId);
                            m_knxipStatus.cmdState = CMD_STATE_IDLE;
                        }
                    }
                }
                else if (cemi.cemi.l_data == cEMI::L_DATA_IND) {
                    //Store indication to database
                    cemi.cemi.data[1] &= 0x0f;
                    QString tmpGroupAddr = cemi.groupAddr;
                    QString tmpData = Common::ByteValueToString(cemi.cemi.data+1, (int)cemi.cemi.dataLen);

                    QString knxEvt = "EVENT,KNX,DB:UDP,"+tmpGroupAddr+","+tmpData;
                    emit Output(knxEvt);

//                    qDebug() << "[KnxGateway::onUdpData] " << knxEvt;
                }

                //qDebug() << "Sending ACK to: " << m_knxipStatus.gwDataPort;
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
                if (seqNum != m_knxipStatus.clientSeqCntr) {
                    if ( abs(m_knxipStatus.clientSeqCntr - 1) > 1) {
                        qDebug() << "[KnxGateway::UdpThread] False ack sequence number." << seqNum << ", " << m_knxipStatus.clientSeqCntr;
                        m_knxipStatus.state = KNXIP_STATE_CONNECTING;
                    }
                }
                for(int i=0; i<NUM_OF_CMDS; i++) {
                    if (m_cmdPool[i].sequense == seqNum) {
//                        qDebug() << "TUNNELING ACKED: " << seqNum;
                        ReleaseSlot(i);
                        break;
                    }
                }
                //Check for other packets to send
                SendNextData();

            }   //~: serviceType == KNXIP_TUNNELING_ACK

        }   //:~ Valid packet (dataStartPos >= 0)
    }   //:~ pending packets
}


void KnxGateway::onDataTimeout()
{
    m_dataTimeout.stop();
    AddLog(tr("Command timeout."));
    if (m_dataRetries++ >= 3) {
        //Try to reconnect
        Disconnect();
        Connect();
        m_dataRetries = 0;
    }
}


void KnxGateway::onHeartBeat()
{
    char buffer[20];

    if (m_heartBeatAck == false) {
        //No connection
        AddLog(tr("Heartbeat timeout."));
        Disconnect();
        return;
    }

    quint64 len = GetServiceHeader(KNXIP_CONNECTION_STATE_REQ, &buffer[0]);

    buffer[6] = m_knxipStatus.commChannelId;
    buffer[7] = 0;

    Hpai hpai(m_clientData.localIp,
              m_clientData.localControlPort,
              HPAI_IP_PROTOCOL_IPV4_UDP);
    hpai.GetHpaiData((unsigned char*) &buffer[8]);

    m_udpControl.writeDatagram((const char*)buffer, len,
                               QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);
    m_heartBeatAck = false;

}



void KnxGateway::UpdateGroupAddresses()
{
//    //Update all group addresses
//    ModuleDB dbmod(m_clientData.db.dbName, m_clientData.db.dbHostName,
//                   m_clientData.db.dbUserName, m_clientData.db.dbPassword,
//                   m_clientData.db.);

//    QSqlQuery query = dbmod.ExecuteQuery("SELECT fld_groupAddrStatus FROM tbl_knx");
//    unsigned int ga;
//    unsigned char data[255];
//    int dataLen;
//    while (query.next()) {
//        QSqlRecord rec = query.record();
//        ga = query.value(rec.indexOf("fld_groupAddrStatus")).toInt();
//        if (ga > 0) {
//            Send(cEMI::CEMI_ACTION_READ, ga, data, dataLen);
//        }
//    };
}


void KnxGateway::Input(QString data)
{
	qDebug() << "[KnxGateway::Input] dbData: " << data;
	QT_TRY {
        cEMI::en_cemiAction cmdAction;
        //Get paranon-clmeters
        QString tmpStr = Common::GetParam(data, Common::PARAM_CMD);
		if (tmpStr.isEmpty()) return;

        if (tmpStr == "WRITE") cmdAction = cEMI::CEMI_ACTION_WRITE;
        else if (tmpStr == "READ") cmdAction = cEMI::CEMI_ACTION_READ;
		else return;

        tmpStr = Common::GetParam(data, Common::PARAM_DATA_START);
		if (tmpStr.isEmpty()) return;
		unsigned int i_groupAddr = Common::GroupAddrToInt(tmpStr);

        tmpStr = Common::GetParam(data, Common::PARAM_DATA_START + 1);
		unsigned char c_data[255];
		int dataLen = Common::StrValueToBytes(tmpStr, c_data);
		Send(cmdAction, i_groupAddr, c_data, dataLen);
	}
	QT_CATCH(...) {
		Log("Input] GetParam error with: " + data);
	}
}


int KnxGateway::Send(cEMI::en_cemiAction action, unsigned int groupAddr, unsigned char * data, size_t dataLen)
{
	int ret = -1;
	cEMI cemi(action, groupAddr, data, dataLen);

    if (AddToSlot(&cemi.cemi) >= 0) {
		ret = 0;
	}
	else {
		qDebug() << "[KnxGateway::Send] Failed to send cmd...";
	}

	return(ret);
}

void KnxGateway::SendNextData()
{
	int nextSlot = GetNextWaitSlot();
	if ( nextSlot >= 0 ) {
		size_t len;
        char buffer[KNXIP_DATA_BUFFER];

		buffer[6] = 4;
		buffer[7] = m_knxipStatus.commChannelId;
		buffer[9] = KNXIP_ERR_NO_ERROR;

        if ( (m_cmdPool[nextSlot].cemi->cemi.action == cEMI::CEMI_ACTION_READ)
             || (m_cmdPool[nextSlot].cemi->cemi.action == cEMI::CEMI_ACTION_WRITE) ){

			m_cmdPool[nextSlot].sequense = (int)GetNextClientSeqNum();	//keep sequence number to track the ACK in RcvKnxipData()
			buffer[8] = m_cmdPool[nextSlot].sequense;
			len = GetServiceHeader(KNXIP_TUNNELING_REQ, &buffer[0]) + 4;

			//cmdPool[nextSlot].cemi->DebugPrintCEMI();
            len += m_cmdPool[nextSlot].cemi->FillBuffer((unsigned char*)&buffer[10]);	//Fill buffer with cEMI data


			//Write total packet length
			buffer[4] = static_cast<unsigned char>(len >> 8);
			buffer[5] = static_cast<unsigned char>(len & 0xFF);

			m_cmdPool[nextSlot].state = CMD_STATE_WAIT_ACK;

			m_knxipStatus.cmdState = CMD_STATE_WAIT_CONF;
			m_knxipStatus.timeout.start();

            quint64 dataSent = m_udpData.writeDatagram((const char*)buffer, len, QHostAddress(m_knxipStatus.gwip), KNXIP_EIBNET_MULTICAST_PORT);
			qDebug() << "[KnxGateway::SendKnxipData] Sending(" << dataSent << "):" << m_cmdPool[nextSlot].cemi->groupAddr;
		}
	}
}

int KnxGateway::SendKnxDate(unsigned int groupAddr)
{
	QDate date = QDate::currentDate();
    cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE;
	int retval = -1;
	unsigned char data[4];

	data[0] = 0;
	data[1] = date.day();
	data[2] = date.month();
	data[3] = date.year() - 2000;

	cEMI cemi(action, groupAddr, data, 4);

    if (AddToSlot(&cemi.cemi) >= 0) {
		retval = 0;
		qDebug() << "[KnxGateway::SendKnxDate] Date sent.";
	}
	return(retval);
}

int KnxGateway::SendKnxTime(unsigned int groupAddr)
{
	QTime time = QTime::currentTime();
	QDate date = QDate::currentDate();
	int retval = -1;
	unsigned char data[4];

    cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE;

	data[0] = 0;
	data[1] = (unsigned char)(date.dayOfWeek() << 5);
	data[1] |= time.hour();
	data[2] = time.minute();
	data[3] = time.second();

	cEMI cemi(action, groupAddr, data, 4);

    if (AddToSlot(&cemi.cemi) >= 0) {
		retval = 0;
		qDebug() << "[KnxGateway::SendKnxTime] Time sent.";
	}
	return(retval);
}


void KnxGateway::InitSlots(void)
{
	for(int i=0; i<NUM_OF_CMDS; i++) {
		m_cmdPool[i].slotId = i;
		m_cmdPool[i].sequense = -1;
        m_cmdPool[i].state = CMD_STATE_IDLE;
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

int KnxGateway::AddToSlot(cEMI::tp_cEMI * cemiData)
{
	int nextSlot;
    if ( (nextSlot = GetNextFreeSlot()) >= 0 ) {
		m_cmdPool[nextSlot].cemi->RenewcEMI(cemiData);
		m_cmdPool[nextSlot].state = CMD_STATE_WAIT;
	}
	return(nextSlot);
}

unsigned char KnxGateway::GetNextClientSeqNum(void)
{
	if ( m_knxipStatus.clientSeqCntr == 255) {
			m_knxipStatus.clientSeqCntr = 0;
	}
	else ++m_knxipStatus.clientSeqCntr;
	return(m_knxipStatus.clientSeqCntr);
}

unsigned char KnxGateway::GetNextServerSeqNum(void)
{
	if ( m_knxipStatus.serverSeqCntr == 255) {
			m_knxipStatus.serverSeqCntr = 0;
	}
	else ++m_knxipStatus.serverSeqCntr;
	return(m_knxipStatus.serverSeqCntr);
}

int KnxGateway::GetNextWaitSlot(void)
{
	int index = -1;
	m_cmdMutex.lock();

	for(int i=0; i<NUM_OF_CMDS; i++) {
		//TRACE(("Search slot = %d", i));
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
	m_cmdPool[slotId].sequense = -1;
	m_cmdMutex.unlock();
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
                    return entry;
                }
            }
        }
    }
    return QNetworkAddressEntry();
}
