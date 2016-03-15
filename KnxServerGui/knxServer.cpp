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


#include "knxServer.h"


KnxServer::KnxServer(QString iniString, int mode)
{
    if (mode == 0) {
        //Read ini file
        m_iniFile = iniString;
        QSettings settings(m_iniFile, QSettings::IniFormat);
        //qDebug() << settings.fileName();
        m_iniData.localIp = settings.value("KnxServer/localIp").toString();
        m_iniData.name = settings.value("KnxServer/name").toString();
    }
    else if (mode == 1) {
        m_iniData.localIp = iniString;
        m_iniData.name = "GiDT";
    }

    AddLog("[KnxServer::KnxServer]", GIDT_SERVER_INFO);

    m_eth0 = GetNetworkInterface(m_iniData.localIp);

    m_iniData.macAddr = m_eth0.hardwareAddress();


    m_iniData.localHpai = new Hpai(m_iniData.localIp,
              KNXIP_EIBNET_MULTICAST_PORT,
              HPAI_IP_PROTOCOL_IPV4_UDP);

    //Test timer
    m_timer = new QTimer(this);
        connect(m_timer, SIGNAL(timeout()), this, SLOT(onTestTimer()));
}

void KnxServer::Close()
{
    m_mcuSocket->close();
    m_mcuSocket->deleteLater();
    udpSocket->close();
    udpSocket->deleteLater();
}



void KnxServer::Bind()
{
    m_mcuSocket = new QUdpSocket(this);

    if (!m_mcuSocket->bind(KNXIP_EIBNET_MULTICAST_PORT, QUdpSocket::ShareAddress) ) {
        AddLog("[KnxServer::Bind]"," Failed to bind at multicast port");
        exit(-1);
    }
    if (!m_mcuSocket->joinMulticastGroup(QHostAddress(KNXIP_EIBNET_MULTICAST_IP),m_eth0) ) {
        AddLog("[KnxServer::Bind]", "Failed to join at multicast ip.");
        exit(-1);
    }
    connect(m_mcuSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingMulticastDatagrams()));

    udpSocket = new QUdpSocket(this);
    if (! udpSocket->bind(QHostAddress(m_iniData.localIp), KNXIP_EIBNET_MULTICAST_PORT,
                         QUdpSocket::ShareAddress) ) {
       AddLog("[KnxServer::Bind]", "Failed to bind at: " + m_iniData.localIp);
       exit(-1);
    }
    connect(udpSocket, SIGNAL(readyRead()),
            this, SLOT(processPendingDatagrams()));
    AddLog("[KnxServer::Bind]", "Bound to multicast address");
}


void KnxServer::onTestTimer()
{
    onSendDataToClients("1.1.4", "0/0/3", "80");
}


void KnxServer::onSendDataToClients(QString phyAddr, QString groupAddr, QString data)
{
    tp_knxClients client;
    for (int i=0; i<m_clients.count(); i++) {
        //Send KNXIP_DATA_BUFFER
        char buffer[KNXIP_DATA_BUFFER];

        buffer[6] = 4;   //struct length
        buffer[7] = m_clients[i].commChannelId;
        buffer[8] = m_clients[i].serverSeqCntr;
        buffer[9] = KNXIP_ERR_NO_ERROR;

        size_t len = GetServiceHeader(KNXIP_TUNNELING_REQ, &buffer[0]);

        cEMI::tp_cEMI tmpcemi;
        tmpcemi.l_data = cEMI::L_DATA_IND;
        tmpcemi.additionalInfo = 0;
        tmpcemi.ctrl1.byte = 0xbc;
        tmpcemi.ctrl2.byte = 0xe0;
        tmpcemi.srcAddr = (unsigned short)Common::PhysAddrToInt(phyAddr);
        tmpcemi.destAddr = (unsigned short)Common::GroupAddrToInt(groupAddr);


        unsigned char b_data[255];
        tmpcemi.dataLen = Common::StrValueToBytes(data, b_data);
        tmpcemi.data = b_data;

        cEMI dcemi(&tmpcemi);
        len += dcemi.FillBuffer((unsigned char*) &buffer[10]);   //fill send buffer with cemi

        //Write total packet length
        buffer[4] = static_cast<unsigned char>(len >> 8);
        buffer[5] = static_cast<unsigned char>(len & 0xFF);

        udpSocket->writeDatagram(buffer, len, QHostAddress(m_clients[i].ip),
                                 m_clients[i].dataPoint->GetPort());
    }
}

