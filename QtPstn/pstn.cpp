#include "pstn.h"
#include "w2cUSBM_API.h"

#define GET_TONE_VOLUME(x) (0x7FFF * x / 100)

typedef enum {
	PSTN_STATE_IDLE = 0,					// idle
	PSTN_STATE_RINGING = 1,					// incoming call
	PSTN_STATE_USER_CALL = 2,				// user is calling from inside or outside
	PSTN_STATE_CALL_ANSWERED_BY_USER = 4,	// if user answers the call while the answering machine is activated
	PSTN_STATE_ANSWERING_MACHINE = 8,		// answering machine answers an incoming call
	PSTN_STATE_ANSWERING_REC = 16,			// answering machine records a message
	PSTN_STATE_CMD_WAIT_INT = 32,			// waits a dtmf command from internal device
	PSTN_STATE_CMD_WAIT_INT_HOLD = 64,		// holds the line
	PSTN_STATE_CMD_WAIT_EXT = 128,			// waits a dtmf command from external device
	PSTN_STATE_CMD_CALL_USER = 256,			//device has called user to report an event
	PSTN_STATE_CLOSE_EXT = 512				// hang up external call
} en_state;


char glb_statusMsg[256];
int glb_numOfRings = 0;
bool glb_validTel = false;
bool glb_recording = false;
bool glb_playRecTone = false;
int		glb_msgEvtDelay = 0;
bool	glb_sendingMsgEvt = false;
ClientGenerateTone_tag glb_ansTone;
//QString glb_menuOpts;

//Sets the modem's state
void PSTN::SetState(int currState)
{
	if (m_state != currState) {	// if wanted state is different from current
		m_prevState = m_state;	// save previous state
		m_state = currState;	// save wanted state
		qDebug() << "[PSTN::SetState] going from " + QString::number(m_prevState) + " to " + QString::number(m_state);
		ResetTimestamp();
		if (currState == PSTN_STATE_IDLE) {
			glb_numOfRings = 0;		//reset ring counter
			glb_validTel = false;	//no valid tel is called
			glb_playRecTone = false;	//no tone is played
			m_dtmfMsg.clear();		//clear dtmf buffer


			if (glb_recording) w2cUsbM_StopRecord(m_deviceId);	//stop any recordings
			glb_recording = false;
			w2cUsbM_SetSoftAGC_OnOff(m_deviceId, 0);	//no automatic AGC
			w2cUsbM_DoCommand(m_deviceId, HPCMD_GENERATE_STOP_ALL_TONES, 0, 0);	//stop any tone is played

			w2cUsbM_HangUp(m_deviceId, HP_CALL_USE_LOCAL_PHONE);	//close any opened call
			SetMode(HPCMD_SW_DEFAULT_PHONE_LINE);	//return to default mode PHONE<->LINE
		}

		else if (currState == PSTN_STATE_CMD_CALL_USER) {	//call user to report
			SetMode(HPCMD_SW_LINE_AudioStream);
			m_msgEvtTriesCntr++;
			//Get only the first number
			QString dialCmd = "W," + m_validTel[0];		//wait dial tone and call
			QByteArray bDialCmd;
			bDialCmd.append(dialCmd);
			long resp = w2cUsbM_Dial(m_deviceId, (char*)bDialCmd.constData()); //execute dial
			if (resp != W2C_ERR_SUCCESS) {	//if falied
				if ((++m_msgEvtTriesCntr) >= m_msgEvtTries) {	//check that tries maximum is not reached
					m_msgEvtTriesCntr = 0;	//reset tries and wait
					glb_msgEvtDelay = 120;	//use 2mins as default
				}
				m_msgEvtCntr = 0;
				SetState(PSTN_STATE_IDLE);	//return to idle
				qDebug() << "Dial failed: " << QString::number(m_msgEvtTriesCntr) << "/" << QString::number(m_msgEvtTries);
			}
			else {
				qDebug() << "success dialCmd: " << dialCmd;
				m_msgEvtTries = 0;
				glb_msgEvtDelay = m_msgEvtDelay;	//reset evt delay to normal so it doesn't hang up
			}
		}

		else if (currState == PSTN_STATE_USER_CALL) {			// if user makes a call from an internal devie
			SetMode(HPCMD_SW_LINE_AudioStream_PHONE_MONITOR);	//monitor line
		}

		else if (currState == PSTN_STATE_ANSWERING_MACHINE) {
			SetMode(HPCMD_SW_LINE_AudioStream);
			PlayFile(m_voiceMailMsg);	//Play unswering machine msg
		}

		else if (currState == PSTN_STATE_ANSWERING_REC) {

			w2cUsbM_SetSoftAGC_OnOff(m_deviceId, 1);	//set to automatic agc 
			QByteArray fname;
			fname.append(m_voiceMailFolder + "/" + QDateTime::currentDateTime().toString("yyyy_MM_dd_hh_mm_ss") + ".wav");	//create voicemail file
			glb_recording = true;	//indicate recording start
			long resp = w2cUsbM_RecordWaveFile(m_deviceId, (char*) fname.constData(), m_driverOut);	//start recording
			qDebug() << "Start recording..." << QString::number(resp) << "," << fname;
		}

		else if (currState == PSTN_STATE_CMD_WAIT_INT) {
			m_menuOpts.clear();
			QString wavFile;
			QString command;
			GetNextAction("0",wavFile,command);		//by default play menu 0
			SetMode(HPCMD_SW_PHONE_AudioStream);
			QString wavPath = m_voiceMenuFolder + "/" + wavFile;
			PlayFile(wavPath);
		}

		else if (currState == PSTN_STATE_CMD_WAIT_INT_HOLD) {
			SetMode(HPCMD_SW_PHONE_AudioStream_LINE_HOLD);
		}

		else if (currState == PSTN_STATE_CMD_WAIT_EXT) {
			SetMode(HPCMD_SW_LINE_AudioStream);
		}

		else if (currState == PSTN_STATE_CALL_ANSWERED_BY_USER) {
			SetMode(HPCMD_SW_LINE_AudioStream_PHONE_MONITOR );
		}

	}
}

