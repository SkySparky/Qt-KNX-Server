#include "chronos.h"

//GetStatus
// Get generic hardware status
// Returns: HW_IDLE, HW_SIMPLICITI_STOPPED, HW_SIMPLICITI_TRYING_TO_LINK, HW_SIMPLICITI_LINKED,
// HW_BLUEROBIN_STOPPED, HW_BLUEROBIN_TRANSMITTING, HW_ERROR, HW_NO_ERROR, HW_NOT_CONNECTED


Chronos::Chronos(QString comPort) : m_comPort(comPort)
{
	bool resp;
	if (m_comPort.isEmpty()) {
		unsigned char port;
		resp = BM_GetCOM(port);
		if (port > 0) {
			QTextStream(&m_comPort) << "COM" << port;
			qDebug() << "AP found on port: " << m_comPort;
		}
	}
	m_apState = AP_STATE_DISCONNECTED;
}

Chronos::~Chronos()
{
	if (m_apState != AP_STATE_IDLE) {
		if (BM_SPL_Stop()) {
			BM_CloseCOM();
		}
	}
}


void Chronos::Input(QString)
{

}

void Chronos::StartAP(void)
{
	bool resp;
	WORD status;
	WORD prevStatus;
	WORD buffStatus;
	WORD prevBuffStatus;

	while(1) {

		switch(m_apState) {
		case AP_STATE_DISCONNECTED:
			{

			QByteArray ba = m_comPort.toLatin1();
			//connect
			resp = BM_OpenCOM(ba.data());
			if (!resp) exit(-1);
			qDebug() << "[Chronos::StartAP] port opened.";
			resp = BM_Reset();
			if (!resp) exit(-1);
			qDebug() << "[Chronos::StartAP] AP reset.";
			resp = BM_SYNC_Start();
			if (!resp) exit(-1);
			qDebug() << "[Chronos::StartAP] SYNC mode started.";
			m_apState = AP_STATE_CONNECTING;
			}
			break;
		case AP_STATE_CONNECTING:
			if (BM_GetStatus(status)) {
				if (prevStatus != status)
					qDebug() << "status: " << status;


				if (status == HW_SIMPLICITI_LINKED) {
					m_apState = AP_STATE_CONNECTED;
					qDebug() << "[Chronos::StartAP] SYNCED.";
				}
				prevStatus = status;
			}

			if (BM_SYNC_GetBufferStatus(buffStatus)) {
				if (buffStatus != prevBuffStatus)
					qDebug() << "buffer status: " << buffStatus;
				prevBuffStatus = buffStatus;
			}
			break;

		case AP_STATE_CONNECTED:
			resp = BM_SYNC_GetBufferStatus(status);
			if (resp) {
				qDebug() << status;
			}
			break;

		case AP_STATE_DISCONNECTING:
			if (BM_SPL_Stop()) {
				BM_CloseCOM();
			}
			m_apState = AP_STATE_IDLE;
			break;
		};
	};
}