void KnxServer::processPendingMulticastDatagrams()
 {
     while( m_mcuSocket->hasPendingDatagrams() )
     {
         QHostAddress sender;
         quint16 senderPort;
         unsigned char datagram[KNXIP_DATA_BUFFER];

         quint64 dataLen = m_mcuSocket->readDatagram( (char*)datagram, KNXIP_DATA_BUFFER,
                                        &sender, &senderPort);

         unsigned int serviceType;
         int dataStartPos = ValidateData(datagram, dataLen, &serviceType);  //returns the data first index
         if ( dataStartPos >= 0) {
             if (serviceType == KNXIP_SEARCH_REQ) {
                 //respond
                 char data[100];
                 quint64 dataLen = GetServiceHeader(KNXIP_SEARCH_RESP, data);
                 udpSocket->writeDatagram(data, dataLen,
                                      sender, senderPort);

                 AddLog("[KnxServer::processPendingMulticastDatagrams]", "Search req from " + sender.toString());
             }
         }
     }
 }


void KnxServer::processPendingDatagrams()
 {

    while( udpSocket->hasPendingDatagrams() )
    {
        QHostAddress sender;
        quint16 senderPort;
        unsigned char datagram[KNXIP_DATA_BUFFER];

        quint64 datagramLen = udpSocket->readDatagram( (char*)datagram, KNXIP_DATA_BUFFER,
                            &sender, &senderPort);

        unsigned int serviceType;
        int dataStartPos = ValidateData(datagram, datagramLen, &serviceType);

        if ( dataStartPos >= 0) {
            //qDebug() << "service: " << serviceType;

            if (serviceType == KNXIP_DESCRIPTION_REQ) {
                //respond
                char data[100];
                quint64 dataLen = GetServiceHeader(KNXIP_DESCRIPTION_RESP, data);
                udpSocket->writeDatagram(data, dataLen,
                                        sender, senderPort);
            }
            else if (serviceType == KNXIP_CONNECT_REQ) {
                //add new client
                if (datagram[dataStartPos+17] == KNXIP_TUNNELLING_CONNECTION) {  //in case of new tunneling request
                    tp_knxClients client;
                    client.controlPoint = new Hpai(&datagram[dataStartPos], datagramLen);  //get hpai struct
                    client.dataPoint = new Hpai(&datagram[dataStartPos+8], datagramLen);  //get hpai struct

                    char data[100];
                    quint64 dataLen = GetServiceHeader(KNXIP_CONNECT_RESP, data);
                    data[6] = client.commChannelId = 1;
                    client.clientSeqCntr = 0;
                    client.cmdState = CMD_STATE_IDLE;
                    client.serverSeqCntr = 0;
                    client.ip = sender.toString();
                    //client.timeout = 120;
                    data[7] = KNXIP_ERR_NO_ERROR;
                    m_iniData.localHpai->GetHpaiData((unsigned char*) &data[8]);       //copy to buffer
                    data[16] = 4; data[17] = KNXIP_TUNNELLING_CONNECTION; data[18] = 0; data[19] = 0;

                    udpSocket->writeDatagram(data, dataLen,
                                            sender, client.controlPoint->GetPort());
                    //m_timer->start(1000);

                    m_clients.append(client);

                    AddLog("[KnxServer::process]" , "Connection req from: " + sender.toString());

                }

            }
            else if (serviceType == KNXIP_CONNECTION_STATE_REQ) {

                Hpai in_client(&datagram[dataStartPos+2], datagramLen);

                foreach(tp_knxClients client, m_clients) {

                    if (client.controlPoint->hpai_t.ip == in_client.hpai_t.ip) {
                        char data[100];
                        quint64 dataLen = GetServiceHeader(KNXIP_CONNECTION_STATE_RESP, data);

                        data[6] = client.commChannelId;
                        if (datagram[dataStartPos] != client.commChannelId) data[7] = KNXIP_ERR_CONNECTION_ID;
                        else data[7] = KNXIP_ERR_NO_ERROR;

                        udpSocket->writeDatagram(data, dataLen,
                                                sender, client.controlPoint->GetPort());
                        break;
                    }
                }
            }
            else if (serviceType == KNXIP_DISCONNECT_REQ) {
                Hpai in_client(&datagram[dataStartPos+2], datagramLen);
                //foreach(tp_knxClients client, m_clients) {
                tp_knxClients client;
                for (int i=0; i<m_clients.count(); i++) {

                    client = m_clients.at(i);
                    if (client.controlPoint->hpai_t.ip == in_client.hpai_t.ip) {
                        char data[100];
                        quint64 dataLen = GetServiceHeader(KNXIP_DISCONNECT_RESP, data);

                        data[6] = client.commChannelId;
                        if (datagram[dataStartPos] != client.commChannelId) data[7] = KNXIP_ERR_CONNECTION_ID;
                        else data[7] = KNXIP_ERR_NO_ERROR;

                        udpSocket->writeDatagram(data, dataLen,
                                                sender, client.controlPoint->GetPort());
                        //m_clients.removeOne(client);
                        m_clients.removeAt(i);
                        AddLog("[KnxServer::process]" , "Disconnection req from: " + sender.toString());
                        break;
                    }
                }
            }
            else if (serviceType == KNXIP_TUNNELING_ACK) {
                for (int i=0; i<m_clients.count(); i++) {
                    if (m_clients[i].ip == sender.toString()) {
                        if ( (datagram[dataStartPos+3] == KNXIP_ERR_NO_ERROR) &&
                             (datagram[dataStartPos+2] == m_clients[i].serverSeqCntr)) {    //acknowledged
                            //qDebug() << "ACKED!";
                            ++m_clients[i].serverSeqCntr;
                            break;
                        }
                    }
                }
            }
            else if (serviceType == KNXIP_TUNNELING_REQ) {

                for (int i=0; i<m_clients.count(); i++) {
                    if (m_clients[i].ip == sender.toString()) {
                        //valid channel & client

                        //ACK REQ
                        char data[100];
                        quint64 dataLen = GetServiceHeader(KNXIP_TUNNELING_ACK, data);

                        data[6] = 4;   //struct length
                        data[7] = datagram[dataStartPos+1]; // channel id
                        data[8] = m_clients[i].clientSeqCntr = datagram[dataStartPos+2]; // sequence counter
                        data[9] = KNXIP_ERR_NO_ERROR;

                        udpSocket->writeDatagram(data, dataLen,
                                                sender, m_clients[i].dataPoint->GetPort()); //ACK da REQ

                        //CONFIRM
                        dataLen = GetServiceHeader(KNXIP_TUNNELING_REQ, data);

                        data[6] = 4;   //struct length
                        data[7] = m_clients[i].commChannelId;
                        data[8] = m_clients[i].serverSeqCntr;
                        data[9] = KNXIP_ERR_NO_ERROR;

                        cEMI tmpcemi(&datagram[dataStartPos+4], datagramLen - (dataStartPos+4));
                        tmpcemi.cemi.l_data = cEMI::L_DATA_CON;
                        tmpcemi.cemi.ctrl1.byte = 0xbc;
                        tmpcemi.cemi.data = &datagram[dataStartPos+14];

                        data[5] += tmpcemi.FillBuffer((unsigned char*)&data[10]);

                        udpSocket->writeDatagram(data, datagramLen,
                                                sender, m_clients[i].dataPoint->GetPort());

                        AddLog("[KnxServer::process]" , "Tunneling req from: " + sender.toString()
                               + ", ga: " + Common::GroupAddrToStr(tmpcemi.cemi.destAddr)
                               + ", data: " + Common::ByteValueToString(tmpcemi.cemi.data, tmpcemi.cemi.dataLen));

                        QString ga = Common::GroupAddrToStr(tmpcemi.cemi.destAddr);
                        QString dt = Common::ByteValueToString(tmpcemi.cemi.data, tmpcemi.cemi.dataLen);
                        emit GatewayData(ga, dt);

                        //Send to all clients
                        tmpcemi.cemi.l_data = cEMI::L_DATA_IND;
                        tmpcemi.cemi.additionalInfo = 0;
                        tmpcemi.cemi.ctrl1.byte = 0xbc;
                        tmpcemi.cemi.ctrl2.byte = 0xe0;
                        for (int k=0; k<m_clients.count(); k++) {
                            if (k != i) {   //send to all other clients
                                data[7] = m_clients[k].commChannelId;
                                data[8] = m_clients[k].serverSeqCntr;
                                udpSocket->writeDatagram(data, datagramLen,
                                                         QHostAddress(m_clients[k].ip), m_clients[k].dataPoint->GetPort());
                            }
                        }
                        break;
                    }
                }   //:~ foreach
            }   //:~ serviceType
        }   //:~ dataStartPos
    }   //:~ while
}