long WINAPI PstnCallBack(
				  WORD		wDeviceID,		// which device called
				  DWORD		dwEventCode,	// The event code
				  DWORD		dwEventData,	// The event data (if any)
				  LPVOID		lpParameter,	// Callback data passed to the function
				  // using the lpParameter parameter of
				  // the initialization function
				  LPVOID		lpBuffer,		// Data buffer passed from the caller
				  DWORD		dwData,			// Additional data, depends on the callback
				  DWORD		dwReserved		// For future use (0)
				  )
{
	// note the use of 'lpParameter'
	PSTN * pstnDev = (PSTN *)lpParameter;
	long resp;

	if(NULL == pstnDev)
		return 0;

	// Show last event	
	if (pstnDev->m_printEvents) {
		w2cUsbM_TranslateEventToString(wDeviceID, (LPTSTR)glb_statusMsg, dwEventCode, dwEventData);
		QString logMsg = glb_statusMsg;
		pstnDev->AddLog("PstnCallBack] Status msg: " + logMsg);
	}


	// pars event
	switch(dwEventCode)
	{
		case HPEVT_DTMF: {
		//case HPEVT_DTMF_END:

			if (pstnDev->m_state == PSTN_STATE_CMD_CALL_USER) {
				glb_sendingMsgEvt = true;
			}
			else {
				QString wavFile;
				QString command;
				QString dtmfChar = pstnDev->GetDtmfString(dwEventData);
				pstnDev->m_dtmfMsg.append(dtmfChar);
				if ( pstnDev->GetNextAction(dtmfChar, wavFile, command) ) {
					QString wavPath = pstnDev->m_voiceMenuFolder + "/" + wavFile;
					pstnDev->PlayFile(wavPath);
					//if (!command.isEmpty()) {
					//	 pstnDev->m_mod->Write("EVENT,PSTN,DB," + pstnDev->m_dtmfMsg);
					//}
				}
				pstnDev->m_mod->Write("EVENT,PSTN,DB," + pstnDev->m_dtmfMsg);	//send event to DB in case no command has been found
			}
		 }
		break;

		case HPEVT_CALLPROGRESS_CALL_ANSWERED:
			if (pstnDev->m_state == PSTN_STATE_USER_CALL) {
				//start playing the events
				glb_sendingMsgEvt = true;
			}
			break;


		case HPEVT_PARALLEL_PHONE_OFF_HOOK://Parallel Phone Off-Hook. True for devcaps.wModel>=W2C_DEV_MODEL_PRO
		case HPEVT_PHONE_OFF_HOOK://Local Handset Off-Hook
			if (pstnDev->m_state == PSTN_STATE_IDLE) {
				pstnDev->SetState(PSTN_STATE_USER_CALL);	//by default give the tel line to the user when picks the phone
			}
			else if (pstnDev->m_state == PSTN_STATE_RINGING) {
				pstnDev->SetState(PSTN_STATE_CALL_ANSWERED_BY_USER);
			}
			else if (pstnDev->m_state == PSTN_STATE_ANSWERING_MACHINE) {
				w2cUsbM_SetSoftAGC_OnOff(pstnDev->m_deviceId, 0);
				w2cUsbM_DoCommand(pstnDev->m_deviceId, HPCMD_GENERATE_STOP_ALL_TONES, 0, 0);
				pstnDev->SetState(PSTN_STATE_CALL_ANSWERED_BY_USER);
			}
			else if (pstnDev->m_state == PSTN_STATE_ANSWERING_REC) {
				if (glb_recording) w2cUsbM_StopRecord(pstnDev->m_deviceId); 
				w2cUsbM_SetSoftAGC_OnOff(pstnDev->m_deviceId, 0);
				w2cUsbM_DoCommand(pstnDev->m_deviceId, HPCMD_GENERATE_STOP_ALL_TONES, 0, 0);
				pstnDev->SetState(PSTN_STATE_CALL_ANSWERED_BY_USER);
			}
			glb_numOfRings = 0;

			break;

		case HPEVT_LINE_CURRENT_DROPED:
		case HPEVT_PARALLEL_PHONE_ON_HOOK://Parallel Phone On-Hook. True for devcaps.wModel>=W2C_DEV_MODEL_PRO
		case HPEVT_PHONE_ON_HOOK://Local Handset On-Hook

			//set default type
			pstnDev->SetState(PSTN_STATE_IDLE);
			break;

		case HPEVT_PHONE_HOOK_FLASH:
			qDebug() << "internal flash with states: " << QString::number(pstnDev->m_prevState) <<"," << QString::number(pstnDev->m_state);
			if (pstnDev->m_state == PSTN_STATE_USER_CALL) {	//if it's LINE<->PHONE then turn to MODEM<->PHONE
				pstnDev->SetState(PSTN_STATE_CMD_WAIT_INT);
			}
			else if (pstnDev->m_state == PSTN_STATE_CALL_ANSWERED_BY_USER) {	//if it's LINE<->PHONE then turn to MODEM<->PHONE
				pstnDev->SetState(PSTN_STATE_CMD_WAIT_INT_HOLD);
			}
			else if ((pstnDev->m_state == PSTN_STATE_CMD_WAIT_INT) && (pstnDev->m_prevState == PSTN_STATE_USER_CALL) ) {
				pstnDev->SetState(PSTN_STATE_USER_CALL);
			}
			else if ((pstnDev->m_state == PSTN_STATE_CMD_WAIT_INT_HOLD) && (pstnDev->m_prevState == PSTN_STATE_CALL_ANSWERED_BY_USER) ) {
				pstnDev->SetState(PSTN_STATE_CALL_ANSWERED_BY_USER);
			}
			break;

		case HPEVT_LINE_RING_START:
			
			//w2cUsbM_DoCommand(pstnDev->m_deviceId, HPCMD_RINGER_START, 0, 0);
			pstnDev->SetState(PSTN_STATE_RINGING);
			pstnDev->ResetTimestamp();
			if ((++glb_numOfRings) == pstnDev->m_answerRings) {
				//answer the call
				glb_numOfRings = 0;	//reset ring counter
				if (glb_validTel) {
					pstnDev->SetState(PSTN_STATE_CMD_WAIT_EXT);
				}
				else {
					if (pstnDev->m_voiceMailEnabled) pstnDev->SetState(PSTN_STATE_ANSWERING_MACHINE);
				}
			}
			break;
		case HPEVT_LINE_RING_END:
			//w2cUsbM_DoCommand(pstnDev->m_deviceId, HPCMD_RINGER_STOP, 0, 0);

			break;

		case HP_EVENT_ASYNC_PLAYBACK_DONE: {
				if (pstnDev->m_state == PSTN_STATE_ANSWERING_MACHINE) {
					//voice mail msg is done play a tone and start recording
					glb_playRecTone = true;
					w2cUsbM_GenerateTones(wDeviceID, &glb_ansTone, 1);
					pstnDev->SetState(PSTN_STATE_ANSWERING_REC);
				}
				else if (pstnDev->m_state == PSTN_STATE_CMD_CALL_USER) {
					glb_sendingMsgEvt = true;
				}
			}
			break;


		case HPEVT_LINE_CALLER_ID://Caller-ID data Detected
		case HPEVT_LINE_CALL_WAITING_CID://Call waiting Caller-ID data Detected.
			glb_validTel = false;
			char callerId[255];
			resp = w2cUsbM_GetCidString (0, callerId);
			if (resp == W2C_ERR_SUCCESS) {
				QString telNo(callerId);
				for (int i=0; i<pstnDev->m_validTel.length(); i++) {
					if (telNo.contains(pstnDev->m_validTel.at(i))) {
						qDebug() << pstnDev->m_validTel.at(i);
						pstnDev->AddLog("PstnCallBack] incoming valid: " + QString::fromAscii(callerId));
						glb_validTel = true;
					}
				}
				if (!glb_validTel) {
					pstnDev->AddLog("PstnCallBack] incoming invalid: " + QString::fromAscii(callerId));
				}
			}

			break;
	}
	return 0;
}

