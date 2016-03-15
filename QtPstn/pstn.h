/*
 * knxGateway.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef PSTN_H_
#define PSTN_H_

#include <QtCore>
#include <QObject>
#include <QDateTime>
#include "../QtKnxCore/ModuleDB.h"
#include "../QtKnxModule/gidt_module.h"

class PSTN : public QObject 
{
	Q_OBJECT
		
public:
	int m_state;					//pstn modem state
	int m_prevState;				//pstn previous state
	int m_answerRings;				//number of rings from valid users to answer
	int m_answerInvalidRings;		//number of rings from invalid users to answer 
	int m_version;					//modules version
	int m_dtmfTimeout;				//timeout between two dtmf commands
	uint m_driverOut;				//device drivers output (sound card)
	QString m_voiceMenuFolder;
	QString m_voiceValue;
	QString m_unlockpin;			//pin for unlocking dtmf menu
	QString m_voiceMailFolder;		//folder to store voice mail msg
	QString m_voiceMailMsg;			//voicemail intro msg
	int m_voiceMailEnabled;			//0: voicemail disabled, 1: enabled
	QString m_dtmfMsg;				//dtmf command buffer
	QString m_msgFolder;
	int m_msgEvtTries;
	int m_msgEvtTriesCntr;
	int	m_msgEvtDelay;				//delay time before start sending a voice event in order to gather more events
	int	m_msgEvtCntr;				//cntr for m_msgEvtDelay used in timer
	QList<QString> m_msgEvtToSend;	//list of messsage wavs to send to user
	QList<QString> m_validTel;		//list of valid user tel number
	bool m_printEvents;				//debug print for w2c callback
	long m_deviceId;				//pstn modem id used in w2c
	GidtModule * m_mod;				//pointer to module


	PSTN(QString &iniFile, GidtModule *mod);
	~PSTN();
	void ResetTimestamp(void);
	void AddLog(QString msg);
	bool InitializeModem(void);
	bool GetNextAction(const QString &pstnTone, QString &wavFile, QString &command);
	QString GetDtmfString(int code);
	void SetState(int currState);
	bool PlayFile(QString &fname, long fromPos = 0);

private:
	ModuleDB * m_db;
	uint m_timestamp;
	QString m_iniFile;
	QString m_dbName;
	QString m_dbServer;
	QString m_dbUser;
	QString m_dbPassword;
	QString m_menuOpts;
	void LoadSettings(QString iniFile);
	void SetMode(int mode);
    bool StopPlay(void);

signals:
	void OutputLog(QString);

public slots:
	void Input(QString);
	void pstnHandler(void);
	void LocalTimer(void);
};


#endif //PSTN_H_
