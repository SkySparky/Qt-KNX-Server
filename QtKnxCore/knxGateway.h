/*
 * knxGateway.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef KNXGATEWAY_H_
#define KNXGATEWAY_H_

#include <QtCore>
#include <QObject>
#include <QtNetwork>
#include <QMutex>
#include "cemi.h"
#include "hpai.h"
#include "../KnxCommon/common.h"
#include "ModuleDB.h"

#define NUM_OF_CMDS		100
#define WATCHDOG_TIME 90 //in secs, watchdog for keep alive the knxip connection

#define ERR_SEARCH_BIND     -1
#define ERR_SEARCH_WRITE    -2
#define ERR_SEARCH_WRONG_SERVICE -3
#define ERR_SEARCH_NO_RESP -4

#define ERR_CONTROL_BIND     -1
#define ERR_CONTROL_WRITE    -2
#define ERR_CONTROL_WRONG_SERVICE -3
#define ERR_CONTROL_NO_RESP -4
#define ERR_CONTROL_NO_SLOTS -5

class KnxGateway : public QObject {
	Q_OBJECT

public:

    typedef enum {
        KNXIP_STATE_ERROR,
        KNXIP_STATE_SEARCHING,		/*!< Server is searching for gateways on the network */
        KNXIP_STATE_IDENTIFY,
        KNXIP_STATE_FOUND_GW,
        KNXIP_STATE_CONNECTING,		/*!< Server is trying to connect on a gateway */
        KNXIP_STATE_CONNECTED,		/*!< Server is connected on a gateway */
        KNXIP_STATE_DISCONNECTING,	/*!< Server is disconnecting from a gateway */
        KNXIP_STATE_DISCONNECTED	/*!< Disconnected */
    } en_knxGatewayState;

    typedef enum {
        KNXIP_ERR_NONE,
        KNXIP_ERR_WRONG_SEQ_NUMBER
    } en_knxGatewayError;

    KnxGateway(QString iniFile);
    int Search();
    int Identify(QString ip = "");
    int Connect();
    void Disconnect(int channel = -1);
    bool IsConnected();
    KnxGateway::en_knxGatewayError GetError();

public slots:
    void onUdpControl();
    void onUdpData();
    void onHeartBeat();
    void onDataTimeout();
    void Input(QString data);
	void AllQuit();

signals:
	void Output(QString evtData);
	void error(int socketError, const QString &message);
	void Log(QString logString);
    void KnxIpState(KnxGateway::en_knxGatewayState state);
    void Notify(int notifyType, QString notifyData);

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



#pragma pack(push, 8)
	typedef struct {
		unsigned char   headerSize:8;         /*!< Header size */
		unsigned char   protocolVersion:8;    /*!< KNX/IP protocol version */
		unsigned short  service:16;           /*!< Service type */
		unsigned short  svrDataLen:16;        /*!< Service data length */
	} tp_knxipHeader;
#pragma pack(pop)

    typedef struct {
        bool			sendDateTime;
        int				sendDateTimePeriod;
        QString			dateGroupAddr;
        QString			timeGroupAddr;
    } tp_datetimeData;

    typedef struct {
        QString			dbName;
        QString			dbHostName;
        QString			dbUserName;
        QString			dbPassword;
    } tp_dbData;

	typedef struct {
        QNetworkAddressEntry interface;
		QString			localIp;
        quint16         localControlPort;
        quint16         localDataPort;
        tp_datetimeData dateTime;
        tp_dbData       db;
    } tp_clientData;

	typedef struct {
        QString         gwip;
        quint16			gwControlPort;
        quint16			gwDataPort;
        unsigned char	lastChannel;
		unsigned char	commChannelId;	/*!< Communication channel ID */
		unsigned char	serverSeqCntr;	/*!< Current Server's sequence counter */
		unsigned char	clientSeqCntr;	/*!< Current Client's sequence counter */
		cmdState_t		cmdState;
		QTime			timeout;
		en_knxGatewayState state;		/*!< Server's <-> knx/ip gateway connection state */
        en_knxGatewayError error;
	} tp_knxGateway;

	typedef struct {
		int				slotId;		/*!< Keeps the command slot id */
		int				sequense;	/*!< Keeps the slot's sequence number */
        cmdState_t 		state;		/*!< keeps the command state */
		cEMI			*cemi;		/*!< Command's data */
	} cmd_t;

    QString			m_iniFile;
    QUdpSocket      m_udpControl;
    QUdpSocket      m_udpData;
    tp_clientData   m_clientData;				/*!< Server's local IP */
    tp_knxGateway 	m_knxipStatus;			/*!< The connected gateway's status */

	QMutex			m_cmdMutex;				/*!< Mutex for locking the cmdWaiting */
    QMutex			m_seqNumMutex;			/*!< Mutex for locking the local sequence number */
    cmd_t			m_cmdPool[NUM_OF_CMDS];
    QHash<QString,int> m_groupAddr;

    QTimer          m_heartBeat;
    bool            m_heartBeatAck;
    QTimer          m_dataTimeout;
    int             m_dataRetries;

    void            ChangeStateTo(KnxGateway::en_knxGatewayState state);

    int 			Send(cEMI::en_cemiAction cmdType, unsigned int groupAddr = 0, unsigned char * data = NULL, size_t dataLen = 0);
	int 			SendKnxTime(unsigned int groupAddr);
	int 			SendKnxDate(unsigned int groupAddr);
    void            SendNextData();

    void            UpdateGroupAddresses();
	void 			InitSlots(void);
	int 			GetNextFreeSlot(void);
    int 			AddToSlot(cEMI::tp_cEMI * cemiData);
	int 			GetNextWaitSlot(void);
	void 			ReleaseSlot(int slotId);
	unsigned char	GetNextServerSeqNum(void);
    unsigned char	GetNextClientSeqNum(void);
    int				GetServiceHeader(unsigned int service, char * data);
    int				ValidateData(const char * data, int datalen, unsigned int * serviceType);
    void			AddLog(QString logMsg);
    QNetworkAddressEntry GetNetworkInterface();
};
#endif /* KNXGATEWAY_H_ */