PSTN::PSTN(QString &iniFile, GidtModule *mod) : 
	m_deviceId(-1), m_printEvents(true), m_state(PSTN_STATE_IDLE), m_mod(mod),
		m_dtmfTimeout(30), m_iniFile(iniFile)
{
	qDebug() << "constructor";

	//read ini file
	LoadSettings(m_iniFile);
	//Init
	InitializeModem();
	//set default type
	SetState(PSTN_STATE_IDLE);

	//Start local timer
	QTimer *timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(LocalTimer()));
	timer->start(1000);

}

PSTN::~PSTN()
{
	if (m_deviceId >= 0) {
		//w2cUsbM_HangUp (WORD wDeviceID, short bUseLocalPhone);
		w2cUsbM_CloseDevice (m_deviceId, 0);
		w2cUsbM_ShutdownDevice(m_deviceId,0);
	}
}


bool PSTN::GetNextAction(const QString &pstnTone, QString &wavFile, QString &command)
{
	bool ret = false; //dont do anything
	qDebug() << "[PSTN::GetNextAction] pstnCode=" + pstnTone;
	StopPlay();	//stop previous sound

	if ( m_state == PSTN_STATE_ANSWERING_MACHINE) {//Only during playback accept the master code
		if (pstnTone == m_unlockpin) {			//if code is correct
			SetState(PSTN_STATE_CMD_WAIT_EXT);	//go to remote control state
			AddLog("GetNextAction] unlock code used. Entering PSTN_STATE_CMD_WAIT_EXT");
			m_dtmfMsg.clear();					//empty code buffer
		}
	}
	else if (m_state & (PSTN_STATE_CMD_WAIT_INT | PSTN_STATE_CMD_WAIT_INT_HOLD | PSTN_STATE_CMD_WAIT_EXT) ) {

		QSqlQuery query;

		if (pstnTone.contains("*")) {	//return to main menu and clear all
			m_menuOpts = "0";
			query = m_db->ExecuteQuery("SELECT * FROM tbl_pstnmenus WHERE fld_id=0");
			while (query.next()) {
				QSqlRecord rec = query.record();
				wavFile = query.value(rec.indexOf("fld_wavFile")).toString();
				command = query.value(rec.indexOf("fld_action")).toString();
				qDebug() << "got: " << wavFile << "," << command;
			};
			m_dtmfMsg.clear();
			m_voiceValue.clear();
		}
		else {
			m_menuOpts.append(pstnTone);

			qDebug() << "requesting menu: " << m_menuOpts;
			query = m_db->ExecuteQuery("SELECT * FROM tbl_pstnmenus WHERE fld_id=" + m_menuOpts);
			while (query.next()) {
				QSqlRecord rec = query.record();
				wavFile = query.value(rec.indexOf("fld_wavFile")).toString();
				command = query.value(rec.indexOf("fld_action")).toString();
				qDebug() << "got: " << wavFile << "," << command;
			};

		}
		if (query.numRowsAffected() > 0) ret = true;
		/*
		if (pstnTone == "18#0*") {
			QString fname = "./rec8.wav";
			PlayFile(fname);
			m_mod->Write("WRITE,PSTN,KNX,0/0/18,00");
			m_dtmfMsg.clear();
		}
		else if (pstnTone == "18#1*") {
			QString fname = "./rec8.wav";
			PlayFile(fname);
			m_mod->Write("WRITE,PSTN,KNX,0/0/18,01");
			m_dtmfMsg.clear();
		}
		else if (pstnTone.contains("*")) {
			m_dtmfMsg.clear();

		}
		*/
	}
	else {
		m_dtmfMsg.clear();
	}


	return(ret);
}


