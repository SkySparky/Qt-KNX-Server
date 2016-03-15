/*
 * knxGateway.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef KNXSERVER_H_
#define KNXSERVER_H_

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include <QMutex>
#include <QTimer>
#include "cemi.h"
#include "hpai.h"
#include "common.h"

#define NUM_OF_CMDS		100
#define WATCHDOG_TIME 90 //in secs, watchdog for keep alive the knxip connection

#define ERR_SEARCH_BIND     -1
#define ERR_SEARCH_WRITE    -2
#define ERR_SEARCH_WRONG_SERVICE -3
#define ERR_SEARCH_NO_RESP -4


#define GIDT_SERVER_INFO    "GiDT KnxGateway v0.01"

class KnxServer : public QObject {
	Q_OBJECT

public:
    KnxServer(QString iniString, int mode = 0);   //0: from ini file, from ip
    void Bind();
    void Close();

public slots:
    void processData();
    void processPendingDatagrams();
    void processPendingMulticastDatagrams();
    void onSendDataToClients(QString phyAddr, QString groupAddr, QString data);
    void onTestTimer();

signals:
    void GatewayData(QString groupAddr, QString data);
    void Log(QString func, QString msg);

private:
	typedef enum {
		CMD_STATE_IDLE,			/*!< No command is waiting */
		CMD_STATE_WAIT,			/*!< Command is waiting to be transmitted */
		CMD_STATE_WAIT_ACK,		/*!< Command is waiting for ACK from the gateway */
		CMD_STATE_WAIT_CONF,	/*!< Command is waiting for confirmation from the gateway */
		CMD_STATE_ACK_CONF,		/*!< Command is waiting to transmit ACK to confirmation */
		CMD_STATE_WAIT_RESP,	/*!< Command is waiting for response */
		CMD_STATE_ACK_RESP		/*!< Command is waiting to ACK the response */
	} cmdState_t;

	typedef enum {
		KNXIP_CMD_READ,		/*!< Read from the bus */
		KNXIP_CMD_WRITE,	/*!< Write to the bus */
		KNXIP_CMD_ACK,		/*!< Send ACK to the bus */
		KNXIP_CMD_NONE		/*!< default. Not actually used */
	} en_knxCmdType;

	typedef enum {
		KNXIP_STATE_DISCONNECTED,	/*!< Disconnected */
		KNXIP_STATE_SEARCHING,		/*!< Server is searching for gateways on the network */
		KNXIP_STATE_CONNECTING,		/*!< Server is trying to connect on a gateway */
		KNXIP_STATE_CONNECTED,		/*!< Server is connected on a gateway */
		KNXIP_STATE_DISCONNECTING	/*!< Server is disconnecting from a gateway */
	} en_knxGatewayState;

#pragma pack(push, 8)
	typedef struct {
		unsigned char   headerSize:8;         /*!< Header size */
		unsigned char   protocolVersion:8;    /*!< KNX/IP protocol version */
		unsigned short  service:16;           /*!< Service type */
		unsigned short  svrDataLen:16;        /*!< Service data length */
	} tp_knxipHeader;
#pragma pack(pop)

	typedef struct {
        QString			localIp;
        QString         name;
        QString         macAddr;
        Hpai            *localHpai;
    } tp_inidata;

    typedef struct {
        QUdpSocket      *socket;
        QString         ip;
        Hpai            *controlPoint;
        Hpai            *dataPoint;
		unsigned char	commChannelId;	/*!< Communication channel ID */
		unsigned char	serverSeqCntr;	/*!< Current Server's sequence counter */
        unsigned char	clientSeqCntr;	/*!< Current Client's sequence counter */
		QTime			timeout;
        en_knxGatewayState state;		/*!< Server's <-> knx/ip gateway connection state */
    } tp_knxClients;

	typedef struct {
		int				slotId;		/*!< Keeps the command slot id */
		int				sequense;	/*!< Keeps the slot's sequence number */
		cmdState_t 		state;		/*!< keeps the command state */
		en_knxCmdType	cmdType;	/*!< The commands type */
		cEMI			*cemi;		/*!< Command's data */
	} cmd_t;

    QList<tp_knxClients> m_clients;
    QString			m_iniFile;
    tp_inidata      m_iniData;
    QUdpSocket      *m_mcuSocket;
    QUdpSocket      *m_udpSocket;
    QByteArray      m_searchResponce;
    QNetworkInterface m_eth0;
    QTimer          *m_timer;

    int             GetServerDIB(char * buffer);
    int             StrValueToBytes(QString &data, char * value);
    QNetworkInterface GetNetworkInterface(QString ipAddress);
	QString			GetParam(QString inString, int param, QString separator = ",");
    int				GetServiceHeader(unsigned int service, char * data);
    int				ValidateData(const char * data, int datalen, unsigned int * serviceType);
    void            AddLog(QString func, QString msg);
    unsigned char   GetNextServerSeqNum(tp_knxClients & client);
    unsigned char   GetNextClientSeqNum(tp_knxClients & client);
};
#endif /* KNXSERVER_H_ */