int KnxServer::GetServiceHeader(unsigned int service, char * data)
{
	tp_knxipHeader knxipHeader;

    knxipHeader.headerSize = KNXIP_HEADER_SIZE;
    knxipHeader.protocolVersion = KNXIP_VERSION;
    knxipHeader.service = (unsigned char)(service & 0xFF);
    knxipHeader.service <<= 8;
    knxipHeader.service += (unsigned char)(service >> 8);

    int len = 0;
    if (service == KNXIP_SEARCH_RESP) {
        len = 76;
        //Create HPAI body
        m_iniData.localHpai->GetHpaiData((unsigned char*) &data[6]);       //copy to buffer
        GetServerDIB(&data[14]);
    }
    else if (service == KNXIP_DESCRIPTION_RESP) {
        len = 68;
        GetServerDIB(&data[6]);
    }
    else if (service == KNXIP_CONNECT_RESP) {
        len = sizeof(tp_knxipHeader) + sizeof(tp_HPAI) + 6;
    }
    else if (service == KNXIP_CONNECTION_STATE_RESP) {
        len = sizeof(tp_knxipHeader) + 2;
    }
    else if (service == KNXIP_DISCONNECT_RESP) {
        len = sizeof(tp_knxipHeader) + 2;
    }
    else if (service == KNXIP_TUNNELING_ACK) {
        len = sizeof(tp_knxipHeader) + 4;
    }
    else if (service == KNXIP_TUNNELING_REQ) {
        len = sizeof(tp_knxipHeader) + 4;	//+ cEMI length
    }

    knxipHeader.svrDataLen = (unsigned char)(len);
    knxipHeader.svrDataLen <<= 8;
    knxipHeader.svrDataLen += (unsigned char)(len >> 8);

    if (data != NULL)
        memcpy(data, (unsigned char*)&knxipHeader, sizeof(tp_knxipHeader));

    return(len);
}