bool PSTN::PlayFile(QString &fname, long fromPos)
{
	bool ret = true;

	QByteArray file;
	file.append(fname);
	w2cUsbM_DoCommand(m_deviceId, HPCMD_AudioStream_UNMUTE, 0, 0);
	long resp = w2cUsbM_PlayWaveFile(m_deviceId, (char*)file.constData(), fromPos, m_driverOut);
	if (resp != W2C_ERR_SUCCESS) {
		AddLog("PlayFile] failed to play file: " + fname);
		ret = false;
	}
	return(ret);
}

bool PSTN::StopPlay(void)
{
	bool ret = true;
	ResetTimestamp();
	long resp = w2cUsbM_DoCommand(m_deviceId, HPCMD_AudioStream_MUTE, 0, 0);
	//long resp = w2cUsbM_StopPlay(m_deviceId);
	if (resp != W2C_ERR_SUCCESS) {
		AddLog("StopPlay] failed to stop file.");
	}
	return(ret);
}



void PSTN::LoadSettings(QString iniFile)
{
	QSettings settings(iniFile, QSettings::IniFormat);
	bool ok;

    m_dbName = settings.value("Database/dbName").toString();
    m_dbServer = settings.value("Database/dbServer").toString();
    m_dbUser = settings.value("Database/dbUser").toString();
    m_dbPassword = settings.value("Database/dbPassword").toString();
	QString dbName = "PSTNDB";
    m_db = new ModuleDB(m_dbName, m_dbServer, m_dbUser, m_dbPassword, m_dbName);
    //try to connect to db
	if (!m_db->Connect()) {
		AddLog("LoadSettings] Could not connect to DB. Check your settings.");
		exit(-1);
	}

	m_answerRings = settings.value("Config/answer_rings_valid").toInt(&ok);
	if (!ok) {
		AddLog("LoadSettings] Could not load Config/answer_rings_valid");
		exit(-1);
	}
	m_answerInvalidRings = settings.value("Config/answer_rings_invalid").toInt(&ok);
	if (!ok) {
		AddLog("LoadSettings] Could not load Config/answer_rings_invalid");
		exit(-1);
	} 
	m_dtmfTimeout = settings.value("Config/dtmf_wait_timeout_secs").toInt(&ok);
	if (!ok) {
		AddLog("LoadSettings] Could not load Config/answer_rings_invalid");
		exit(-1);
	}
	m_unlockpin = settings.value("Config/unlock_pin").toString();

	m_msgEvtDelay = settings.value("Config/voice_msg_delay_secs").toInt(&ok);
	if (!ok) {
		AddLog("LoadSettings] Could not load Config/voice_msg_delay_secs");
		exit(-1);
	}
	glb_msgEvtDelay = m_msgEvtDelay;
	m_msgFolder = settings.value("Config/messages_folder").toString();
	QDir msgFolder(m_msgFolder);
	if (!msgFolder.exists()) {
		AddLog("LoadSettings] messages_folder doesn't exists");
		exit(-1);
	}

	m_voiceMenuFolder = settings.value("Config/voicemenu_folder").toString();
	QDir menuFolder(m_voiceMenuFolder);
	if (!menuFolder.exists()) {
		AddLog("LoadSettings] voicemenu_folder doesn't exists");
		exit(-1);
	}
	
	m_voiceMailEnabled = settings.value("Config/enable_voicemail").toInt(&ok);
	if (!ok) {
		AddLog("LoadSettings] Could not load Config/answer_rings_invalid");
		exit(-1);
	}
	if (m_voiceMailEnabled) {
		m_voiceMailMsg = settings.value("Config/voicemail_msg").toString();
		//Check if file exists
		QDir exists;
		if (!exists.exists(m_voiceMailMsg)) {
			AddLog("LoadSettings] voicemail_msg file doesn't exists");
			exit(-1);
		}

		m_voiceMailFolder = settings.value("Config/voicemail_folder").toString();
		QDir voicemailfolder(m_voiceMailFolder);
		if (!voicemailfolder.exists()) {
			AddLog("LoadSettings] voicemail_folder doesn't exists");
			exit(-1);
		}
	}
	int size = settings.beginReadArray("Config");
	for (int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		m_validTel << settings.value("valid_tel").toString();
	}
}


