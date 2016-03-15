#ifndef PDXALARM_H_
#define PDXALARM_H_

#include <QtCore>
#include <QObject>
#include "../QtKnxModule/gidt_module.h"

class PdxAlarm : public QObject 
{
	Q_OBJECT
	typedef struct {
		QString groupAddr;	//group Addr
		QString alarmCmd[2];	//cmd for value 0
		int delay[2];			//delay for value 0
		int cntr[2];			//delay for value 0
		int lastsent;		//0: value 0 was sent last, 1: value 1 was sent last
		bool sent[2];			//is value 0 sent?
		int sendAlways;
		int cancelOther;	//0: the commands can't cancel each other, 1: commands can cancel each other
	} tp_cmd;

public:
	PdxAlarm(QString &iniFile, GidtModule *mod);
	//~PdxAlarm();

private:
	GidtModule * m_mod;				//pointer to module
	QList<tp_cmd> m_cmd;
	QByteArray m_buffer;
	QTimer * m_cmdTimer;
	QString m_destination;
	QString m_inifile;

	void AddLog(QString msg);
	void LoadIni(QString iniFile);
	QStringList LoadAlarmValues(QString iniFile);
	void SendCommand(QString cmd);
	QString GetCommandToSend(QString cmd);
	int GetCommandToSendByIndex(QString &cmd, tp_cmd &tmpCmd, int index);
	void CheckDelay(int index, int boolIndex);

signals:
	void Output(QString,uint,uint);

public slots:
	void Input(QString);
	void AlrmInput(QByteArray);
	void CmdTimer(void);
};

#endif //ALARM_H_