int KnxServer::ValidateData(const unsigned char * data, int datalen, unsigned int * serviceType)
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


int KnxServer::StrValueToBytes(QString &data, char * value)
{
    int k = 0;
    data.remove(QChar(':'), Qt::CaseInsensitive);
    //qDebug() << "mac: " << data;
    for (int i=0; i<data.length(); i+=2) {
        value[k] = (unsigned char) data.mid(i, 2).toInt(0, 16);
        k++;
    }
    return(k);
}


QNetworkInterface KnxServer::GetNetworkInterface(QString ipAddress)
{
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(interface.flags() & QNetworkInterface::IsLoopBack)) {

            foreach(QNetworkAddressEntry entry, interface.addressEntries())
            {
                QString ip = entry.ip().toString();
                if (ip == ipAddress) {
                    return(interface);
                }
            }
        }
    }
    return QNetworkInterface();
}


//This gets the param inside the param
QString KnxServer::GetParam(QString inString, int param, QString separator)
{
    QString strResult;

    QT_TRY {
        QStringList params = inString.split(separator);
        //QString retString = params.at(param+1);
        if (params.isEmpty() == false) {
            strResult = params.at(param-1);
            QStringList splitParms = strResult.split("=");
            if (splitParms.count() == 2) {
                //QString dbParamName = splitParms[0];	//get param name
                strResult = splitParms[1];		//get param value
            }
        }
    }
    QT_CATCH(...) {
        qDebug() << "GetParam error with: " << inString;
    }
    return(strResult);
}


void KnxServer::AddLog(QString func, QString msg)
{
    //qDebug() << func << " : " << msg;
    emit Log(func, msg);
}


int KnxServer::GetServerDIB(char * buffer)
{
    //Create DIB information
    int index = 0;
    buffer[index] = 0x36;
    buffer[index+1] = 1; //description code
    buffer[index+2] = 2; // medium 02h = TP1
    buffer[index+3] = 0; // device status
    buffer[index+4] = 0x11; // physical address
    buffer[index+5] = 0xd3; //
    buffer[index+6] = 0; // project installation
    buffer[index+7] = 0;
    buffer[index+8] = 0; //serial number
    buffer[index+9] = 0xc5;
    buffer[index+10] = 7;
    buffer[index+11] = 2;
    buffer[index+12] = 2;
    buffer[index+13] = 0x1c;
    buffer[index+14] = 0;buffer[index+15] = 0;buffer[index+16] = 0;buffer[index+17] = 0;

    StrValueToBytes(m_iniData.macAddr, &buffer[index+18]);

    buffer[index+24] = 0x47;  //name
    buffer[index+25] = 0x69;
    buffer[index+26] = 0x44;
    buffer[index+27] = 0x54;
    buffer[index+28] = 0x20;
    buffer[index+29] = 0x2d;
    buffer[index+30] = 0x20;
    buffer[index+31] = 0x47;
    buffer[index+32] = 0x61;
    buffer[index+33] = 0x74;
    buffer[index+34] = 0x65;
    buffer[index+35] = 0x77;
    buffer[index+36] = 0x61;
    buffer[index+37] = 0x79;
    buffer[index+38] = 0x20;
    buffer[index+39] = 0x76;
    buffer[index+40] = 0x30;
    buffer[index+41] = 0x2e;
    buffer[index+42] = 0x30;
    buffer[index+43] = 0x31;

    for (int i=0; i<10; i++) buffer[index+44+i] = 0;

    buffer[index+54] = 0x08;
    buffer[index+55] = 0x02;
    buffer[index+56] = 0x02;
    buffer[index+57] = 0x01;
    buffer[index+58] = 0x03;
    buffer[index+59] = 0x01;
    buffer[index+60] = 0x04;
    buffer[index+61] = 0x01;

    return(62);
}