bool PSTN::InitializeModem(void) 
{
	bool ret = false;
	qDebug() << "Initializing modem drivers...";
	w2cUsbM_InitializeDriver(0);

	qDebug() << "Searching for pstn modems...";
	WORD numOfDev = 0;
	long resp = w2cUsbM_GetNumDevs (&numOfDev, 0);
	if (resp == W2C_ERR_SUCCESS) {
		qDebug() << "found " << numOfDev << " devices";
		m_deviceId = 0;
		if (numOfDev == 0) {
			AddLog("PSTN] Could not enumerate any device. Exiting");
			exit(-1);
		}
		//Initialize device
		resp = w2cUsbM_InitializeDevice(m_deviceId, PstnCallBack, (void*) this, NULL, 0);
		if (resp != W2C_ERR_SUCCESS) {
			AddLog("::PSTN] Failed to initialize. Err: " + resp);
			//Add log
			exit(-1);
		}
		AddLog("PSTN] Device " + QString::number(m_deviceId) + " Initialized");

		resp = w2cUsbM_OpenDevice(m_deviceId,0);
		if (resp != W2C_ERR_SUCCESS) {
			AddLog("::PSTN] Failed to open device. Err: " + resp);
			exit(-1);
		}

		//SetMode(HPCMD_DAA_CTR21_COMPLEX);

		w2cDevCaps_tag devCaps;
		devCaps.wCbSize = sizeof(w2cDevCaps_tag);
		w2cUsbM_GetDevCaps(m_deviceId, &devCaps, 0);
		m_driverOut = devCaps.uWaveOutDrvID;

		glb_ansTone.dwDurationOn = 800;
		glb_ansTone.dwDurationOff = 0;
		glb_ansTone.Frequency = 800;
		glb_ansTone.Level = GET_TONE_VOLUME(50);
		//Set country codes
		char countryCode[3] = {'3','0',0};
		w2cUsbM_SetLocalCountry (m_deviceId, countryCode);

		ret = true;
	}
	return(ret);
}

