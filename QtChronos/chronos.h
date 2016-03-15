#ifndef CHRONOS_H_
#define CHRONOS_H_

#include <windows.h>

#include <QtCore>
#include <QObject>
#include <QTextStream>

#include "chronos_api/BM_API.h"
#include "chronos_api/BM_Comm.h"
#include "chronos_api/BM_Driver.h"
#include "chronos_api/BM_Sync.h"

enum en_apState {
	AP_STATE_DISCONNECTED,
	AP_STATE_CONNECTING,
	AP_STATE_CONNECTED,
	AP_STATE_IDLE,
	AP_STATE_RECEIVED_DATA,
	AP_STATE_SENDING_DATA,
	AP_STATE_DISCONNECTING
};

class Chronos : public QObject
{
	Q_OBJECT
		
public:
	Chronos(QString comPort = "");
	~Chronos();

private:
	QString m_comPort;
	en_apState m_apState;

public slots:
	void StartAP();
	void Input(QString);

signals:
	void Output(QString);
};

#endif