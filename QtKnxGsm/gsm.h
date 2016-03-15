/*
 * gsm.h
 *
 *  Created on: 29 Ïêô 2010
 *      Author: Administrator
 */

#ifndef GSM_H_
#define GSM_H_

#include <QtCore>
#include <QDir>
#include <QDebug>
#include <QObject>
#include <QThread>
#include <QByteArray>
#include <QString>
#include <QList>
#include <QTimer>
#include "abstractserial.h"
#include "../QtKnxModule/gidt_module.h"

#define PARAM_SMS_TEL	1
#define PARAM_SMS_TEXT	2


typedef enum {
	SMS_TYPE_7BIT,
	SMS_TYPE_UNICODE
} sms_type_en;


typedef enum {
	STATE_UNREGISTERED,
	STATE_WAIT_REGISTRATION,
	STATE_WAIT_ATE0,
	STATE_WAIT_CMGF,			//at+cmgf=0 ,for PDU SMSs
	STATE_WAIT_DELETE_ALL_SMS,
	STATE_IDLE,
	STATE_SEND_SMS_FROM_LIST,
	STATE_WAIT_SMS_INPUT,
	STATE_SENDING_SMS,
	STATE_SMS_SENT,
	STATE_SMS_SEND_ERROR,
	STATE_READ_SMS,
	STATE_WAIT_READ_RESP
} gsmState_en;

typedef struct {
	gsmState_en state;

} gsmState_t;

typedef struct {
	QString 	smsTel;
	QString 	smsText;
	sms_type_en	smsType;	//0: for 7-bit, 1: for
	int			smsLength;
} sms_t;

class Gsm : public QThread {
	Q_OBJECT
public:

	/**
	* \brief This constructor creates an Gsm Object
	* @param[in]	watchFolder	The folder that the module watched for SMS for sending
	*/
	Gsm(GidtModule * mod, QString ComPort, QStringList smsTel);

	/**
	* Destructor
	*/
	~Gsm();

	/**
	* \brief Starts the monitor thread
	*/
	void Start(void);
	int SendSMS(QString smsText, QString smsTel = "");

protected:

	/**
	* \brief Virtual function inherited from QThread and runs the thread
	*/
	void run(void);

public slots:
	void OnTimer();
	void Input(QString incomingData);

private:

	GidtModule * m_module;
	AbstractSerial *m_port;
	gsmState_t m_state;
	int m_rcvTimeout;			/*!< Receive timeout */
	QString m_rcvBuffer;
	QString m_comport;			/*!< COM port */
	QString m_smsTel;			/*!< Default SMS telephone */
	QList<sms_t>	m_smsList;	/*!< List of outgoing SMS messages */
	QList<int>	m_inbox;
	sms_t	m_currSms;			/*!< Current sending SMS */
	int		m_readSmsIndex;
	int		m_previousState;
	//int		_currentState;
	QTimer * m_timer;
	QTime	m_watchdog;
	QString m_currPDU;
	QStringList m_validTel;

	QString Gsm::GetParam(QString inString, int param, QString separator=",");
	void SmsSendHandler(void);
	sms_t DecodePDU(QString &pduSms);
	QString EncodeToPDU(sms_t &sms); //, QString &pdu);
	QString EncodeTo7bit(QString &text);
	QString EncodeToUnicode(QString &text);
	QString SwapBytes(QString &bytes);

};


#endif /* GSM_H_ */