void PSTN::SetMode(int mode)
{
	long resp = -1;

	resp = w2cUsbM_DoCommand(m_deviceId, (WORD)mode, 0, 0);
	if (resp != W2C_ERR_SUCCESS ) {
		AddLog("PSTN] Failed to ser device to mode " + QString::number(mode));
		exit(-1);
	}
}



void PSTN::LocalTimer(void)
{
	uint now = QDateTime::currentDateTime().toTime_t();
	if ((m_state == PSTN_STATE_CMD_WAIT_INT) || (m_state == PSTN_STATE_CMD_WAIT_EXT) ) {
		if (now - m_timestamp > m_dtmfTimeout) {
			AddLog("LocalTimer] PSTN_STATE_CMD_WAIT_* timed out.");
			SetState(PSTN_STATE_IDLE);
		}
	}
	else if (m_state == PSTN_STATE_RINGING) {
		if (now - m_timestamp > 15) {
			AddLog("LocalTimer] PSTN_STATE_RINGING timed out.");
			SetState(PSTN_STATE_IDLE);
		}
	}
	else if (m_state == PSTN_STATE_ANSWERING_REC) {
		if (glb_playRecTone) {
			if (now - m_timestamp > 1) {
				glb_playRecTone = false;
				w2cUsbM_DoCommand(m_deviceId, HPCMD_GENERATE_STOP_ALL_TONES, 0, 0);
			}
		}
		if (now - m_timestamp > 60) {
			AddLog("LocalTimer] PSTN_STATE_ANSWERING_REC timed out.");
			SetState(PSTN_STATE_IDLE);
		}
	}
	else if (m_state == PSTN_STATE_CMD_CALL_USER) {
		if (glb_sendingMsgEvt) {
			if (!m_msgEvtToSend.isEmpty()) {
				QString msg = m_msgFolder + "/" + m_msgEvtToSend.at(0);	//get filename with path
				if (!msg.isEmpty()) {
					ResetTimestamp();
					if (PlayFile(msg) ) {
						m_msgEvtToSend.removeAt(0);
					}
					else {
						SetState(PSTN_STATE_IDLE);
					}
				}
			}
			else {
				glb_sendingMsgEvt = false;
			}
		}
		if (now - m_timestamp > 25) {
			AddLog("LocalTimer] PSTN_STATE_CMD_CALL_USER timed out.");
			SetState(PSTN_STATE_IDLE);
		}
	}
	else if (!m_msgEvtToSend.isEmpty()) {
		if (m_state == PSTN_STATE_IDLE) {
			if ((m_msgEvtCntr++) == glb_msgEvtDelay) {
				//start calling procedure
				SetState(PSTN_STATE_CMD_CALL_USER);
				m_msgEvtCntr = 0;
			}
		}
	}
}

void PSTN::ResetTimestamp(void) 
{
	m_timestamp = QDateTime::currentDateTime().toTime_t();	//update timestamp
}

QString PSTN::GetDtmfString(int code)
{
	QString resp;
	ResetTimestamp();

	if (HPEVT_DTMF_0 == code) resp="0";
	else if (HPEVT_DTMF_1 == code) resp="1";
	else if (HPEVT_DTMF_2 == code) resp="2";
	else if (HPEVT_DTMF_3 == code) resp="3";
	else if (HPEVT_DTMF_4 == code) resp="4";
	else if (HPEVT_DTMF_5 == code) resp="5";
	else if (HPEVT_DTMF_6 == code) resp="6";
	else if (HPEVT_DTMF_7 == code) resp="7";
	else if (HPEVT_DTMF_8 == code) resp="8";
	else if (HPEVT_DTMF_9 == code) resp="9";
	else if (HPEVT_DTMF_A == code) resp="A";
	else if (HPEVT_DTMF_B == code) resp="B";
	else if (HPEVT_DTMF_C == code) resp="C";
	else if (HPEVT_DTMF_D == code) resp="D";
	else if (HPEVT_DTMF_STAR == code) resp="*";
	else if (HPEVT_DTMF_POUND == code) resp="#"; 
	//qDebug() << "[PSTN::GetDtmfString] code= " + QString::number(code) + "," + resp;
	return(resp);
}


void PSTN::AddLog(QString msg)
{
	qDebug() << "[PSTN::" + msg;
	emit OutputLog("[PSTN::" + msg);
}


// PARAM_CMD,PARAM_SENDER,PARAM_DEST,
void PSTN::Input(QString msg)
{
    if (Common::GetParam(msg, Common::PARAM_DEST) == "PSTN") {
		qDebug() << "[PSTN::Input] " + msg;
        QString cmd = Common::GetParam(msg, Common::PARAM_CMD);
		QString voiceData;
		if (cmd == "EVENT") {
		
		}
		else if (cmd == "WRITE") {
			m_msgEvtCntr = 0;
            m_msgEvtToSend << Common::GetParam(msg, Common::PARAM_DATA_START);
			if (m_state == PSTN_STATE_CMD_CALL_USER) {
				if (!glb_sendingMsgEvt) glb_sendingMsgEvt = true;
			}
		}
		else if (cmd == "CMD") {
            if (Common::GetParam(msg, Common::PARAM_DEST) == "RELOAD") {	//reload config
				//read ini file
				LoadSettings(m_iniFile);
				//Init
				InitializeModem();
				//set default type
				SetState(PSTN_STATE_IDLE);
			}
		}
	}

}

void PSTN::pstnHandler(void)
{


}
