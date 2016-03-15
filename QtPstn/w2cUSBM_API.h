/*

  =========================================================================
                   Way2call  PROPRIETARY  INFORMATION
  
      This software is supplied under the terms of a licence agreement
      or non-disclosure agreement with Way2call and may not be copied nor
      disclosed except in accordance with the terms of that agreement.
       
  =========================================================================
  
  File Name:
	w2cUSBM_API.h
  
  Description:
	Hi-Phone Multipe devices Driver API
       
  Author:
	Daniel Dan-Hoffmann

  Date:
    March 2008

  Version:
	1.05.04
*/

/**
\file This is the Hi-Phone Multipe devices DLL API header file.

\author Daniel Dan-Hoffmann

\version 1.06.02
*/






/** \mainpage "Way2call Multiple Devices DLL API"



\n
Visit our web: http://www.way2call.com/

Send feedback: sdkfeedback@way2call.com
\n

!!Getting Started

  Make sure that:
-# w2cUSBM_API.h is included.
-# w2cUSBM_API.lib is linked.

!Gathering Devices Information 

- Optionally Call w2cUsbM_GetDriverVersion to get driver version. 
  \n Driver version will help application 's maintenance and support.
 

- Call w2cUsbM_InitializeDriver to  Initialize the Driver Module. 
  \n Make sure that your application has a matching call to w2cUsbM_ShutdownDriver when it is done using the driver.

 

- Call w2cUsbM_GetNumDevs to retrieve how many devices are currently present on the system. 
 

- For each device, call w2cUsbM_GetDevCaps to retrieve specific device information. 
  \n wDeviceID values are from 0 to (pwNumDevs-1)  See w2cUsbM_GetNumDevs.


!Opening and closing devices


- After Gathering Devices Information, Call w2cUsbM_InitializeDevice.

- Make sure that:

-# Aapplication has a matching call to w2cUsbM_ShutdownDevice with the same wDeviceID specified with w2cUsbM_InitializeDevice.
-# A valid callback function address has been passed with lpfnEventCallback argument.
   \n Events from the device are reported thru this callback function.
   \n See HiPhoneCallbackProc
   


- Call w2cUsbM_OpenDevice.
  \n Make sure your application has a matching call to w2cUsbM_CloseDevice with
  \n the same wDeviceID specified with w2cUsbM_OpenDevice.

---
#The device is now ready for work.#
---


!Making a call


 Use w2cUsbM_Call
 
\code

  long r = w2cUsbM_Call(wDevID,
                        "W1800606060",// wait for Dial Tone, Dial 1800606060
			            0);
  // check r error code.. 
  


\endcode

When the call is answered, HPEVT_CALLPROGRESS_CALL_ANSWERED event will be fired.


See "Error codes"




!Sending device native commands

  Sending device native commands is required in cases where higher level API function such as w2cUsbM_Call
  will not control specific feature (using the headset, custom dial prcedure, etc.).


- Call w2cUsbM_DoCommand and specify the command code and the optional (command depended) command’s data..

- #It is Highly recommended to study the device switching modes.#

  \image HiPhoneSwitching.gif "Device switching modes"


  See "Device Switching Modes"

  See "Commands"


!Getting events from the Hi-Phone(s)


  When calling w2cUsbM_InitializeDevice, pass a pointer to HiPhoneCallbackProc.
  A single callback function (serving all devices) or multiple callback functions (different one for each device)
  may be used.


\code
long WINAPI HiPhoneCallbackProc(
        WORD wDeviceID,      // which device fired the event
        DWORD dwEventCode,   // The event code
        DWORD dwEventData,   // The event data (if any)
        LPVOID lpParameter,  // Callback data passed to the function
        LPVOID lpBuffer,     // Data buffer passed from the caller
        DWORD dwData,        // Additional data, depends on the callback
        DWORD dwReserved     // For future use (0)
)
{

    //check wDeviceID ...

    switch(dwEventCode)
    {
	case HPEVT_LINE_RING_START://Incoming line RING
		// handle incomming ring event
		break;

    case HPEVT_LINE_CALLER_ID://Incoming line Caller ID
		// handle Incoming line Caller ID
		break;


	}

  return 0;

}

\endcode


  See "Events"







*/




/**
\dir
 
Note the Globals DEFINEs.



*/

/**\page " Release Notes"

---
!2009 April 08

- "Hi-Phone Maestro Features" updated.

- Headset Echo Suppression feature added.
  - Control:
    - HPCMD_HEADSET_ECHO_SUPPRESSION_ON
    - HPCMD_HEADSET_ECHO_SUPPRESSION_OFF
  - Parameters:
    - W2C_AP_HEADSET_ECHO_SUPPRESSION_SILENCE_THRESHOLD
    - W2C_AP_HEADSET_ECHO_SUPPRESSION_OUT2IN_DIFF_THRESHOLD
    - W2C_AP_HEADSET_ECHO_SUPPRESSION_OFF_TIME
    - W2C_AP_HEADSET_ECHO_SUPPRESSION_ON_TIME
    - w2cUsbM_SetParameterValue
    - w2cUsbM_GetParameter

- Phone Echo Suppression updated.
  - See:
    - HPCMD_PHONE_ECHO_SUPPRESSION_ON
    - HPCMD_PHONE_ECHO_SUPPRESSION_OFF

- Echo Suppression state for both Phone and Headset is returned on w2cDevStatus_tag.bEchoSuppression.
  - See:
    - w2cDevStatus_tag.bEchoSuppression
    - w2cUsbM_GetDeviceStatus.

*/

/**\page "Hi-Phone Maestro Features"

!Description
The Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device has 4 lines, 1 Phone, 1 dual Headset
and one assignable Thumb Wheel.

The 4 Lines Phone and Headset are represented as 6 Hi-Phone devices.
Each device with its own relevant device capabilities w2cDevCaps_tag , w2c_CapsBits_tag .

!Terminal
The Phone and/or Headset terminals can be attached to any line using w2cUsbM_SetTerminal function.

!Conference
The Lines 1 to4 can be conferenced using w2cUsbM_ConferenceAdd function.
Since there are total of 2 possible conferences among 4 lines,
The Maestro has 2 conferences entities W2C_CONFERENCE_ID_MAESTRO_A and W2C_CONFERENCE_ID_MAESTRO_B 
which Lines 1 to4 can be added to or removed from.
|If Phone and/or Headset are required to be part of a lines conference,
They should be added to the conferenced lines, using w2cUsbM_SetTerminal function.

The Lines Conference will be active for Lines that are off-hook,
i.e. at the following switcing modes:
- HPCMD_SW_LINE_AudioStream
- HPCMD_SW_LINE_AudioStream_PHONE
- HPCMD_SW_LINE_AudioStream_PHONE_MONITOR

The PC 'Aux. A' wave in/out can be used to Play or Record to/from all 'Conference A' members.
Note that the PC 'Aux. A' is also shared with both Phone and Headset.



!Thumb Wheel
The Thumb Wheel can be assigned to control any volume for any line/phone/headset
using w2cUsbM_ThumbWheelAssign.


!Wave Audio Assignment

- Wave INs, PC Recording
||Name||Assigned to
|Hi-Phone Maestro Line 1|Line 1
|Hi-Phone Maestro Line 2|Line 2
|Hi-Phone Maestro Line 3|Line 3
|Hi-Phone Maestro Line 4|Line 4
|Hi-Phone Maestro Aux. A|Shard by Phone and Headset, #Conference ID A recording#


- Wave OUTs, PC Playback
||Name||Assigned to
|Hi-Phone Maestro Line 1|Line 1
|Hi-Phone Maestro Line 2|Line 2
|Hi-Phone Maestro Line 3|Line 3
|Hi-Phone Maestro Line 4|Line 4
|Hi-Phone Maestro Aux. A|Shard by Phone and Headset, #Conference ID A Playback#
|Hi-Phone Maestro Aux. B|Shard by Lines 1-4 when put to HOLD, can be used for music on hold



!Summary
The following summarizes the Hi-Phone Maestro related Features:


Functions:
- w2cUsbM_SetTerminal
- w2cUsbM_GetTerminal
- w2cUsbM_ConferenceAdd
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- w2cUsbM_ThumbWheelAssign
- w2cUsbM_GetDeviceParallelHookState


Events:
- HPEVT_PARALLEL_PHONE_OFF_HOOK
- HPEVT_PARALLEL_PHONE_ON_HOOK
- HPEVT_LINE_UNPLUGGED
- HPEVT_LINE_PLUGGED
- HP_EVENT_LINE_TERMINAL_CHANGED
- HP_EVENT_MATRIX_ERROR
- HP_EVENT_CONFERENCE_CONNECTED
- HP_EVENT_CONFERENCE_DISCONNECTED
- HPEVT_THUMB_WHEEL_REASSIGNED
- HPEVT_VOLUME_CHANGED

Commands:
- HPCMD_WIRETAPPING


*/

/**\page "Device Switching Modes"

\n #It is Highly recommended to study the device switching modes.#

  \n
  \image HiPhoneSwitching.gif "Device switching modes"
  \n
  \n
  <hr>

  \n HPCMD_SW_PHONE_AudioStream
  \n
  \n The local 'Phone' is powered by the Hi-Phone. 
  \n The PC can exchange audio with the local 'Phone'.
  \n
  \n \image 0x0a.gif "Phone<->AudioStream"
  \n
  \n
  \n
  <hr>
  
  \n HPCMD_SW_LINE_AudioStream_PHONE_Direct
  \n
  \n 'Line' (with 'Phone' in parallel) - 'PC Audio'. 
  \n The 'Phone' is paralleled to the 'Line'.
  \n This mode rearly used since it draws more current from the 'Line'.
  \n The PC can exchange audio with the 'Line' and with the local 'Phone' via the 'Line'.
  \n The local 'Phone' is powered by the line.
  \n
  \n \image 0x1a.gif "Line/phone (direct)<->AudioStream" 
  \n
  \n
  \n
  <hr>


  
  \n HPCMD_SW_NONE_CONNECTED
  \n None connected.
  \n The local 'Phone' is powered by the Hi-Phone. 
  \n \image 0x2a.gif "No connection" 
  \n
  \n
  \n
  <hr>


     
  \n HPCMD_SW_DEFAULT_PHONE_LINE
  \n Phone - Line. The Default switching mode.
  \n
  \n \image 0x3a.gif "Phone/Line connection (default)" 
  \n
  \n
  \n
  <hr>

  
  \n HPCMD_SW_PHONE_AudioStream_LINE_HOLD
  \n Phone - PC Audio connection with the line opened and no audio to / from it, 'Line' is on HOLD.
  \n
  \n \image 0x4a.gif "Phone<->AudioStream, Line on hold" 
  \n
  \n
  \n
  <hr>

  
  \n HPCMD_SW_LINE_AudioStream
  \n 'Line' - 'PC Audio'. The Line is opened for answering / making a call.
  \n The PC can exchange audio with the 'Line'.
  \n
  \n \image 0x5a.gif "Line <-> AudioStream" 
  \n
  \n
  \n
  <hr>
  

  \n HPCMD_SW_LINE_AudioStream_PHONE
  \n 'Line' - 'PC Audio' - 'Phone'.
  \n Conference style connection.
  \n The 'PC Audio', 'Line' and the local 'Phone' can exchange audio.
  \n 'Line'->'Phone' or 'Phone'->'Line' audio can be mute / unmute.
  \n
  \n \image 0x6a.gif "Line<->AudioStream<->Phone"
  \n
  \n
  \n
  <hr>

  
  \n HPCMD_SW_LINE_AudioStream_PHONE_MONITOR
  \n 'Line' - 'PC Audio' 
  \n The PC can exchange audio with the 'Line'.
  \n The phone can exchange audio with the 'Line'.
  \n 'Line'->'Phone' or 'Phone'->'Line' audio can be mute / unmute.
  \n
  \n \image 0x7a.gif "Line <-> AudioStream,  Phone as Line Monitor" 
  \n
  \n
  \n
  
*/






/**\page "Call Related Functions"


||Function|| brief description
|w2cUsbM_Call|Open the line, dial the specified number, and start call progress analysis.
|w2cUsbM_Answer|Open the 'Line' for answer incoming call or dial.
|w2cUsbM_Dial|Dial the specified number.
|w2cUsbM_HangUp|Close the line and hang up a call.



*/


/**\page "Audio Play / Rec."


|It is recommended to study Windows Multimedia Audio SDK.
\n
\n

---
!Playback functions
||Function||brief description
|w2cUsbM_GetWaveFileEndPosition|Get Wave File End Position
|w2cUsbM_PlayWaveFile|Play a Wave File to the specified audio device.
|w2cUsbM_StopPlay|Stop Playback
|w2cUsbM_PausePlay|Pause Playback
|w2cUsbM_ResumePlay|Resume Playback
|w2cUsbM_GetPlayPosition|Get Playback position
|w2cUsbM_SetPlayPosition|Set Playback position

---
!Recording Functions
||Function||brief description
|w2cUsbM_RecordWaveFile|Record a Wave File from the specified audio device.
|w2cUsbM_StopRecord|Stop recording
|w2cUsbM_PauseRecord|Pause recording
|w2cUsbM_ResumeRecord|Resume recording
|w2cUsbM_RecordedAudioCompression|Turn recording compression on or off.
|w2cUsbM_GetRecAudioFormatString|Get recording compression format string.
|w2cUsbM_SelectRecAudioFormatDlg|Display a  recording compression format dialog.
|w2cUsbM_GetRecordingSignalLevel|Get Recording Signal Level.
|w2cUsbM_SetSoftAGC_OnOff|Turn software automatic gain on or off.
|w2cUsbM_SetSoftAGC_Parameters|Set software automatic gain parameters
|w2cUsbM_GetSoftAGC_Parameters|Get software automatic gain parameters
|w2cUsbM_GetSoftAGC_Activity|Get software automatic gain activity
*/






#pragma once

#ifndef _include_w2cUSBM_API
#define _include_w2cUSBM_API




#include <windows.h>



// ==================
// Way2call Product IDs


/// Hi-Phone Desktop RS232
#define W2C_DEV_MODEL_RS232					0x0001

/// Hi-Phone Desktop PCMCIA
#define W2C_DEV_MODEL_PCMCIA				0x0002

/// Hi-Phone Desktop PCMCIA DSP
#define W2C_DEV_MODEL_PCMCIADSP				0x0003

/// Hi-Phone Desktop USB
#define W2C_DEV_MODEL_USB					0x0004

/// Hi-Phone Desktop Lite
#define W2C_DEV_MODEL_LITE					0x0005

/// Hi-Phone Chat
#define W2C_DEV_MODEL_CHAT					0x0006

/// Hi-Phone Mini Chat
#define W2C_DEV_MODEL_MINICHAT				0x0007

/// Hi-Phone Super Chat
#define W2C_DEV_MODEL_SUPERCHAT				0x0008

/// Hi-Phone Desktop Pro.
#define W2C_DEV_MODEL_PRO					0x000A

///Hi-Phone Maestro, see "Hi-Phone Maestro Features"
#define W2C_DEV_MODEL_MAESTRO				0x000B

///Virtual Window (Dialog) device
#define W2C_DEV_MODEL_VIRTUAL_WINDOW		0x0070

///Virtual Internet Telephony Service Provider device 
#define W2C_DEV_MODEL_VIRTUAL_ITSP			0x0071

///Virtual Converged (ITSP+Analog) device 
#define W2C_DEV_MODEL_VIRTUAL_CONVERGED		0x0072



/**Phone terminal device

!See:
- HP_EVENT_LINE_TERMINAL_CHANGED
- w2cUsbM_SetTerminal
*/
#define W2C_TERMINAL_PHONE			0

/**Headset terminal device

!See:
- HP_EVENT_LINE_TERMINAL_CHANGED
- w2cUsbM_SetTerminal

*/
#define W2C_TERMINAL_HEADSET		1


/**The terminal is disconnected from the line.


!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- W2C_TERMINAL_PHONE
- W2C_TERMINAL_HEADSET
*/
#define W2C_TERMMODE_NONE                     0x00000000



/**Line Ring signal to local phone's (Terminal) ringer routing.
Valid for local phone only.

!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- W2C_TERMINAL_PHONE
- W2C_TERMMODE_HOOKSWITCH
*/
#define W2C_TERMMODE_RINGER                     0x00000008


/**Local phone (Terminal) Hook-Switch signal to Line routing.
Valid for local phone only.

!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- W2C_TERMINAL_PHONE
- W2C_TERMMODE_RINGER
*/
#define W2C_TERMMODE_HOOKSWITCH                 0x00000010


/**Local Terminal Audio to Line routing.
Valid for both local phone and headset

!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- W2C_TERMINAL_PHONE
- W2C_TERMINAL_HEADSET
*/
#define W2C_TERMMODE_MEDIATOLINE                0x00000020

/**Line to Local Terminal Audio routing.
Valid for both local phone and headset

!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- W2C_TERMINAL_PHONE
- W2C_TERMINAL_HEADSET
*/
#define W2C_TERMMODE_MEDIAFROMLINE              0x00000040




/**Local Headset (Terminal) plugged/unplugged events to the line device.
Valid for local Headset only.

!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED

*/
#define W2C_TERMMODE_PLUGGED                 0x00000080


/**Maestro Conference ID.
This is conference A ID.
See
- w2cUsbM_ConferenceAdd
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"
*/
#define W2C_CONFERENCE_ID_MAESTRO_A		0


/**Maestro Conference ID.
This is conference B ID.
See
- w2cUsbM_ConferenceAdd
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"
*/
#define W2C_CONFERENCE_ID_MAESTRO_B		1




// ==================
// Hi-Phone Commands

//Device switching modes
//'AudioStream' is the PC Audio Stream


/** Phone<->AudioStream
\n \image 0x0a.gif "Phone<->AudioStream"
\n 
The local 'Phone' is powered by the Hi-Phone. 
\n The PC can exchange audio with the local 'Phone'.
\n See "Device Switching Modes"
*/
#define HPCMD_SW_PHONE_AudioStream					0x000A 

// Line/phone (direct)<->AudioStream
/**Line/phone (direct)<->AudioStream
\n \image 0x1a.gif "Line/phone (direct)<->AudioStream" 

\n 'Line' (with 'Phone' in parallel) - 'PC Audio'. 
\n The 'Phone' is paralleled to the 'Line'.
\n This mode rearly used since it draws more current from the 'Line'.
\n The PC can exchange audio with the 'Line' and with the local 'Phone' via the 'Line'.
\n The local 'Phone' is powered by the line.
\n See "Device Switching Modes"
*/
#define HPCMD_SW_LINE_AudioStream_PHONE_Direct		0x001A  

// No connection
/**No connection
\n \image 0x2a.gif "No connection"
\n None connected.
\n The local 'Phone' is powered by the Hi-Phone.
\n See "Device Switching Modes"
*/
#define HPCMD_SW_NONE_CONNECTED						0x002A  

// Phone/Line connection (default)
/**Phone/Line connection (default)
\n \image 0x3a.gif "Phone/Line connection (default)" 
\n Phone - Line. The Default switching mode.
\n See "Device Switching Modes"
*/
#define HPCMD_SW_DEFAULT_PHONE_LINE					0x003A  

// Phone <-> AudioStream, line on-hold
/**Phone <-> AudioStream, line on-hold
\n \image 0x4a.gif "Phone <-> AudioStream, line on-hold"
\n Phone - PC Audio connection with the line opened and no audio to / from it, 'Line' is on HOLD. 
\n See "Device Switching Modes"
*/
#define HPCMD_SW_PHONE_AudioStream_LINE_HOLD		0x004A	

// Line <-> AudioStream
/**Line <-> AudioStream
\n \image 0x5a.gif "Line <-> AudioStream" 
\n 'Line' - 'PC Audio'. The Line is opened for answering / making a call.
\n The PC can exchange audio with the 'Line'. 
\n See "Device Switching Modes"
*/
#define HPCMD_SW_LINE_AudioStream					0x005A	

// Line<->AudioStream<->Phone
/**Line<->AudioStream<->Phone
\n \image 0x6a.gif "Line<->AudioStream<->Phone"
\n 'Line' - 'PC Audio' - 'Phone'.
\n Conference style connection.
\n The 'PC Audio', 'Line' and the local 'Phone' can exchange audio.
\n 'Line'->'Phone' or 'Phone'->'Line' audio can be mute / unmute.
\n See "Device Switching Modes"
*/
#define HPCMD_SW_LINE_AudioStream_PHONE				0x006A	

// Line <-> AudioStream,  Phone as Line Monitor
/**Line <-> AudioStream,  Phone as Line Monitor
\n \image 0x7a.gif "Line <-> AudioStream,  Phone as Line Monitor" 
\n 'Line' - 'PC Audio' 
\n The PC can exchange audio with the 'Line'.
\n The phone can exchange audio with the 'Line'.
\n 'Line'->'Phone' or 'Phone'->'Line' audio can be mute / unmute
\n See "Device Switching Modes"
*/
#define HPCMD_SW_LINE_AudioStream_PHONE_MONITOR		0x007A	





// Audio to/from PC

/// Audio to/from PC is normal (default)
#define HPCMD_AudioStream_UNMUTE		0x12 

/// Audio to/from PC is muted
#define HPCMD_AudioStream_MUTE			0x02 


// When HPCMD_SW_LINE_AudioStream_PHONE_MONITOR  mode or 
// HPCMD_SW_LINE_AudioStream_PHONE are used,
// The following commands are valid:
/// Un-Mute phone
#define HPCMD_MONITOR_UNMUTE_PHONE		0x002B

/// Mute phone
#define HPCMD_MONITOR_MUTE_PHONE		0x003B	

/// Un-Mute line
#define HPCMD_MONITOR_UNMUTE_LINE		0x004B	

/// Mute line
#define HPCMD_MONITOR_MUTE_LINE			0x005B


	

/**Wiretapping
This mode can be used to record or listening to other calls on the line
while the line is closed (not actively used by the Hi-Phone).

When the line is closed (all DAA on-hhok modes):
HPCMD_SW_PHONE_AudioStream
HPCMD_SW_NONE_CONNECTED
HPCMD_SW_DEFAULT_PHONE_LINE 
      
The audio from the line is routed to the wave-in or local phone/headset.

Command's data:
|HPCMD_WIRETAPPING_ON| Turn Wiretapping ON
|HPCMD_WIRETAPPING_OFF|Turn Wiretapping OFF

The wiretapping feature has no capability bit yet.
The wiretapping feature is available with the following products:
W2C_DEV_MODEL_PRO
W2C_DEV_MODEL_MAESTRO

!See:
- w2cDevStatus_tag.bWiretapping

*/
#define HPCMD_WIRETAPPING				0x008A
    // HPCMD_WIRETAPPING Command data
	///HPCMD_WIRETAPPING Command Data: Turn on
	#define HPCMD_WIRETAPPING_ON		0x0001

    ///HPCMD_WIRETAPPING Command Data: Turn off
	#define HPCMD_WIRETAPPING_OFF		0x0000



// Headset control
/// Select local Telephone.
#define HPCMD_SELECT_PHONE				0x000E	

/// Select local Headset
#define HPCMD_SELECT_HEADSET			0x001E	

/**Disable Headset echo suppression (default)
Works for the following Hi-Phone devices:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO

See:
  - w2cDevStatus_tag.bEchoSuppression
  - w2cUsbM_GetDeviceStatus.

*/
#define HPCMD_HEADSET_ECHO_SUPPRESSION_OFF		0x006B  

/**Enable Headset echo suppression.

Used when a regular microphone and speakers are connected to the headset port.

Works for the following Hi-Phone devices:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO

See:
- w2cDevStatus_tag.bEchoSuppression
- w2cUsbM_GetDeviceStatus.
- W2C_AP_HEADSET_ECHO_SUPPRESSION_SILENCE_THRESHOLD
- W2C_AP_HEADSET_ECHO_SUPPRESSION_OUT2IN_DIFF_THRESHOLD
- W2C_AP_HEADSET_ECHO_SUPPRESSION_OFF_TIME
- W2C_AP_HEADSET_ECHO_SUPPRESSION_ON_TIME


*/
#define HPCMD_HEADSET_ECHO_SUPPRESSION_ON		0x007B  


//Aux. wave in audio content
/// Aux wave in content is CODEC (mormal).
#define HPCMD_AUX_CODEC					0x004E

/// Aux. wave in content is Wave Out (echoed back)
#define HPCMD_AUX_WAVEOUT				0x005E	

/// Aux. wave in content is Wave Out Mixed with CODEC
#define HPCMD_AUX_CODEC_WAVEOUT			0x006E	

// Echo Suppression
/**Disable Phone echo suppression.

See:
- HPCMD_PHONE_ECHO_SUPPRESSION_ON
- w2cDevStatus_tag.bEchoSuppression
- w2cUsbM_GetDeviceStatus.

*/
#define HPCMD_PHONE_ECHO_SUPPRESSION_OFF	0x000B  

/**Enable Phone echo suppression (default).
For the following Hi-Phone devices,
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO

Echo Cancellation algorithm is used for the phone port.


For the rest Hi-Phone devices,
Echo Suppression algorithm is used for the 'Phone' <-> 'PC Audio Stream' signal path only.

See:
- HPCMD_PHONE_ECHO_SUPPRESSION_OFF
- w2cDevStatus_tag.bEchoSuppression
- w2cUsbM_GetDeviceStatus.

*/
#define HPCMD_PHONE_ECHO_SUPPRESSION_ON		0x001B  




// Native Dial commands
/** Native Dial command.
Command's Data is Dial content.

|It is recommended to use w2cUsbM_Dial
which is a Higher Level function.


*/
#define HPCMD_DIAL						0x008C		

/// Call progress control. Command's Data start / stop
#define HPCMD_CALL_PROGRESS_CONTROL		HPCMD_DIAL	

	// Native Dialing Command - Command's Data
    
    ///HPCMD_DIAL Command's Data: DTMF 0
	#define HPCMD_DIAL_DTMF_0			0x00

    ///HPCMD_DIAL Command's Data: DTMF 1
	#define HPCMD_DIAL_DTMF_1			0x01

	///HPCMD_DIAL Command's Data: DTMF 2
	#define HPCMD_DIAL_DTMF_2			0x02

	///HPCMD_DIAL Command's Data: DTMF 3
	#define HPCMD_DIAL_DTMF_3			0x03

	///HPCMD_DIAL Command's Data: DTMF 4
	#define HPCMD_DIAL_DTMF_4			0x04

	///HPCMD_DIAL Command's Data: DTMF 5
	#define HPCMD_DIAL_DTMF_5			0x05

	///HPCMD_DIAL Command's Data: DTMF 6
	#define HPCMD_DIAL_DTMF_6			0x06

	///HPCMD_DIAL Command's Data: DTMF 7
	#define HPCMD_DIAL_DTMF_7			0x07	

	///HPCMD_DIAL Command's Data: DTMF 8
	#define HPCMD_DIAL_DTMF_8			0x08

	///HPCMD_DIAL Command's Data: DTMF 9
	#define HPCMD_DIAL_DTMF_9			0x09

	///HPCMD_DIAL Command's Data: DTMF *
	#define HPCMD_DIAL_DTMF_STAR		0x0A

	///HPCMD_DIAL Command's Data: DTMF \#
	#define HPCMD_DIAL_DTMF_POUND		0x0B

	///HPCMD_DIAL Command's Data: DTMF A
	#define HPCMD_DIAL_DTMF_A			0x0C

	///HPCMD_DIAL Command's Data: DTMF B
	#define HPCMD_DIAL_DTMF_B			0x0D

	///HPCMD_DIAL Command's Data: DTMF C
	#define HPCMD_DIAL_DTMF_C			0x0E

	///HPCMD_DIAL Command's Data: DTMF D
	#define HPCMD_DIAL_DTMF_D			0x0F
	
	///HPCMD_DIAL Command's Data: Pulse  0
	#define HPCMD_DIAL_PULSE_0			0x10

	///HPCMD_DIAL Command's Data: Pulse 1
	#define HPCMD_DIAL_PULSE_1			0x11

	///HPCMD_DIAL Command's Data: Pulse 2
	#define HPCMD_DIAL_PULSE_2			0x12

	///HPCMD_DIAL Command's Data: Pulse 3
	#define HPCMD_DIAL_PULSE_3			0x13

	///HPCMD_DIAL Command's Data: Pulse 4
	#define HPCMD_DIAL_PULSE_4			0x14

	///HPCMD_DIAL Command's Data: Pulse 5
	#define HPCMD_DIAL_PULSE_5			0x15

	///HPCMD_DIAL Command's Data: Pulse 6
	#define HPCMD_DIAL_PULSE_6			0x16

	///HPCMD_DIAL Command's Data: Pulse 7
	#define HPCMD_DIAL_PULSE_7			0x17

	///HPCMD_DIAL Command's Data: Pulse 8
	#define HPCMD_DIAL_PULSE_8			0x18

	///HPCMD_DIAL Command's Data: Pulse 9
	#define HPCMD_DIAL_PULSE_9			0x19

	///HPCMD_DIAL Command's Data: Dial Hook-Flash 
	#define HPCMD_DIAL_FLASH			0x1A

	///HPCMD_DIAL Command's Data: Dial Pause 
	#define HPCMD_DIAL_PAUSE			0x1B

	///HPCMD_DIAL Command's Data: Wait for Dial Tone
	#define HPCMD_DIAL_WAIT_DIALTONE	0x1C

	// Call Progress control 
	///HPCMD_DIAL or HPCMD_CALL_PROGRESS_CONTROL Command's Data: Stop call progress analysis
	#define HPCMD_CALL_PROGRESS_STOP	0x1E

	///HPCMD_DIAL or HPCMD_CALL_PROGRESS_CONTROL Command's Data: Start call progress analysis
	#define HPCMD_CALL_PROGRESS_START	0x1F




//~ #define HPCMD_SET_ECHO_THRESHOLD	0x009D	/// Set echo-cancelation threshold

/**
Call Waiting Caller ID feature control.
Command Data 0 is diable, Data 1 is enable. default is 0.
*/
#define HPCMD_CWCID_SW					0x007E	

// Tone generator

/** Generate Dial-Tone.
 350Hz + 440Hz, contineous.
*/
#define HPCMD_GENERATE_DIAL_TONE		0x000C

/** Generate Ringback-Tone.
 440Hz + 480Hz, 2 seconds On, 4 seconds off.
*/
#define HPCMD_GENERATE_RINGBACK_TONE	0x001C	

/** Generate Busy-Tone.
480Hz + 620Hz, 0.5 second On, 0.5 second off.
*/
#define HPCMD_GENERATE_BUSY_TONE		0x002C	

/** Generate Reorder-Tone.
480Hz + 620Hz, 0.25 second On, 0.25 second off.
*/
#define HPCMD_GENERATE_REORDER_TONE		0x003C	

/** Generate Proceeding-Tone.
 1000Hz, 0.01 second On, 1 second off.
*/
#define HPCMD_GENERATE_PROCEEDING_TONE	0x004C	


/**Generate extended tone.
Command Data is extended tone number:

||Command's Data||Description
|HPCMD_GENERATE_EX_INFINITE_1KHZ|1000Hz infinite beep
|HPCMD_GENERATE_EX_1KHZ_BEEP|1000Hz beep , 700 miliseconds duration
|HPCMD_GENERATE_EX_RCEIVER_OFF_HOOK|Receiver Of-Hook (ROH) 4 frequencies,
		100 milisecond on/off cyclic. (1400 Hz, 2060 Hz 2450 Hz, 2600 Hz)
|HPCMD_GENERATE_EX_CWCID_CEAS|Call Waiting Caller ID CEAS

*/
#define HPCMD_GENERATE_EX				0x006C	       
	
	/// HPCMD_GENERATE_EX Command Data: 1000Hz infinite beep.
	#define HPCMD_GENERATE_EX_INFINITE_1KHZ     0 
	
	/// HPCMD_GENERATE_EX Command Data: 1000Hz beep , 700 miliseconds duration
	#define HPCMD_GENERATE_EX_1KHZ_BEEP	        1 /// 1 == 
	
	/** HPCMD_GENERATE_EX Command Data: Receiver Of-Hook (ROH) 4 frequencies,
		100 milisecond on/off cyclic. (1400 Hz, 2060 Hz 2450 Hz, 2600 Hz).
	*/
	#define HPCMD_GENERATE_EX_RCEIVER_OFF_HOOK  2 
	
	/// HPCMD_GENERATE_EX Command Data: Call Waiting Caller ID CEAS
	#define HPCMD_GENERATE_EX_CWCID_CEAS	    3 


/** Stop Generating any Tones.

!See:
- w2cUsbM_GenerateTones

*/
#define HPCMD_GENERATE_STOP_ALL_TONES	0x007C	


// Ringer control
/// Stop ringer (default)
#define HPCMD_RINGER_STOP               0x0004

/**Start ringing the local phone.
Command Data is ring pattern:
0 is default pattern, >= 1 is a defined ring pattern.
!See:
- w2cUsbM_GetNumRings
- w2cUsbM_GetRingName
- w2cUsbM_DistinctiveRingDialog
- "Distinctive Ring Setup"
- HPCMD_BUZZER_ENABLE HPCMD_BUZZER_DISABLE
*/
#define HPCMD_RINGER_START				0x0014

/**Set the default ring pattern's  off period.
Command data = period in 100ms units*/
#define HPCMD_RINGER_OFF_PERIOD			0x0087 

/**Set the default ring pattern's on period.
Command data = period in 100ms units.
*/
#define HPCMD_RINGER_ON_PERIOD			0x0097 

// Ringer frequency

/// Set ringer frequency to 17Hz
#define HPCMD_RINGER_FREQ_17HZ			0x0044 

/// Set ringer frequency to 20Hz
#define HPCMD_RINGER_FREQ_20HZ			0x0054 

/// Set ringer frequency to 25Hz (Default)
#define HPCMD_RINGER_FREQ_25HZ			0x0064 )

/// Set ringer frequency to 50Hz
#define HPCMD_RINGER_FREQ_50HZ			0x0074 


/**Enable Internal buzzer

Some Hi-Phone Devices like the Hi-Phone Desktop Lite W2C_DEV_MODEL_LITE ,
has internal buzzer.
The internal Buzzer sounds when:
- Follow Line Ring
- Can be programatically activated using HPCMD_RINGER_START command utilizing ring patterns.

Check if w2c_CapsBits_tag.bRingableBuzzer is set.

The Internal Buzzer is enabled by default.

See
- HPCMD_BUZZER_DISABLE
- HPCMD_RINGER_START

*/
#define HPCMD_BUZZER_ENABLE				0x0015


/**Disable Internal buzzer

See HPCMD_BUZZER_ENABLE
*/
#define HPCMD_BUZZER_DISABLE			0x0005




// DAA Impedance
/// Set DAA (Line Interface) impedance to normal (Default)
#define HPCMD_DAA_NORMAL				0x0003

/// Set DAA (Line Interface) impedance to complex
#define HPCMD_DAA_COMPLEX				0x0013,

/// Set DAA (Line Interface) impedance to special
#define HPCMD_DAA_SPECIAL				0x0023,

/// Set DAA (Line Interface) impedance to special complex
#define HPCMD_DAA_SPECIAL_COMPLEX		0x0033,

/// Set DAA (Line Interface) impedance to CTR21 (Europe)
#define HPCMD_DAA_CTR21					0x0043,

/// Set DAA (Line Interface) impedance to cmplex (Europe, Germany)
#define HPCMD_DAA_CTR21_COMPLEX			0x0053,

/// Set DAA (Line Interface) impedance to CTR21 special (Europe)
#define HPCMD_DAA_CTR21_SPECIAL			0x0063,

/// Set DAA (Line Interface) impedance to CTR21 special complex (Europe)
#define HPCMD_DAA_CTR21_SPECIAL_COMPLEX	0x0073,

// Pulse dial Make/Break ratio

/// Set Pulse dial Make/Break ratio to 39/61 @ 10 PPS (USA, Default)
#define HPCMD_PULSE_396110			0x000D

/// Set Pulse dial Make/Break ratio to 33/67 @ 10 PPS (UK, Hong Kong)
#define HPCMD_PULSE_336710			0x001D

/// Set Pulse dial Make/Break ratio to 39/61 @ 20 PPS
#define HPCMD_PULSE_396120			0x002D

/// Set Pulse dial Make/Break ratio to 33/67 @ 20 PPS (Japan)
#define HPCMD_PULSE_336720			0x003D


// Set Adjustable Parameters, Read/ Wrtie device registers
/// Set DIALTONE timeout. Command data = period in seconds. Range:1-255,default=4.
#define HPCMD_SET_WAIT_DIALTONE		0x00A7

/// Set ANSWER timeout. Command data = period in seconds.Range:1-255,default=120.
#define HPCMD_SET_WAIT_ANSWER		0x00B7  

/// Set DTMF dialing speed. Command data = period in 1ms. Range: 50-255, default = 95.
#define HPCMD_SET_DTMF_SPEED		0x00C7

/// Set PAUSE (comma) time. Command data = period in seconds,Range:1-255,default=1.
#define HPCMD_SET_PAUSE_TIME		0x00D7

/// Set Hook-Flash duration. Command data = period in 10ms. Range:1-255, default 70.
#define HPCMD_SET_HOOK_FLASH_LENGTH	0x008D

/**Set Voice detection threshold. Command Data Range: 0 to 127. default is 15.

!See:
- HPEVT_CALLPROGRESS_CALL_ANSWERED

*/
#define HPCMD_SET_VOICE_THRESHOLD	0x008E

// Write only Device Registers

/// Set Pre - Hook-Flash delay time. Command data = period in 10 ms. Range 1-255, default=100.
#define HPCMD_SET_HOOK_FLASH_PRE    0x00DD

/// Set Post - Hook-Flash delay time. Command data = period in 10 ms. Range 1-255, default=100
#define HPCMD_SET_HOOK_FLASH_POST   0x00ED

/// Set minimum DTMF detection time.Command data = period in 1ms. Range: 1-55, default is 50.
#define HPCMD_SET_DTMF_DETECT_TIME  0x00FD



// Request Adjustable Parameter as event 
/// Request system status1. Device Response with HPEVT_NOTIFY_STATUS1 event
#define HPCMD_GET_STATUS1			0x0008

/// Request system status2. Device Response with HPEVT_NOTIFY_STATUS2 event
#define HPCMD_GET_STATUS2			0x0018

/// Request DIALTONE timeout. Device Response with HPEVT_NOTIFY_WAIT_DIALTONE event
#define HPCMD_GET_WAIT_DIALTONE		0x0028

/// Request ANSWER timeout. Device Response with HPEVT_NOTIFY_WAIT_ANSWER event
#define HPCMD_GET_WAIT_ANSWER		0x0038

/// Request DTMF dialing speed. Device Response with HPEVT_NOTIFY_DTMF_SPEED event
#define HPCMD_GET_DTMF_SPEED		0x0048

/// Request PAUSE (comma) time. Device Response with HPEVT_NOTIFY_PAUSE_TIME event
#define HPCMD_GET_PAUSE_TIME		0x0058


/// Lite DTMF detection level from DAA, phone on-hook.
#define HPCMD_SET_LITE_DTMF_THRESHOLD_DAA_ONHOOK	0x0088

/// Lite DTMF detection level from DAA, phone off-hook.
#define HPCMD_SET_LITE_DTMF_THRESHOLD_DAA_OFFHOOK	0x0098

/// Lite DTMF detection level from phone.
#define HPCMD_SET_LITE_DTMF_THRESHOLD_CODEC			0x00A8


// Set Events Control / Masks
/// Disables repetitions of call progress events
#define HPCMD_DISABLE_EVENTS_REPETITIONS	0x0029

/// Enables repetitions of call progress events (DEFAULT)
#define HPCMD_ENABLE_EVENTS_REPETITIONS		0x0039


/// Sets events mask (Group 1)
#define HPCMD_SET_EVENT_MASK_1			0x0089

	// HPCMD_SET_EVENT_MASK_1 Command Data:
	///HPCMD_SET_EVENT_MASK_1 Command Data: Disable all DTMF events (40h-4Fh, 5Fh). 
	#define HP_EVENT_MASK1_DTMF			0x01	//- - - -   - - - X 1 = disable all DTMF events (40h-4Fh, 5Fh). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: reserved
	#define HP_EVENT_MASK1_RESERVED1	0x02	//- - - -   - - X - reserved. 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable DTMF key release event (5Fh)
	#define HP_EVENT_MASK1_DTMF_END		0x04	//- - - -   - X - - 1 = disable DTMF key release event (5Fh). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable pulse dial events (50h-59h)
	#define HP_EVENT_MASK1_PULSE_DIAL	0x08	//- - - -   X - - - 1 = disable pulse dial events (50h-59h). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable hook-flash event (61h)
	#define HP_EVENT_MASK1_HOOK_FLASH	0x10	//- - - X   - - - - 1 = disable hook-flash event (61h). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable handset events 0ff/om hook (62h-63h)
	#define HP_EVENT_MASK1_HANDSET		0x20	//- - X -   - - - - 1 = disable handset events 0ff/om hook (62h-63h). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable headset events (64h-65h)
	#define HP_EVENT_MASK1_HEADSET		0x40	//- X - -   - - - - 1 = disable headset events (64h-65h). 
	
	///HPCMD_SET_EVENT_MASK_1 Command Data: disable ringer transitions events (74h-75h) - default
	#define HP_EVENT_MASK1_RINGER		0x80	//X - - -   - - - - 1 = disable ringer transitions events (74h-75h) - default. 

/// Sets events mask (Group 2)
#define HPCMD_SET_EVENT_MASK_2			0x0099

	// HPCMD_SET_EVENT_MASK_2 Command Data:
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable dial tone event (68h)
	#define HP_EVENT_MASK2_DIALTONE		0x01	//- - - -   - - - X 1 = disable dial tone event (68h). 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable time-out event and functionality (6Ah)
	#define HP_EVENT_MASK2_TIMEOUT		0x02	//- - - -   - - X - 1 = disable time-out event and functionality (6Ah).
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: reserved
	#define HP_EVENT_MASK2_RESERVED2	0x04	//- - - -   - X - - reserved. 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable voice presence event (6Ch)
	#define HP_EVENT_MASK2_VOICE		0x08	//- - - -   X - - - 1 = disable voice presence event (6Ch). 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: reserved
	#define HP_EVENT_MASK2_RESERVED4	0x10	//- - - X   - - - - reserved. 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable fax/answer tone event (6Fh)
	#define HP_EVENT_MASK2_FAX_ANSWER	0x20	//- - X -   - - - - 1 = disable fax/answer tone event (6Fh). 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable incoming ring events (76h, 7Eh)
	#define HP_EVENT_MASK2_LINERING		0x40	//- X - -   - - - - 1 = disable incoming ring events (76h, 7Eh). 
	
	///HPCMD_SET_EVENT_MASK_2 Command Data: disable caller-ID event (E1h)
	#define HP_EVENT_MASK2_CID			0x80	//X - - -   - - - - 1 = disable caller-ID event (E1h). 


/// Sets events mask (Group 3)
#define HPCMD_SET_EVENT_MASK_3			0x00A9  

	// HPCMD_SET_EVENT_MASK_3 Command Data:
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: disable incoming call waiting event (77h)
	#define HP_EVENT_MASK3_CALLWAITING	0x01	//- - - -   - - - X 1 = disable incoming call waiting event (77h). 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: disable caller-ID on call-waiting event  and functionality (E4h) - default
	#define HP_EVENT_MASK3_CWCID		0x02	//- - - -   - - X - 1 = disable caller-ID on call-waiting event  and functionality (E4h) - default. 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: disable incoming fax event (6Eh)
	#define HP_EVENT_MASK3_FAX_INCOM	0x04	//- - - -   - X - - 1 = disable incoming fax event (6Eh). 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: reserved, read as 0
	#define HP_EVENT_MASK3_RESERVED3	0x08	//- - - -   X - - - reserved, read as 0. 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: reserved, read as 0
	#define HP_EVENT_MASK3_RESERVED4	0x10	//- - - X   - - - - reserved, read as 0. 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: reserved, read as 0
	#define HP_EVENT_MASK3_RESERVED5	0x20	//- - X -   - - - - reserved, read as 0. 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: reserved, read as 0
	#define HP_EVENT_MASK3_RESERVED6	0x40	//- X - -   - - - - reserved, read as 0. 
	
	/// HPCMD_SET_EVENT_MASK_3 Command Data: reserved, read as 0
	#define HP_EVENT_MASK3_RESERVED7	0x80	//X - - -   - - - - reserved, read as 0. 


/// Hi-Phone Desktop USB h/w version 30 and up: Set DAA Gain to off (default)
#define HPCMD_SET_DAA_GAIN_OFF			0x0026; 

/// Hi-Phone Desktop USB h/w version 30 and up: Set DAA Gain to on
#define HPCMD_SET_DAA_GAIN_ON			0x0036;

/// Hi-Phone Desktop Lite: Set Phone power current boost to off (default)
#define HPCMD_SET_PHONE_CURRENT_BOOST_OFF	0x0046

/// Hi-Phone Desktop Lite: Set Phone power current boost to on
#define HPCMD_SET_PHONE_CURRENT_BOOST_ON    0x0056


/**Toggle polarity for local phone (SLIC) Polaruty.
This also known as 'Line Polarity Reversal' for local phone.
*/
#define HPCMD_SET_PHONE_POLARITY    0x0066


// International Hardware 
#define IH_CMD_HRADWARE_SETUP		0x45	/// Hardware Setup Command
#define IH_CMD_SETUP_CHIP_REGISTER	0x01	/// Chip Registers setup command
#define IH_CMD_SETUP_STANDARD		0x02	/// Standards setup command






//===================================================================
// Hi-Phone Events

/**DTMF detected.

!dwEventData is DTMF Key Code:

!DTMF Key Codes

||DTMF Key||Code||Value
|0|HPEVT_DTMF_0|0x00
|1|HPEVT_DTMF_1|0x01
|2|HPEVT_DTMF_2|0x02
|3|HPEVT_DTMF_3|0x03
|4|HPEVT_DTMF_4|0x04
|5|HPEVT_DTMF_5|0x05
|6|HPEVT_DTMF_6|0x06
|7|HPEVT_DTMF_7|0x07
|8|HPEVT_DTMF_8|0x08
|9|HPEVT_DTMF_9|0x09
|A|HPEVT_DTMF_A|0x0A
|B|HPEVT_DTMF_B|0x0B
|C|HPEVT_DTMF_C|0x0C
|D|HPEVT_DTMF_D|0x0D
|*|HPEVT_DTMF_STAR|0x0E
|\#|HPEVT_DTMF_POUND|0x0F


!dwData is DTMF Origin:

-# HPEVT_DTMF_ORIGIN_COMMON
-# HPEVT_DTMF_ORIGIN_PHONE
-# HPEVT_DTMF_ORIGIN_LINE



*/
#define HPEVT_DTMF						0x0040


/// The DTMF origin is common: Line and/or Phone.
#define HPEVT_DTMF_ORIGIN_COMMON 0

/// The DTMF origin is Phone.
#define HPEVT_DTMF_ORIGIN_PHONE 1

/// The DTMF origin is Line.
#define HPEVT_DTMF_ORIGIN_LINE 2


/**USB Phone Key pushed down.
Event Data == USB Phone Keypad Key Codes.
*/
#define HPEVT_PHONE_KEYPAD_KEY_PUSHED	HPEVT_DTMF	  

	// HPEVT_DTMF Key Codes

	/// DTMF '0'
	#define HPEVT_DTMF_0				0x00

	/// DTMF '1'
	#define HPEVT_DTMF_1				0x01

	/// DTMF '2'
	#define HPEVT_DTMF_2				0x02

	/// DTMF '3'
	#define HPEVT_DTMF_3				0x03

	/// DTMF '4'
	#define HPEVT_DTMF_4				0x04

	/// DTMF '5'
	#define HPEVT_DTMF_5				0x05

	/// DTMF '6'
	#define HPEVT_DTMF_6				0x06

	/// DTMF '7'
	#define HPEVT_DTMF_7				0x07

	/// DTMF '8'
	#define HPEVT_DTMF_8				0x08

	/// DTMF '9'
	#define HPEVT_DTMF_9				0x09

	/// DTMF 'A'
	#define HPEVT_DTMF_A				0x0A

	/// DTMF 'B'
	#define HPEVT_DTMF_B				0x0B

	/// DTMF 'C'
	#define HPEVT_DTMF_C				0x0C

	/// DTMF 'D'
	#define HPEVT_DTMF_D				0x0D

	/// DTMF '*'
	#define HPEVT_DTMF_STAR				0x0E 

	/// DTMF '#'
	#define HPEVT_DTMF_POUND			0x0F 



	// USB Phone Keypad Key Codes
	#define HPEVT_KEYPAD_0				HPEVT_DTMF_0
	#define HPEVT_KEYPAD_1				HPEVT_DTMF_1
	#define HPEVT_KEYPAD_2				HPEVT_DTMF_2
	#define HPEVT_KEYPAD_3				HPEVT_DTMF_3
	#define HPEVT_KEYPAD_4				HPEVT_DTMF_4
	#define HPEVT_KEYPAD_5				HPEVT_DTMF_5
	#define HPEVT_KEYPAD_6				HPEVT_DTMF_6
	#define HPEVT_KEYPAD_7				HPEVT_DTMF_7
	#define HPEVT_KEYPAD_8				HPEVT_DTMF_8
	#define HPEVT_KEYPAD_9				HPEVT_DTMF_9
	#define HPEVT_KEYPAD_STAR			HPEVT_DTMF_STAR   // *
	#define HPEVT_KEYPAD_POUND			HPEVT_DTMF_POUND  // #
	
	/// 'Hot' Key
	#define HPEVT_KEYPAD_HOTKEY			0x11

	/// 'Up' Key
	#define HPEVT_KEYPAD_UP				0x12	

	/// 'Down' Key
	#define HPEVT_KEYPAD_DOWN			0x13

	/// 'Send' (make call) Key
	#define HPEVT_KEYPAD_SEND			0x14	

	/// 'Redial' Key
	#define HPEVT_KEYPAD_REDIAL			0x15	

	/// 'End' (end call) Key
	#define HPEVT_KEYPAD_END			0x16	


/*
#define HPEVT_PULSE_KEY             0x0050  /// Pulses dialed. Event data = dialed number
	#define HPEVT_PULSE_0				0x00
	#define HPEVT_PULSE_1				0x01
	#define HPEVT_PULSE_2				0x02
	#define HPEVT_PULSE_3				0x03
	#define HPEVT_PULSE_4				0x04
	#define HPEVT_PULSE_5				0x05
	#define HPEVT_PULSE_6				0x06
	#define HPEVT_PULSE_7				0x07
	#define HPEVT_PULSE_8				0x08
	#define HPEVT_PULSE_9				0x09
*/

/// DTMF key released
#define HPEVT_DTMF_END              0x005F

/// USB Phone Key released
#define HPEVT_PHONE_KEYPAD_KEY_RELEASED	HPEVT_DTMF_END 


/// Local Handset Off-Hook
#define HPEVT_PHONE_OFF_HOOK		0x0063

/// Local Handset On-Hook
#define HPEVT_PHONE_ON_HOOK			0x0062

/// Local Handset Hook-Flash dialed
#define HPEVT_PHONE_HOOK_FLASH		0x0061


/** Parallel Phone Off-Hook.
Some Hi-Phone devices (Pro., Maestro),
can detect that other phones,
connected somwhere else on the same line,
has changed their hook state.

Check  w2c_CapsBits_tag.bParallelPhoneHookDetect

!See:
- HPEVT_PARALLEL_PHONE_ON_HOOK

*/
#define HPEVT_PARALLEL_PHONE_OFF_HOOK 0x0162

/** Parallel Phone On-Hook.
Some Hi-Phone devices (Pro., Maestro),
can detect that other phones,
connected somwhere else on the same line,
has changed their hook state.

Check  w2c_CapsBits_tag.bParallelPhoneHookDetect

!See:
- HPEVT_PARALLEL_PHONE_OFF_HOOK

*/
#define HPEVT_PARALLEL_PHONE_ON_HOOK  0x0163


/// Headset-1 plugged OUT
#define HPEVT_HEADSET1_OUT			0x0064

/// Headset-1 plugged IN
#define HPEVT_HEADSET1_IN			0x0065

/// Headset-2 plugged OUT
#define HPEVT_HEADSET2_OUT			0x0066

/// Headset-2 plugged IN
#define HPEVT_HEADSET2_IN			0x0067


// Call Progress Events:

/** Dial Tone Detected.

||Event's Data||Description
|HPEVT_CP_DIALTONE_NORMAL|Normal Dial Tone
|HPEVT_CP_DIALTONE_PABX|PABX Dial TOne
|HPEVT_CP_DIALTONE_SECOND_1|Second Dial Tone #1
|HPEVT_CP_DIALTONE_SECOND_2|Second Dial Tone #2
|HPEVT_CP_DIALTONE_SPECIAL|Special Dial Tone
|HPEVT_CP_DIALTONE_SPECIAL_TRANSMITION|Special Transmission Dial Tone

*/
#define HPEVT_CALLPROGRESS_DIALTONE				0x0068  

	// HPEVT_CALLPROGRESS_DIALTONE Event Data
	///HPEVT_CALLPROGRESS_DIALTONE Event Data: Normal Dial Tone
	#define HPEVT_CP_DIALTONE_NORMAL				0

	///HPEVT_CALLPROGRESS_DIALTONE Event Data: PABX Dial TOne
	#define HPEVT_CP_DIALTONE_PABX					1

	///HPEVT_CALLPROGRESS_DIALTONE Event Data: Second Dial Tone #1
	#define HPEVT_CP_DIALTONE_SECOND_1				2

	///HPEVT_CALLPROGRESS_DIALTONE Event Data: Second Dial Tone #2
	#define HPEVT_CP_DIALTONE_SECOND_2				3

	///HPEVT_CALLPROGRESS_DIALTONE Event Data: Special Dial Tone
	#define HPEVT_CP_DIALTONE_SPECIAL				4

	///HPEVT_CALLPROGRESS_DIALTONE Event Data: Special Transmission Dial Tone
	#define HPEVT_CP_DIALTONE_SPECIAL_TRANSMITION	5


/** Stutter dial tone Detected.
||Event's Data||Description
|HPEVT_CP_STUTTER_TONE_NORMAL|Normal
|HPEVT_CP_STUTTER_TONE_RECALL|Recall

*/
#define HPEVT_CALLPROGRESS_STUTTER_TONE			0x0069

	//HPEVT_CALLPROGRESS_STUTTER_TONE Event Data

	///HPEVT_CALLPROGRESS_STUTTER_TONE Event Data: Normal
	#define HPEVT_CP_STUTTER_TONE_NORMAL		0

	///HPEVT_CALLPROGRESS_STUTTER_TONE Event Data: Recall
	#define HPEVT_CP_STUTTER_TONE_RECALL		1


/// No signal detected  (Dial Tone).
#define HPEVT_CALLPROGRESS_TIMEOUT				0x006A

/** BUSY Detected.

||Event's Data||Description
|HPEVT_CP_BUSY_NORMAL|Normal
|HPEVT_CP_BUSY_BUSY1|Busy I
|HPEVT_CP_BUSY_BUSY2|Busy II

*/
#define HPEVT_CALLPROGRESS_BUSY					0x006B  

	//HPEVT_CALLPROGRESS_BUSY  Event Data
	///HPEVT_CALLPROGRESS_BUSY  Event Data: Normal
	#define HPEVT_CP_BUSY_NORMAL				0

	///HPEVT_CALLPROGRESS_BUSY  Event Data: Busy I
	#define HPEVT_CP_BUSY_BUSY1					1

	///HPEVT_CALLPROGRESS_BUSY  Event Data: Busy II
	#define HPEVT_CP_BUSY_BUSY2					2

/**The call was answered.
||Event's Data||Description
|HPEVT_CP_CALL_ANSWERED_VOICE|A human voice was detected
|HPEVT_CP_CALL_ANSWERED_SPEECH|A human speech was detected
|HPEVT_CP_CALL_ANSWERED_MACHINE|Answering machine was detected +

+ Currently not implemeted.

!See:
- HPCMD_SET_VOICE_THRESHOLD

 

*/
#define HPEVT_CALLPROGRESS_CALL_ANSWERED		0x006C

	/**HPEVT_CALLPROGRESS_CALL_ANSWERED Event Data:
	A human voice was detected.
	*/
	#define HPEVT_CP_CALL_ANSWERED_VOICE			0

	/**HPEVT_CALLPROGRESS_CALL_ANSWERED Event Data:
	A human speech was detected.
	*/
	#define HPEVT_CP_CALL_ANSWERED_SPEECH			1

	/**HPEVT_CALLPROGRESS_CALL_ANSWERED Event Data:
	Answering machine was detected.
	Currently not implemeted.
	*/
	#define HPEVT_CP_CALL_ANSWERED_MACHINE			2



/** Ringback Detected.

||Event's Data||Description
|HPEVT_CP_RINGBACK_NORMAL|Normal
|HPEVT_CP_RINGBACK_RINGBACK1|Ringback I
|HPEVT_CP_RINGBACK_RINGBACK2|Ringback II
|HPEVT_CP_RINGBACK_RINGBACK3|Ringback III
|HPEVT_CP_RINGBACK_RINGBACK4|Ringback IV

*/
#define HPEVT_CALLPROGRESS_RINGBACK				0x006D
	
	//HPEVT_CALLPROGRESS_RINGBACK Event Data

	///HPEVT_CALLPROGRESS_RINGBACK Event Data: Normal
	#define HPEVT_CP_RINGBACK_NORMAL			0

	///HPEVT_CALLPROGRESS_RINGBACK Event Data: Ringback I
	#define HPEVT_CP_RINGBACK_RINGBACK1			1

	///HPEVT_CALLPROGRESS_RINGBACK Event Data: Ringback II
	#define HPEVT_CP_RINGBACK_RINGBACK2			2

	///HPEVT_CALLPROGRESS_RINGBACK Event Data: Ringback III
	#define HPEVT_CP_RINGBACK_RINGBACK3			3

	///HPEVT_CALLPROGRESS_RINGBACK Event Data: Ringback IV
	#define HPEVT_CP_RINGBACK_RINGBACK4			4


/// Incoming FAX Detected.
#define HPEVT_CALLPROGRESS_FAX_INCOMING			0x006E

/// FAX answer Detected.
#define HPEVT_CALLPROGRESS_FAX_ANSWER			0x006F  

/// Message Waiting tone detected.
#define HPEVT_CALLPROGRESS_MESSAGE_WAITING		0x0070

/// Confirmation tone detected.
#define HPEVT_CALLPROGRESS_CONFIRMATION_TONE	0x0071

/** Reorder (fast busy) tone detected.

||Event's Data||Description
|HPEVT_CP_REORDER_TONE_NORMAL|Normal
|HPEVT_CP_REORDER_TONE_REORDER1|Reorder I
|HPEVT_CP_REORDER_TONE_REORDER2|Reorder II

*/
#define HPEVT_CALLPROGRESS_REORDER_TONE			0x0072

	// HPEVT_CALLPROGRESS_REORDER_TONE	Event Data

	///HPEVT_CALLPROGRESS_REORDER_TONE	Event Data: Normal
	#define HPEVT_CP_REORDER_TONE_NORMAL		0

	///HPEVT_CALLPROGRESS_REORDER_TONE	Event Data: Reorder I
	#define HPEVT_CP_REORDER_TONE_REORDER1		1

	///HPEVT_CALLPROGRESS_REORDER_TONE	Event Data: Reorder II
	#define HPEVT_CP_REORDER_TONE_REORDER2		2

/** Incoming Call-Waiting detected.

||Event's Data||Description
|HPEVT_CP_CALL_WAITING_NORMAL|Normal
|HPEVT_CP_CALL_WAITING_1|Call-Waiting I
|HPEVT_CP_CALL_WAITING_2|Call-Waiting II


*/
#define HPEVT_CALLPROGRESS_CALL_WAITING			0x0077 
	
	// HPEVT_CALLPROGRESS_CALL_WAITING 	Event Data

	///HPEVT_CALLPROGRESS_CALL_WAITING 	Event Data: Normal
	#define HPEVT_CP_CALL_WAITING_NORMAL		0

	///HPEVT_CALLPROGRESS_CALL_WAITING 	Event Data: Call-Waiting I
	#define HPEVT_CP_CALL_WAITING_1				1

	///HPEVT_CALLPROGRESS_CALL_WAITING 	Event Data: Call-Waiting II
	#define HPEVT_CP_CALL_WAITING_2				2
	

/**Special Information Tone ( SIT ) detected.
Event data is the SIT sequence that can be:

||Event's Data||Description
|HPEVT_CP_SIT_UNKNOWN|Unknown
|HPEVT_CP_SIT_OPERATOR_INTERCEPT_VACANT_CIRCUIT|Operator Intercept or Vacant Circuit
|HPEVT_CP_SIT_NO_CIRCUIT|No Circuit Found
|HPEVT_CP_SIT_REORDER|Reorder
|HPEVT_CP_SIT_1|Generic SIT I
|HPEVT_CP_SIT_2|Generic SIT II

*/
#define HPEVT_CALLPROGRESS_SIT					0x00A0  

	// HPEVT_CALLPROGRESS_SIT Event Data:
	
	///HPEVT_CALLPROGRESS_SIT Event Data: Unknown
	#define HPEVT_CP_SIT_UNKNOWN				0 /// Unknown
	
	///HPEVT_CALLPROGRESS_SIT Event Data: Operator Intercept or Vacant Circuit
	#define HPEVT_CP_SIT_OPERATOR_INTERCEPT_VACANT_CIRCUIT	1

	///HPEVT_CALLPROGRESS_SIT Event Data: No Circuit Found
	#define HPEVT_CP_SIT_NO_CIRCUIT				2

	///HPEVT_CALLPROGRESS_SIT Event Data: Reorder
	#define HPEVT_CP_SIT_REORDER				3

	///HPEVT_CALLPROGRESS_SIT Event Data: Generic SIT I
	#define HPEVT_CP_SIT_1						4

	///HPEVT_CALLPROGRESS_SIT Event Data: Generic SIT II
	#define HPEVT_CP_SIT_2						5


/** Warning tone detected.

||Event's Data||Description
|HPEVT_CP_WARNING_TONE_NORMAL|Normal
|HPEVT_CP_WARNING_TONE_1|Warning I
|HPEVT_CP_WARNING_TONE_2|Warning II
|HPEVT_CP_WARNING_TONE_3|Warning III
|HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING|Operator Intervening
|HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING_PABX|Operator Intervening PABX
|HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING1|perator Intervening  I
|HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING2|perator Intervening  II
|HPEVT_CP_WARNING_TONE_INTRUSION|Intrusion
|HPEVT_CP_WARNING_TONE_INTERCEPT|Intercept
|HPEVT_CP_WARNING_TONE_INTERCEPT_PABX|Intercept PABX
|HPEVT_CP_WARNING_TONE_END_PERIOD|End Of Period
|HPEVT_CP_WARNING_TONE_PIP|PIP

*/
#define HPEVT_CALLPROGRESS_WARNING_TONE			0x0201 

	// HPEVT_CALLPROGRESS_WARNING_TONE Event Data:

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Normal
	#define HPEVT_CP_WARNING_TONE_NORMAL					0

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Warning I
	#define HPEVT_CP_WARNING_TONE_1							1

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Warning II
	#define HPEVT_CP_WARNING_TONE_2							2

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Warning III
	#define HPEVT_CP_WARNING_TONE_3							3

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Operator Intervening
	#define HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING		4

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Operator Intervening PABX
	#define HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING_PABX	5

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Operator Intervening  I
	#define HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING1		6

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Operator Intervening  II
	#define HPEVT_CP_WARNING_TONE_OPERATOR_INTERVENING2		7

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Intrusion
	#define HPEVT_CP_WARNING_TONE_INTRUSION					8

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Intercept
	#define HPEVT_CP_WARNING_TONE_INTERCEPT					9

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: Intercept PABX
	#define HPEVT_CP_WARNING_TONE_INTERCEPT_PABX			10

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: End Of Period
	#define HPEVT_CP_WARNING_TONE_END_PERIOD				11

	///HPEVT_CALLPROGRESS_WARNING_TONE Event Data: PIP
	#define HPEVT_CP_WARNING_TONE_PIP						12
 
/** Pay Phone tone detected.
||Event's Data||Description
|HPEVT_CP_PAY_TONE_NORMAL|Normal
|HPEVT_CP_PAY_TONE_1|Pay Phone Recognition I
|HPEVT_CP_PAY_TONE_2|Pay Phone Recognition II
|HPEVT_CP_PAY_TONE_3|Pay Phone Recognition III
|HPEVT_CP_PAY_TONE_4|Pay Phone Recognition IV

*/
#define HPEVT_CALLPROGRESS_PAY_TONE				0x0202	

	// HPEVT_CALLPROGRESS_PAY_TONE Event Data:

	///HPEVT_CALLPROGRESS_PAY_TONE Event Data: Normal
	#define HPEVT_CP_PAY_TONE_NORMAL	0

	///HPEVT_CALLPROGRESS_PAY_TONE Event Data: Pay Phone Recognition I
	#define HPEVT_CP_PAY_TONE_1			1

	///HPEVT_CALLPROGRESS_PAY_TONE Event Data: Pay Phone Recognition II
	#define HPEVT_CP_PAY_TONE_2			2

	///HPEVT_CALLPROGRESS_PAY_TONE Event Data: Pay Phone Recognition III
	#define HPEVT_CP_PAY_TONE_3			3

	///HPEVT_CALLPROGRESS_PAY_TONE Event Data: Pay Phone Recognition IV
	#define HPEVT_CP_PAY_TONE_4			4


/** Indication tone detected.
||Event's Data||Description
|HPEVT_CP_INDICATION_TONE_NORMAL|Normal
|HPEVT_CP_INDICATION_TONE_POSETIVE|Posetive
|HPEVT_CP_INDICATION_TONE_NEGATIVE|Negative
|HPEVT_CP_INDICATION_TONE_NOTIFY|Notify
|HPEVT_CP_INDICATION_TONE_RECORD|Record
|HPEVT_CP_INDICATION_TONE_TEST_NUMBER|Test Number
|HPEVT_CP_INDICATION_TONE_PREEMPTION|Preemption
|HPEVT_CP_INDICATION_TONE_PREEMPTION_SIGNAL|Preemption Signal
|HPEVT_CP_INDICATION_TONE_IDENTIFICATION|Identification
|HPEVT_CP_INDICATION_TONE_EXECUTIVE_OVERIDE|Executive Override
|HPEVT_CP_INDICATION_TONE_EXECUTIVE_OVERIDE_PABX|Executive Override (PABX)
|HPEVT_CP_INDICATION_TONE_VALID|Valid Tone
|HPEVT_CP_INDICATION_TONE_FUNCTION_ACK|Function Acknowledge
|HPEVT_CP_INDICATION_TONE_REFUSAL|Refusal
|HPEVT_CP_INDICATION_TONE_ACCEPT|Acceptance
|HPEVT_CP_INDICATION_TONE_ROUTE1|Route I
|HPEVT_CP_INDICATION_TONE_ROUTE2|Route II


*/
#define HPEVT_CALLPROGRESS_INDICATION_TONE		0x0203	
	
	//HPEVT_CALLPROGRESS_INDICATION_TONE Event Data:

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Normal
	#define HPEVT_CP_INDICATION_TONE_NORMAL						0

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Posetive
	#define HPEVT_CP_INDICATION_TONE_POSETIVE					1

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Negative
	#define HPEVT_CP_INDICATION_TONE_NEGATIVE					2

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Notify
	#define HPEVT_CP_INDICATION_TONE_NOTIFY						3

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Record
	#define HPEVT_CP_INDICATION_TONE_RECORD						4

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Test Number
	#define HPEVT_CP_INDICATION_TONE_TEST_NUMBER				5

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Preemption
	#define HPEVT_CP_INDICATION_TONE_PREEMPTION					6

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Preemption Signal
	#define HPEVT_CP_INDICATION_TONE_PREEMPTION_SIGNAL			7

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Identification
	#define HPEVT_CP_INDICATION_TONE_IDENTIFICATION				8

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Executive Override
	#define HPEVT_CP_INDICATION_TONE_EXECUTIVE_OVERIDE			9

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Executive Override (PABX)
	#define HPEVT_CP_INDICATION_TONE_EXECUTIVE_OVERIDE_PABX		10

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Valid Tone
	#define HPEVT_CP_INDICATION_TONE_VALID						11

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Function Acknowledge
	#define HPEVT_CP_INDICATION_TONE_FUNCTION_ACK				12

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Refusal
	#define HPEVT_CP_INDICATION_TONE_REFUSAL					13

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Acceptance
	#define HPEVT_CP_INDICATION_TONE_ACCEPT						14

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Route I
	#define HPEVT_CP_INDICATION_TONE_ROUTE1						15

	///HPEVT_CALLPROGRESS_INDICATION_TONE Event Data: Route II
	#define HPEVT_CP_INDICATION_TONE_ROUTE2						16

/** Status tone detected.
||Event's Data||Description
|HPEVT_CP_STAUS_TONE_CONGESTION|Congestion
|HPEVT_CP_STAUS_TONE_CONGESTION1|Congestion I
|HPEVT_CP_STAUS_TONE_CONGESTION2|Congestion II
|HPEVT_CP_STAUS_TONE_WAITING|Waiting
|HPEVT_CP_STAUS_TONE_WAITING_PABX|Waiting (PABX)
|HPEVT_CP_STAUS_TONE_WAITING_OFFERING|Offering
|HPEVT_CP_STAUS_TONE_WAITING_HOLDING|Holding
|HPEVT_CP_STAUS_TONE_WAITING_CONNECTION|Connection
|HPEVT_CP_STAUS_TONE_WAITING_QUEUE|Queue
|HPEVT_CP_STAUS_TONE_WAITING_CONFERENCE|Conference
|HPEVT_CP_STAUS_TONE_WAITING_CONFORT|Comfort
|HPEVT_CP_STAUS_TONE_WAITING_SERVICE_ACTIVATED|Service Activated
|HPEVT_CP_STAUS_TONE_WAITING_END_3D_PARTY_SERVICE|End of Thered Party Service
|HPEVT_CP_STAUS_TONE_WAITING_PROCEEDING|Search (Proceeding)
|HPEVT_CP_STAUS_TONE_WAITING_LINE_LOCK_OUT|Line Lock Out


*/
#define HPEVT_CALLPROGRESS_STAUS_TONE			0x0204	

	//HPEVT_CALLPROGRESS_STAUS_TONE Event Data:

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Congestion
	#define HPEVT_CP_STAUS_TONE_CONGESTION						0

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Congestion I
	#define HPEVT_CP_STAUS_TONE_CONGESTION1						1

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Congestion II
	#define HPEVT_CP_STAUS_TONE_CONGESTION2						2

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Waiting
	#define HPEVT_CP_STAUS_TONE_WAITING							3

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Waiting (PABX)
	#define HPEVT_CP_STAUS_TONE_WAITING_PABX					4

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Offering
	#define HPEVT_CP_STAUS_TONE_WAITING_OFFERING				5

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Holding
	#define HPEVT_CP_STAUS_TONE_WAITING_HOLDING					6

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Connection
	#define HPEVT_CP_STAUS_TONE_WAITING_CONNECTION				7

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Queue
	#define HPEVT_CP_STAUS_TONE_WAITING_QUEUE					8

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Conference
	#define HPEVT_CP_STAUS_TONE_WAITING_CONFERENCE				9

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Comfort
	#define HPEVT_CP_STAUS_TONE_WAITING_CONFORT					10

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Service Activated
	#define HPEVT_CP_STAUS_TONE_WAITING_SERVICE_ACTIVATED		11

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: End of Thered Party Service
	#define HPEVT_CP_STAUS_TONE_WAITING_END_3D_PARTY_SERVICE	12

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Search (Proceeding)
	#define HPEVT_CP_STAUS_TONE_WAITING_PROCEEDING				13

	///HPEVT_CALLPROGRESS_STAUS_TONE Event Data: Line Lock Out
	#define HPEVT_CP_STAUS_TONE_WAITING_LINE_LOCK_OUT			14


/** Custom preset tone detected.

  Event's Data is HPEVT_CP_CUSTOM_TONE_0 to HPEVT_CP_CUSTOM_TONE_9
*/
#define HPEVT_CALLPROGRESS_CUSTOM_TONE			0x205	
	
	//HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data:

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #0
	#define HPEVT_CP_CUSTOM_TONE_0	0
	
	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #1
	#define HPEVT_CP_CUSTOM_TONE_1	1

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #2
	#define HPEVT_CP_CUSTOM_TONE_2	2

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #3
	#define HPEVT_CP_CUSTOM_TONE_3	3

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #4
	#define HPEVT_CP_CUSTOM_TONE_4	4

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #5
	#define HPEVT_CP_CUSTOM_TONE_5	5

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #6
	#define HPEVT_CP_CUSTOM_TONE_6	6

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #7
	#define HPEVT_CP_CUSTOM_TONE_7	7

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #8
	#define HPEVT_CP_CUSTOM_TONE_8	8

	///HPEVT_CALLPROGRESS_CUSTOM_TONE Event Data: custom ton #9
	#define HPEVT_CP_CUSTOM_TONE_9	9




/// Tone monitored. Event's lpBuffer is a pointer to a TONESCALLBACK struct
#define HPEVT_MONITOR_TONE			0x00E5
											/// 

/// End of ringer burst
#define HPEVT_RINGER_BURST_STOP		0x0074  

/// Start of ringer burst
#define HPEVT_RINGER_BURST_START	0x0075  

/**Incoming RING.
!See:
- HPEVT_LINE_RING_END
- w2cUsbM_GetNumRings
- w2cUsbM_DistinctiveRingDialog
- "Distinctive Ring Setup"
*/
#define HPEVT_LINE_RING_START		0x0076  


/**Incoming RING End Period.
Event data = ring pattern.
0 == default Pattern, 1 and up == defined pattern.
!See:
- HPEVT_LINE_RING_START
- w2cUsbM_GetNumRings
- w2cUsbM_DistinctiveRingDialog
- "Distinctive Ring Setup"
*/
#define HPEVT_LINE_RING_END         0x007E

/** Line Current Droped.
Some phone line will drop the line current
and then restore it (Wink)
to indicate that other party has hanged up the call.
!See:
- HPEVT_LINE_CURRENT_RESTORED
*/
#define HPEVT_LINE_CURRENT_DROPED	0x0078

/** Line Current Restored.
Some phone line will drop the line current
and then restore it (Wink)
to indicate that other party has hanged up the call.
!See:
- HPEVT_LINE_CURRENT_DROPED
*/
#define HPEVT_LINE_CURRENT_RESTORED	0x0079


/**The line wire is unplugged.
Calls cannot be answered or made.

This feature is supported on the following Devices:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO

Note:

When the Hi-Phone is in its default switching mode, HPCMD_SW_DEFAULT_PHONE_LINE, 
And there is a local phone connected,
It may take up to 20 seconds to report (fire) this event
since the local phone keeps the line's electrical energy charge
(after the line wire has been unplugged) for up to 20 seconds.

When the Hi-Phone is in other switching modes where the local phone
is not connected to the line, this event fires as soon as possible,
(maximum 1 second time frame).

See Also:
HPEVT_LINE_PLUGGED
w2cUsbM_GetDeviceLineWirePlugged
W2C_ERR_LINE_NOT_CONNECTED

*/
#define HPEVT_LINE_UNPLUGGED	0x0178


/**The line wire is plugged.
Calls can be answered or made.

This feature is supported on the following Devices:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO

\note
This feature can be used by application to generate alarm each time
the line wire is unplugged.


!See:
- HPEVT_LINE_UNPLUGGED
- w2cUsbM_GetDeviceLineWirePlugged

*/
#define HPEVT_LINE_PLUGGED		0x0179


/** Caller-ID data Detected.
for HPEVT_LINE_CALLER_ID and HPEVT_LINE_CALL_WAITING_CID events,
Event Data is buffer length and, 
lpBuffer is the native CID Message Buffer in MDMF standard.
Call w2cUsbM_GetCidString to get a parsed null terminated string.
*/
#define HPEVT_LINE_CALLER_ID		0x00E1


/**Call waiting Caller-ID data Detected.
for HPEVT_LINE_CALLER_ID and HPEVT_LINE_CALL_WAITING_CID events,
Event Data is buffer length and, 
lpBuffer is the native CID Message Buffer in MDMF standard.
Call w2cUsbM_GetCidString to get a parsed null terminated string.
*/
#define HPEVT_LINE_CALL_WAITING_CID	0x00E4





/**A Terminal (Phone or Headset) hardware events  has been Detached from this line.
Valid for Maestro device only W2C_DEV_MODEL_MAESTRO.

The HiPhoneCallbackProc dwEventData can be a combinations of these flags:

- W2C_TERMMODE_RINGER
- W2C_TERMMODE_HOOKSWITCH
- W2C_TERMMODE_PLUGGED

Note that the audio to/from terminal can still be active.

!See:
- w2cUsbM_SetTerminal

*/
#define HP_EVENT_LINE_TERMINAL_CHANGED  0x0170

/**Internal Maestro Matrix write error.
Valid for Maestro device only W2C_DEV_MODEL_MAESTRO.

This error occures when Maestro featurs are not supported
or when ilegal source->destination connection has been requested.

Event's data is error codes bit map:
Bit 0: 1 == Invalid Matrix write.  
Bit 1: 1 == Illegal Matrix write, feature not supported or locked.
Bit 2: 1 == Matrix overloaded, If the write will overload the matrix.


!See:
- w2cUsbM_ConferenceAdd

*/
#define HP_EVENT_MATRIX_ERROR  0x0171




/**Notifies a device that it has been connected to a conference.
Valid for Maestro device only W2C_DEV_MODEL_MAESTRO.


The HiPhoneCallbackProc dwEventData specifies Conference ID
to which it has been connected to.

To find out whice devices are conferenced, use w2cUsbM_ConferenceGetMembers.

!See:
- HP_EVENT_CONFERENCE_DISCONNECTED
- W2C_CONFERENCE_ID_MAESTRO_A
- W2C_CONFERENCE_ID_MAESTRO_B
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"
*/
#define HP_EVENT_CONFERENCE_CONNECTED 0x172


/**Notifies a device that it has been disconnected from conference.
Valid for Maestro device only W2C_DEV_MODEL_MAESTRO.

The HiPhoneCallbackProc dwEventData specifies the Conference ID
which it has been disconnected from.

!See:
- HP_EVENT_CONFERENCE_CONNECTED
- W2C_CONFERENCE_ID_MAESTRO_A
- W2C_CONFERENCE_ID_MAESTRO_B
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"
*/
#define HP_EVENT_CONFERENCE_DISCONNECTED 0x173





/** Device Reset Occured.
Normaly the first event send when opening a device.
Its indicating that the device starts at a known state.
*/
#define HPEVT_DEVICE_RESET			0x007F

/**Device Unplugged.
The device's USB / RS232 cable was physically disconnected from the PC.
\n It is recommended that application will re-initilize its Hi-Phone use.
*/
#define HPEVT_DEVICE_UNPLUGGED		0x00F0




// Aynchronus operation complete events

/// Reporting H/W model code. Event data = model
#define HPEVT_NOTIFY_MODEL          0x00C0

/// Reporting H/W revision. Event data = revision
#define HPEVT_NOTIFY_REVISION       0x00C1  

/// Reporting H/W status1.
#define HPEVT_NOTIFY_STATUS1		0x00C8  

/// Reporting H/W status2.
#define HPEVT_NOTIFY_STATUS2		0x00C9  

/// Reporting Wait-For-Dialtone time.
#define HPEVT_NOTIFY_WAIT_DIALTONE	0x00CA  

/// Reporting Wait-For-Answer time.
#define HPEVT_NOTIFY_WAIT_ANSWER	0x00CB  

/// Reporting DTMF speed.
#define HPEVT_NOTIFY_DTMF_SPEED		0x00CC  

/// Reporting Pause (comma) delay.
#define HPEVT_NOTIFY_PAUSE_TIME		0x00CD  



/** Call Dialing is done.
See w2cUsbM_Call
*/
#define HP_EVENT_ASYNC_CALL_DIALING_DONE	0x01F1

/** Playback is done.
See w2cUsbM_PlayWaveFile
*/
#define HP_EVENT_ASYNC_PLAYBACK_DONE		0x01F2

/** Caller ID Generation is done.

See w2cUsbM_GenerateCallerID

*/
#define HP_EVENT_ASYNC_CID_GENERATION_DONE	0x01F3  



	
	









/**Volume has changed
dwEventData == Which volume control has changed.
Can be one of:
HP_PhoneOutVolume
HP_PhoneInVolume
HP_PhoneLineVolume
HP_PhonePlaybackVolume
HP_PhoneRecordingVolume
HP_HeadsetOutVolume
HP_HeadsetInVolume
HP_HeadsetSideToneVolume
HP_HeadsetLineVolume
HP_HeadsetPlaybackVolume
HP_HeadsetRecordingVolume
HP_LinePlaybackVolume
HP_LineRecordingVolume

dwData == New Volume value.

||dwData value||Volume
|0|Mute
|781|-29dB
|1561|-28dB
|2341|-27dB
|3121|-26dB
|3901|-25dB
|4682|-24dB
|5462|-23dB
|6242|-22dB
|7022|-21dB
|7802|-20dB
|8582|-19dB
|9363|-18dB
|10143|-17dB
|10923|-16dB
|11703|-15dB
|12483|-14dB
|13263|-13dB
|14044|-12dB
|14824|-11dB
|15604|-10dB
|16384|-9dB
|17164|-8dB
|17944|-7dB
|18725|-6dB
|19505|-5dB
|20285|-4dB
|21065|-3dB
|21845|-2dB
|22625|-1dB
||23406||0dB
|24186|+1dB
|24966|+2dB
|25746|+3dB
|26526|+4dB
|27306|+5dB
|28087|+6dB
|28867|+7dB
|29647|+8dB
|30427|+9dB
|31207|+10dB
|31987|+11dB
|32767|+12dB


!See:
- w2cUsbM_ThumbWheelAssign
- HPEVT_THUMB_WHEEL_REASSIGNED

*/
#define HPEVT_VOLUME_CHANGED		0x0400

/**The Thumb Wheel has been reaasigned to other device.
For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

dwData == thumb weel reassig device ID.

!See:
- w2cUsbM_ThumbWheelAssign
- HPEVT_VOLUME_CHANGED

*/
#define HPEVT_THUMB_WHEEL_REASSIGNED 0x401
  

/**Force TSP to report 'call connected'.
Currently for exclusive Way2call use.

!See:
- HPEVT_CALLPROGRESS_CALL_ANSWERED

*/
#define HPEVT_FORCE_CALL_CONNECTED 0x6C6C


// ===================================================================
// Error values that can be returned from the Hi-Phone driver / device

/// Success. Value: 0
#define W2C_ERR_SUCCESS                  0       

/// Invalid pointer in parameters. Value: -1
#define W2C_ERR_INVALID_POINTER          -1      

/// Parameter(s), or Parameter value is wrong. Value: -2
#define W2C_ERR_INVALID_PARAMETERS       -2      

/// Unspecified error. Value: -3
#define W2C_ERR_UNKNOWN                  -3      

/// Error loading the driver (file missing ...). Value: -4
#define W2C_ERR_NO_DRIVER                -4      

/// Error in hardware device. Value: -5
#define W2C_ERR_HARDWARE                 -5      

/// Device already open. Value: -6
#define W2C_ERR_ALREADY_OPEN             -6      

/// Device is not open. Value: -7
#define W2C_ERR_DEVICE_NOT_OPEN          -7      

/// Can not complete operation - handset is on the hook. Value: -8
#define W2C_ERR_HOOK_ON                  -8      

/// Overflow error. Value: -9
#define W2C_ERR_OVERFLOW                 -9      

/// Invalid command requested. Value: -10
#define W2C_ERR_INVALID_COMMAND          -10     

/// Memory error. Value: -11
#define W2C_ERR_NO_MEMORY                -11     

/// Output buffers full. Value: -12
#define W2C_ERR_QUEUE_FULL               -12     

/// Illegal buffer resolution. Value: -13
#define W2C_ERR_INVALID_RESOLUTION       -13     

/// Parameter is reserved (must be 0). Value: -14
#define W2C_ERR_RESERVED_PARAMETER       -14     

/// Device not initialized. Value: -15
#define W2C_ERR_DEVICE_NOT_INIT          -15     

/// The audion stream is open. Value: -16
#define W2C_ERR_AUDIO_OPEN               -16     

/// The driver is already initialized
#define W2C_ERR_ALREADY_INITIALIZED      -17		

/// The dll does not support the current driver version.. Value: -18
#define W2C_ERR_UNSUPPORTED_DRIVER		 -18     

/// The driver was not initialized. Value: -19
#define W2C_ERR_DRIVER_NOT_INITED		 -19     

/// Invalid device ID. Value: -20
#define W2C_ERR_INVALID_DEVICE_ID		 -20     

/// error allocating memory. Value: -21
#define W2C_ERR_MEMORY_ALLOCATION		 -21     

/// The specified feature does not exists in the specified device. Value: -22
#define W2C_ERR_NO_DEVICE_FEATURE		 -22     

/// The requested peration is still currently executing. Value: -23
#define W2C_ERR_OPERATION_STILL_EXEC     -23


/** The Line wire (cord) is physically not connected. Value: -24
Calls on this line can not be made.

Other possible reason:
The Line provider (PSTN, PBX) has dropped the current for this line.

!See:
- w2cUsbM_GetDeviceLineWirePlugged
- w2cUsbM_Call
- HPEVT_LINE_UNPLUGGED

*/
#define W2C_ERR_LINE_NOT_CONNECTED       -24

/**Parallel device is Off-Hook. Value: -25
A parallel device (Phone, FAX) connected to the
same line as the Hi-Phone, is Off-Hook.

This feature is supported on some Hi-Phone Devices.
Check  w2c_CapsBits_tag.bParallelPhoneHookDetect

!See:
- HPEVT_PARALLEL_PHONE_OFF_HOOK


*/
#define W2C_ERR_LINE_PARALLEL_DEVICE_OFF_HOOK     -25
	
/**Line operation cannot be done since it is closed for making or answering calls.



*/
#define W2C_ERR_LINE_CLOSED					-26




// Adjustable Parameters Indexs
/**Dial Tone time out in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_WAIT_DIALTONE_TIMEOUT	0

/**Detection Timeout (No Dial Tone) in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_WAIT_ANSWER_TIMEOUT		1

/**DTMF Dial Time in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DTMF_DIAL_TIME			2

/**Dial Pause duration in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DIAL_PAUSE_TIME			3

/**DTMF detection time in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DTMF_DETECT_TIME			4

/**Hook-Flash Dial time in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HOOK_FLASH_TIME			5

/**Hook-Flash pre - dial time in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HOOK_FLASH_PRE_TIME		6

/**Hook-Flash post - dial time in milliseconds
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HOOK_FLASH_POST_TIME		7

/**Hi-Phone DTMF Threshold for Line opened
!See:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_LITE_DTMF_TH_DAA_OFFHOOK		8

/**Hi-Phone DTMF Threshold for Line closed
!See:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_LITE_DTMF_TH_DAA_ONHOOK		9

/**Hi-Phone DTMF Threshold for CODEC
!See:
- W2C_DEV_MODEL_LITE
- W2C_DEV_MODEL_PRO
- W2C_DEV_MODEL_MAESTRO
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_LITE_DTMF_TH_CODEC			10


/**Voice detection threshold

Same as HPCMD_SET_VOICE_THRESHOLD  
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_VOICE_THRESHOLD				11

/**Call progress analysis signal to noise ratio for single tone
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DETECTION_SNR_SINGLE			12

/**Call progress analysis signal to noise ratio for dual tone
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DETECTION_SNR_DUAL			13

/**Call progress analysis signal to noise ratio for tripple tone
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_DETECTION_SNR_TRIPPLE		14



/**Headset echo suppression parameter: silence threshold.
Range: 0 to 255, representing full range signal level,
Default: 8.

!See:
- HPCMD_HEADSET_ECHO_SUPPRESSION_ON
- HPCMD_HEADSET_ECHO_SUPPRESSION_OFF
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HEADSET_ECHO_SUPPRESSION_SILENCE_THRESHOLD		15




/**Headset echo suppression parameter: signal out-in difference threshold
Range: -128 to +127, representing full range signal level,
Default: 0.

!See:
- HPCMD_HEADSET_ECHO_SUPPRESSION_ON
- HPCMD_HEADSET_ECHO_SUPPRESSION_OFF
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HEADSET_ECHO_SUPPRESSION_OUT2IN_DIFF_THRESHOLD		16


/**Headset echo suppression parameter: signal supression off time. 
Range: 10 to 2550, 10msec taps where the signal level decays by 1dB
Default: 1.

!See:
- HPCMD_HEADSET_ECHO_SUPPRESSION_ON
- HPCMD_HEADSET_ECHO_SUPPRESSION_OFF
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HEADSET_ECHO_SUPPRESSION_OFF_TIME		17


/**Headset echo suppression parameter: signal supression on time. 
Range: 10 to 2550, 10msec taps where the signal level restored by 1dB.
Default: 7.

!See:
- HPCMD_HEADSET_ECHO_SUPPRESSION_ON
- HPCMD_HEADSET_ECHO_SUPPRESSION_OFF
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter
*/
#define W2C_AP_HEADSET_ECHO_SUPPRESSION_ON_TIME		18






/*
	Lite/Pro/Maestro DTMF Thresholds Range:0 to 30.
	Lite/Pro/Maestro DTMF Thresholds default values:
	1. DAA, local phone on-hook:	-30dBm.
	2. DAA, local phone off-hook:	-30dBm.
	3. Local Phone CODEC:			-20dBm.

	(parameters are received by HID as absolute values).

*/

/** Helper struct for adjustable parameters.
!See:
- w2cUsbM_SetParameterValue
- w2cUsbM_GetParameter

*/
typedef struct w2c_Parameter_tag
{

	/// Minimum Value
	DWORD dwMin;
	
	/// Maximum Value
	DWORD dwMax;
	
	/// Default Value
	DWORD dwDefault;
	
	/// Range
	DWORD dwRange;
	
	/// Current Value
	DWORD dwValue;

	/// Value description
	char cValueDescription[32];


}
/// Helper struct for adjustable parameters
W2C_PARAMETER,

/// Helper struct (pointer) for adjustable parameters
* LPW2C_PARAMETER;




/**Device Capabilities bit field struct.

  Member of (CapsBits) w2cDevCaps_tag.

  Used with w2cUsbM_GetDevCaps

*/
typedef struct w2c_CapsBits_tag
{
	///Device has phone
	unsigned char bPhone:				1;

	///Device has phone control
	unsigned char bPhoneControl:		1;

	///Device has Line
	unsigned char bLine:				1;
	
	///Device has Line Control
	unsigned char bLineControl:			1;
	
	///Device has Headset 1
	unsigned char bHeadset1:			1;
	
	///Device has Headset 1 control
	unsigned char bHeadset1Control:		1;
	
	///Device has legacy headset 2
	unsigned char bHeadset2:			1;
	
	///Device has Legacy headset 2 control
	unsigned char bHeadset2Control:		1;

	
	///Device has legacy microphone
	unsigned char bMic:					1;
	
	///Device has legacy microphone control
	unsigned char bMicControl:			1;
	
	///Device has legacy speaker
	unsigned char bSpeaker:				1;
	
	///Device has legacy speaker control
	unsigned char bSpeakerControl:		1;
	
	///Device can Dial DTMF
	unsigned char bDTMF_Dial:			1;
	
	///Device can Dial Hook-Flash 
	unsigned char bPulseDial_FlashHook:	1;
	
	///Device has call progress analysis
	unsigned char bLineAnalysis:		1;
	
	///Device can detect remote DTMF
	unsigned char bRemoteDTMF_Detect:	1;

	
	///Device can detect local DTMF
	unsigned char bLocalDTMF_Detect:	1;
	
	///Device can detect remote pulse dial
	unsigned char bRemotePulseDetect:	1;
	
	///Device can detect local pulse dial
	unsigned char bLocalPulseDetect:	1;
	
	///Device can detect local Hook Switch state
	unsigned char bHandSetOnOffDetect:	1;
	
	///Device can detect local Headset 1 plugged state
	unsigned char bHeadset1OnOffDetect:	1;
	
	///Device can detect local Headset 2 plugged state
	unsigned char bHeadset2OnOffDetect:	1;
	
	///Device can generate Hook-Flash when Off-Hook
	unsigned char bHookFlash_HS_OffHook:1;
	
	///Device can detect Caller ID
	unsigned char bCallerID_Detect:		1;



	
	///Device has Audio In
	unsigned char bAudioIn:				1;
	
	///Device has Audio Out
	unsigned char bAudioOut:			1;
	
	///Device has Ringer
	unsigned char bRinger:				1;
	
	///Device can detect Line Ring 
	unsigned char bRingDetect:			1;
	
	///Device has ringable buzzer
	unsigned char bRingableBuzzer:		1;
	
	///Device Ringer Frequency can be control
	unsigned char bRingerFreqCtrl:		1;
	
	///Device can generate Dial Tone
	unsigned char bDialToneGenerator:	1;
	
	///Device has extended capabilities
	unsigned char bExtendedCaps:		1;



// if bExtendedCaps member is set, the following caps bits are valid
	
	///Device can Mute its local devices Headset or Phone
	unsigned char bPhoneHeadsetMute:	1;
	
	///Device can select its local device: Headset or Phone
	unsigned char bPhoneHeadsetSwitch:	1;
	
	///Device can put the line on HOLD
	unsigned char bLineHold:			1;
	
	///Device's Line Interface (DAA) impedance can be controlled
	unsigned char bDAA_ImpedanceCtrl:	1;
	
	///Device has extended call progress analysis
	unsigned char bCallProgressEx:		1;
	
	///Device has extended call progress analysis gain control
	unsigned char bCallProgExGainCtrl:	1;
	
	///Device Audio Out can be active during analysis.
	unsigned char bAnalysisAudioOutEn:	1;
	
	///if set, Device has No SLIC(Subscriber Line Interface Circuit).
	unsigned char bNO_SLIC:				1;
	


	
	///Device can Mute its Line
	unsigned char bLineMute:			1;
	
	///Device has Hook-Flash time control 
	unsigned char bFlashHookGenTimeCtrl:1;
	
	///Device Legacy Keypad configuration
	unsigned char bKeypadConfig0:		1;
	
	///Device Legacy Keypad configuration
	unsigned char bKeypadConfig1:		1;
	
	///Device Legacy Keypad configuration
	unsigned char bKeypadConfig2:		1;
	
	///USB Phone(s), Local Hook-Switch can be controlled
	unsigned char bHandsetCtrl:			1;
	
	///Device has Line Current Monitor circuit
	unsigned char bLineCurrentMonitor:	1;
	
	///Device has hardware echo canceller
	unsigned char bHardwareEchoCancel:	1;
	

	///Device can detect SIT(Special Information Tone)
	unsigned char bSIT_Detect:			1;
	
	///Device can detect Call Waiting Caller ID
	unsigned char bCWCID_Event:			1;
	
	/// USB Phone(s): Ringer support melody
	unsigned char bRingerMelodies:		1;
	
	///Device has Caller ID Generator
	unsigned char bCID_Generator:		1;
	
	///Device can detect Distinctive Ring Patterns
	unsigned char bDistinctiveRing:		1;
	
	///Device supports LEDs Test
	unsigned char bLEDsTest:			1;
	
	///Device can detect Parallel Phone Hook Switch state.
	unsigned char bParallelPhoneHookDetect:		1;
	
	///More caps - reserved for future use
	unsigned char bMoreCaps:			1;


	/// Firmware version - build number
	unsigned char FirmwareBuild;		


}W2C_CPAS_BITS, * LPW2C_CPAS_BITS;






// ===================

/// Maximum name string size
#define MAX_W2C_DEV_STRING 128

/** Device Capabilities.
See w2cUsbM_GetDevCaps
*/ 
typedef struct w2cDevCaps_tag
{
	/// Structure size in bytes. #Must# be initialized #before# calling w2cUsbM_GetDevCaps.
	WORD   wCbSize;								
	
	/// Model W2C_DEV_MODEL_XXXXX
	WORD   wModel;
	
	/// Raw Firmware version
	WORD   wRawFirmwareVersion;					
	
	/// Firmware Version
	DWORD  dwFirmwareVersion;					
	
	/// Serial Number
	char   cSerialNumber[MAX_W2C_DEV_STRING];	

	/// Name
	char   cName[MAX_W2C_DEV_STRING];			
	
	/// CapsBits or 8 bCapsBytes union
	union
	{
		/// 8 device caps bytes.
		BYTE			bCapsBytes[8];

		/// w2c_CapsBits_tag nested struct
		W2C_CPAS_BITS	CapsBits;				
	};

	/// Associated wave out drv id
	UINT   uWaveOutDrvID;						
	
	/// Associated wave In drv id
	UINT   uWaveInDrvID;		
	
	/// Associated aux. wave In drv id
	UINT   uAuxWaveInDrvID;	
	
	/// Resereved, must be 0(zero).
	DWORD  dwReserved;							
} W2CDEVCAPS, *LPW2CDEVCAPS; 





/// Device Status Register 1, used with HPEVT_NOTIFY_STATUS1 event
typedef struct w2cDevReg1_tag
{

	/// 1==Audio to / from PC is active. 0 == Not active
	unsigned char bPcAudioActive :1;
	
	/// Reserved, do not use, set/read as zero
	unsigned char Reserved1		 :1;

	/// 1==Local phone's handset is off-hook
	unsigned char bOffHook		 :1;


	/// Reserved, do not use, set/read as zero
	unsigned char reserved		 :1;

	/// 1== Ringer is active
	unsigned char RingerStatus	 :1;
	
	
	/** assign to BYTE bSwMode; then use bSwMode = (bSwMode <<4) | 0x0a;
	this will make a match to Device Switching Mode commands*/
	unsigned char DevModeSwitch3 :3;

}W2CDEVREG1, *LPW2CDEVREG1;



///Device Status Register 2, used with HPEVT_NOTIFY_STATUS2 event
typedef struct w2cDevReg2_tag
{
	/// 1== Phone Echo Suppression is active
	unsigned char bEchoSuppression	:1;
	
	/** assign to BYTE bPulseDial; then use bPulseDial = (bSwMode <<4) | 0x0d;
	this will make a match to Pulse Dial Mode commands*/
	unsigned char PulseDialMode2	:2;
									   
	/// 1==Headset is plugged.
	unsigned char bHeadSetPlugged	:1;
	
	/// 1== Headset2 is plugged.
	unsigned char bHeadSet2Plugged  :1;
	
	/** assign to BYTE bDaaCfg; then use bDaaCfg = (bSwMode <<4) | 0x03;
    this will make a match to DAA Impedance commands*/
	unsigned char DAA_Config3		:3;
}W2CDEVREG2, *LPW2CDEVREG2;


/**Device status struct.
Used with w2cUsbM_GetDeviceStatus
*/
typedef struct w2cDevStatus_tag
{
	/// 1==Audio to / from PC is active. 0 == Not active
	unsigned char bPcAudioActive ;

	/// Reserved, do not use, set/read as zero
	unsigned char Reserved1		 ;

	/// 1==Local phone's handset is off-hook
	unsigned char bOffHook		 ;

	/// Reserved, do not use, set/read as zero
	unsigned char reserved		 ;

	/// 1== Ringer is active
	unsigned char RingerStatus	 ;

	/// assign to BYTE bSwMode; then use bSwMode = (bSwMode <<4) | 0x0a;
	unsigned char DevModeSwitch3 ;

	/// assign to BYTE bPulseDial; then use bPulseDial = (bSwMode <<4) | 0x0d;
	unsigned char PulseDialMode2;
									   
	/// 1==Headset is plugged.
	unsigned char bHeadSetPlugged;

	/// 1== Headset2 is plugged.
	unsigned char bHeadSet2Plugged ;

	/// assign to BYTE bDaaCfg; then use bDaaCfg = (bSwMode <<4) | 0x03;
	unsigned char DAA_Config3		;


	/// 0x6A and 0x7A modes - Line to Phone mute state
	unsigned char bPhone2LineMute; 

	/// 0x6A and 0x7A modes - Phone to Line mute state
    unsigned char bLine2PhoneMute; 

	/// 1==local device is headset, 0==local device is phone.
	unsigned char bSelectHeadSet;

	/// Ringer Frequency
	unsigned char RingFrequency2; 

	/** Phone / Headset Echo Suppression.
	Bit 0 is Phone Echo Suppression state.
	Bit 1 is Headset Echo Suppression state.
	*/
	unsigned char bEchoSuppression; 

	/// Aux. Wave In content
	unsigned char SecondaryWave2;
	
	/// CWCID Enable switch
	unsigned char bDisableCWCID;

	/// SLIC (Subscriber Line Interface Circuit) Polarity
	unsigned char bSLIC_PolarityReversal;

	/// For Hi-PPhone Desktop USB (PID == 0x0004), DAA (Line Interface) gain switch
	unsigned char bDaaGain; 

	/// For (PID >= 0x000A), Wriretapping switch state
	unsigned char bWiretapping; 

}W2CDEVSTATUS, *LPW2CDEVSTATUS;


	

///TAPI style tone monitoring struct
typedef struct ClientToneMonitor_tag
{
	/// application list ID
	DWORD	 dwListID;	
	
	/// application parameter to be passed with tone callback
	DWORD  dwAppSpecific;		
  	
	/// duration in millisecond
	DWORD  dwDuration;		
  	
	/// up to 3 simultaneous frequencies
	DWORD  dwFrequency1;		
  	
	/// zero if not used
	DWORD  dwFrequency2;		
  	
	/// zero if not used
	DWORD  dwFrequency3;		
} MONITORTONE, *LPMONITORTONE; 

/// tone detected callback struct
typedef struct TonesCallBack_tag 
{
	/// application list ID	
	DWORD		dwListID;		
	
	/// application parameter passed with tone monitoring struct
	DWORD		dwAppSpecific;	
	
	/// time stamp with 64 milisecond tick resolution
	DWORD		dwTimeStamp;	
} TONESCALLBACK, *LPTONESCALLBACK; 

///TAPI style multiple tone generation struct (array)
typedef struct  ClientGenerateTone_tag
{ 
	/**Frequency in Hz.
	   When > 4000, A Noise will be generated with amplitude
	   Range from 4001 to 5025 (1024 level steps).
	*/
	unsigned short  Frequency;		
	                                  
	/// signal level 0 to 0x7ffff
	unsigned short	Level;			
	
	/// duration on  in millisecond
	unsigned long	dwDurationOn;	
	
	/// duration off in millisecond
	unsigned long	dwDurationOff;  
}CLIENT_GENERATE_TONE, *LPCLIENT_GENERATE_TONE;

// ====================
// Caller ID Generator:

/// Caller ID Generator maximum name chars
#define CID_MAX_NAME_CHARS 50

/// Caller ID Generator maximum number chars
#define CID_MAX_LINE_ID_NUMBER_CHARS   50

/// Caller ID Generator message type SDMF
#define CID_MSGTYPE_SDMF 0

/// Caller ID Generator message type MDMF
#define CID_MSGTYPE_MDMF 1

/** Caller ID Generator struct.
Used with w2cUsbM_GenerateCallerID
*/
typedef struct  ETSI_CID_MSG_tag
{ 
	/// CID_MSGTYPE_SDMF or CID_MSGTYPE_MDMF
	unsigned char   bMsgType;

	/// Caller name
	char			cName[CID_MAX_NAME_CHARS];	
	
	/// Caller name string length
	unsigned char	NameLength;					
	
	/// Caller number
	char			cLineId[CID_MAX_LINE_ID_NUMBER_CHARS]; 
	
	/// Caller number string length
	unsigned char	LineIdLength;						   

	/// Date and Time: MM DD HH mm
	char			cDateTimeMMDDHHmm[8];

	/// Visual Message Waiting Switch: 0x00 == Off, 0xFF == On
	unsigned char   bVisualIndicatorSw; 

	/// 1 == send name
	unsigned char bFlag_SendName:1;
	
	/// 1 == send number
	unsigned char bFlag_SendNumber:1;
	
	/// 1 == send Date time
	unsigned char bFlag_SendDateTime:1;
	
	/// 1 == send Visual Indicator Sw
	unsigned char bFlag_SendVisualIndicator:1;

	/// 'Out of area' (excludes bFlag_Private) 
	unsigned char bFlag_OutOfArea:1;

	/// 'Private' (excludes bFlag_OutOfArea)
	unsigned char bFlag_Private:1; 
	
	/// Use ringer
	unsigned char bFlag_UseRinger:1; 
	
	/// General flag, currently not in use, set to zero.
	unsigned char bFlag_General:1;

	/// 1 == send CIDCW (Call Waiting Caller ID)
	unsigned char bFlag_CIDCW:1;

	/// 1 == wait for CIDCW (Call Waiting Caller ID) ACK
	unsigned char bFlag_WAIT_CIDCW_ACK:1;

	/// padd to 8 bits, set to zero.
	unsigned char bFlag_Pad:6;

	/// FSK signal level. Range: from 0 to 32766, default: 8191
	unsigned short sSignalLevel;	

}ETSI_CID_MSG, *LPETSI_CID_MSG;



#ifndef _AGC_PARAMETER
#define _AGC_PARAMETER


/// AGC Parameters
typedef enum AGC_PARAMETER
{
	/// from which signal level to process 0-32767, default 327
	AGC_NOISE_THRESHOLD=0,	
	
	/// to which signal level to process 0-32767, default 26000	
	AGC_REFERENCE_LEVEL,	
	
	/// Requested target level 0-32767, default , 26000
	AGC_TARGET_LEVEL,		
	
	/// gain limit to reach target level from 1 up to 1024 (multiply factor), default 1024
	AGC_GAIN_LIMIT          
};
#endif




//---------------------------------------------------------------------
/** Callback function pointer typedef.

See HiPhoneCallbackProc

*/
typedef long (WINAPI *W2C_CALLBACK)(
	WORD		wDeviceID,		///< which device fired the event
	DWORD		dwEventCode,	///< The event code
	DWORD		dwEventData,	///< The event data (if any)
	LPVOID		lpParameter,	/**< Callback data passed to the function
								    using the lpParameter parameter of
								    the initialization function
								*/
	LPVOID		lpBuffer,		///< Data buffer passed from the caller
	DWORD		dwData,			///< Additional data, depends on the callback
	DWORD		dwReserved		///< For future use (0)
	);



// Functions API


#ifdef __cplusplus
extern "C" {
#endif


/** Callback function example

A device fire events by calling (callback) this function
(which reside in your application).

When calling w2cUsbM_InitializeDevice, pass a pointer to HiPhoneCallbackProc.
A single callback function or multiple callback functions may be used.


\note
This function is NOT exported.
It is for your own use.

!See:
- W2C_CALLBACK

\code
long WINAPI HiPhoneCallbackProc(
        WORD wDeviceID,      // which device fired the event
        DWORD dwEventCode,   // The event code
        DWORD dwEventData,   // The event data (if any)
        LPVOID lpParameter,  // Callback data passed to the function
        LPVOID lpBuffer,     // Data buffer passed from the caller
        DWORD dwData,        // Additional data, depends on the callback
        DWORD dwReserved     // For future use (0)
)
{

    //check wDeviceID ...

    switch(dwEventCode)
    {
	case HPEVT_LINE_RING_START://Incoming RING
		// handle incomming ring event
		break;

	}

  return 0;

}

\endcode

*/
long WINAPI HiPhoneCallbackProc(
    WORD		wDeviceID,		///< which device fired the event
	DWORD		dwEventCode,	///< The event code
	DWORD		dwEventData,	///< The event data (if any)
	LPVOID		lpParameter,	/**< Callback data passed to the function
								    using the lpParameter parameter of
								    the initialization function
								*/
	LPVOID		lpBuffer,		///< Data buffer passed from the caller
	DWORD		dwData,			///< Additional data, depends on the callback
	DWORD		dwReserved		///< For future use (0)
);


/** Get driver version.
\return Then driver version.
*/
long WINAPI w2cUsbM_GetDriverVersion(
	LPDWORD		pdwVersion			///< Pointer to DWORD to be filled with driver version.
	);



/** Initialize Driver Module.
Must be the first function called.
This function must be called before any other function except w2cUsbM_GetDriverVersion

Make sure that your application has a matching call to w2cUsbM_ShutdownDriver

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_InitializeDriver(
	DWORD			dwReserved	///< Reserved (must be 0)
	);


/** Shutdown Driver Module.
Must be the last function called.

Make sure that your application has a matching call to w2cUsbM_InitializeDriver

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_ShutdownDriver(
	DWORD			dwReserved	///< Reserved (must be 0)
	);


//---------------------------------------------------------------------
/// 
/** Enum Driver Devices. will retrun 1,2,3 ... devices. 0 means no devices.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetNumDevs(
	LPWORD			lpwNumDevs,	///< WORD Pointer to return how many devices currentlly present
	DWORD			dwReserved	///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Get Device capabilities.
w2cDevCaps_tag::wCbSize #Must# be initialized #before# calling w2cUsbM_GetDevCaps.


\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetDevCaps(
	WORD			wDeviceID,	///< Device ID
	LPW2CDEVCAPS	lpDevCaps,	///< pointer to W2CDEVCAPS Device capabilities struct
	DWORD			dwReserved	///< Reserved (must be 0)
	);

	
//---------------------------------------------------------------------
/** Initialize device.


Alternate event firing method can be a window message WM_SETTEXT.

If window message is required for events,
pass a window handle on lpfnEventCallback parameter,
and -1 on lpEventParameter.

The text content is the Hi-Phone event and has the following format:
\pre 
iiii@eeee@dddd@xxxxxxxx
\endpre
where
iiii is device id,
eeee is event,
dddd is event's data,
xxxxxxxx is 8 hex digits timestamp
Fileds are seperated with '@' character.


\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_InitializeDevice(
	WORD			wDeviceID,			///< Device ID
	W2C_CALLBACK	lpfnEventCallback,	///< Callback for event notification
	LPVOID			lpEventParameter,	///< Parameter to pass to the event callback
	LPDWORD			lpdwVersion,		///< Returns the version of the driver
	DWORD			dwReserved			///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Shut down device. Call after w2cUsbM_CloseDevice.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_ShutdownDevice(
	WORD	wDeviceID,			///< Device ID
	DWORD	dwReserved			///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Open device for use. Call after w2cUsbM_InitializeDevice.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_OpenDevice(
	WORD	wDeviceID,			///< Device ID
	DWORD	dwReserved			///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Close the device after use.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_CloseDevice(
	WORD	wDeviceID,
	DWORD	dwReserved			///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Send a command to the device
See HP_CMD_XXX

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_DoCommand(
	WORD	wDeviceID,			///< Device ID
	DWORD	dwCommand,			///< Command code
	DWORD	dwCommandData,		///< Command data (if needed)
	DWORD	dwReserved			///< Reserved (must be 0)
	);


//---------------------------------------------------------------------
/** Resets the device (internal queues and data)
See HP_CMD_XXX

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_DeviceSoftwareReset(
	WORD	wDeviceID,			///< Device ID
	DWORD	dwReserved			///< Reserved (must be 0)
	);

//---------------------------------------------------------------------
/** Resets the device's hardware
See HP_CMD_XXX

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_DeviceHardwareReset(
	WORD	wDeviceID,			///< Device ID
	DWORD	dwReserved			///< Reserved (must be 0)
	);




//---------------------------------------------------------------------
/** Get Event's textual description

\warning 
The string size pointed by szDescription  must be
at lease 256 bytes. 

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_TranslateEventToString(
	WORD	wDeviceID,			///< Device ID
	LPTSTR	szDescription,		///< String to return event's description
	DWORD	dwEvent,			///< Event ID
	DWORD	dwData				///< Event data (if any)
	);


/// DOXYS_OFF 

//---------------------------------------------------------------------
//upload melody for usb phone
long WINAPI w2cUsbM_UploadMelody(WORD wDeviceID, unsigned char *lpBuffer, UINT dwBufferLength);

//---------------------------------------------------------------------
//set default melody for usb phone
long WINAPI w2cUsbM_UploadDefaultMelody(WORD wDeviceID);

//---------------------------------------------------------------------
//device burning - do not use !
//E2Rom Delete functio
#define HP_E2ROM_DELETE_TO_DEFAULT		0x0000  //Delete the E2Rom
#define HP_E2ROM_DELETE_TO_W2C			0x0001	//Delete the E2Rom except the product ID
#define HP_E2ROM_SN						0x0002  //Program serial number

long WINAPI w2cUsbM_E2Rom(WORD wDeviceID, DWORD dwType, char cSN[22], char *cPassword);

/// DOXYS_ON 


/** Translates a horizontal pixel location to a frequency.
Used with the analysis view window.

!See:
- w2cUsbM_SetAnalysis_hWnd

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetIndexFreq(WORD wDeviceID,///< Device ID
								 WORD wIndex,///< horizontal pixel location
								 float * lpFreq ///< Output: the frequency in Hertz
								 );


/** Get how many Ring Patterns are defined.

!See:
- w2cUsbM_SetDevRingPattern
- w2cUsbM_GetDevRingPattern

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetNumRings(UINT * puNumRings///< Pointer to a UINT to be filled with result.
							   );

/** Get Ring Pattern's name

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetRingName(UINT RingID,///< RingPattern ID, see w2cUsbM_GetNumRings
							   char * lpName,///< Pointer to a string to be filled with result.
							   UINT cbNameSize///< string buffer size in bytes.
							   );

/** Get Ring Pattern's associated media mode

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/						   
int WINAPI w2cUsbM_GetRingMediaMode(UINT RingID,///< RingPattern ID, see w2cUsbM_GetNumRings
									UINT *puRingMediaMode///< Pointer to a string to be filled with result.
									);

/** Get Ring media mode's name

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/	
int WINAPI w2cUsbM_GetMediaModeName(UINT uiMediaMode,///< the media mode, see w2cUsbM_GetRingMediaMode
									char * lpName,///< Pointer to a string to be filled with result.
									UINT cbNameSize///< string buffer size in bytes.
									);


/** Display the Distinctive Ring Patterns setup dialog
!See:
- "Distinctive Ring Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_DistinctiveRingDialog(HWND hParent///< Parent window handle.
										 );



/** Set the active Ring Pattern for the specified device.

!See:
- w2cUsbM_GetDevRingPattern
- w2cUsbM_GetNumRings
- "Distinctive Ring Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_SetDevRingPattern(WORD wDeviceID,///< Device ID
									 UINT uRingID///< RingPattern ID, see w2cUsbM_GetNumRings
									 );

/** Get the active Ring Pattern for the specified device.

!See:
- w2cUsbM_SetDevRingPattern
- "Distinctive Ring Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetDevRingPattern(WORD wDeviceID,///< Device ID
									 UINT *puRingID///< Pointer to a UINT to be filled with result.
									 );


/** Get the associated windows mixer device ID

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetMixerDrvID(WORD wDeviceID,///< Device ID
								 UINT * puiMixDrvId///< Pointer to a UINT to be filled with result.
								 );


/*

Hi-Phone Internal Volume settings

	-128 == mute, -30 to +12 range in dB. 0==default (0 dB).

	/// Telephone Control 
	PhoneOutVolume			
	PhoneInVolume			
	
	PhoneLineVolume			
	PhonePlaybackVolume		
	PhoneRecordingVolume

	/// Headset Control
	HeadsetOutVolume		
	HeadsetInVolume			

	HeadsetSideToneVolume	
	HeadsetLineVolume		
	HeadsetPlaybackVolume	
	HeadsetRecordingVolume	


	/// Line control #0 (default)
	LinePlaybackVolume		
	LineRecordingVolume
	LineFeatures:       Bit 0 == AGC

	
*/
// Telephone Control

/// Phone Output Volume
#define HP_PhoneOutVolume			0

/// Phone Input Volume 
#define HP_PhoneInVolume			1		

/// Phone Line (phoneline) Volume
#define HP_PhoneLineVolume			2

/// Phone PC Playback Volume
#define HP_PhonePlaybackVolume		3

/// Phone PC Recording Volume
#define HP_PhoneRecordingVolume		4


// Headset Control
/// Headset Output Volume
#define HP_HeadsetOutVolume			5

/// Headset Input Volume
#define HP_HeadsetInVolume			6

/// Headset side-tone (self hearing) Volume
#define HP_HeadsetSideToneVolume	7

/// Headset Line (phoneline) Volume
#define HP_HeadsetLineVolume		8

/// Headset PC Playback Volume
#define HP_HeadsetPlaybackVolume	9

/// Headset PC Recording Volume
#define HP_HeadsetRecordingVolume	10


// Line control #0 (default)

/// Line PC Playback Volume

#define HP_LinePlaybackVolume		11

/// Line PC Recording Volume
#define HP_LineRecordingVolume		12

#define HP_VOLUMES					13



/** Get Volume for the specified Hi-Phone component (sub-device).

Volume Value Range is from 0 (min) to 32767 (max).
The Total Range represents 42dB in steps of 1 dB:
0 represent mute, 1 represent -30 dB, 32767 represent +12 dB.
It is recommended to keep volume levels at 0dB or lower.

possible sub-decices:

HP_PhoneOutVolume
HP_PhoneInVolume
HP_PhoneLineVolume
HP_PhonePlaybackVolume
HP_PhoneRecordingVolume
HP_HeadsetOutVolume
HP_HeadsetInVolume
HP_HeadsetSideToneVolume
HP_HeadsetLineVolume
HP_HeadsetPlaybackVolume
HP_HeadsetRecordingVolume
HP_LinePlaybackVolume
HP_LineRecordingVolume


pdwVol values table
||pdwVol value||Volume
|0|Mute
|781|-29dB
|1561|-28dB
|2341|-27dB
|3121|-26dB
|3901|-25dB
|4682|-24dB
|5462|-23dB
|6242|-22dB
|7022|-21dB
|7802|-20dB
|8582|-19dB
|9363|-18dB
|10143|-17dB
|10923|-16dB
|11703|-15dB
|12483|-14dB
|13263|-13dB
|14044|-12dB
|14824|-11dB
|15604|-10dB
|16384|-9dB
|17164|-8dB
|17944|-7dB
|18725|-6dB
|19505|-5dB
|20285|-4dB
|21065|-3dB
|21845|-2dB
|22625|-1dB
||23406||0dB
|24186|+1dB
|24966|+2dB
|25746|+3dB
|26526|+4dB
|27306|+5dB
|28087|+6dB
|28867|+7dB
|29647|+8dB
|30427|+9dB
|31207|+10dB
|31987|+11dB
|32767|+12dB


!See:
- w2cUsbM_SetVolume
- w2cUsbM_GetVolumeString
- HPEVT_VOLUME_CHANGED event

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetVolume(WORD wDeviceID,///< Device ID
							 unsigned char iSubDevice,///< Hi-Phone component such as HP_HeadsetOutVolume
							 DWORD * pdwVol///< Pointer to DWORD to be filled with result.
							 );

/** Set Volume for the specified Hi-Phone component (sub-device).

Volume Value Range is from 0 (min) to 32767 (max).
The Total Range represents 42dB in steps of 1 dB:
0 represent mute, 1 represent -30 dB, 32767 represent +12 dB.
The default level for most sub-devices is 0dB.
It is recommended to keep volume levels at 0dB or lower.

possible sub-decices:

HP_PhoneOutVolume
HP_PhoneInVolume
HP_PhoneLineVolume
HP_PhonePlaybackVolume
HP_PhoneRecordingVolume
HP_HeadsetOutVolume
HP_HeadsetInVolume
HP_HeadsetSideToneVolume
HP_HeadsetLineVolume
HP_HeadsetPlaybackVolume
HP_HeadsetRecordingVolume
HP_LinePlaybackVolume
HP_LineRecordingVolume


||dwVol value||Volume
|0|Mute
|781|-29dB
|1561|-28dB
|2341|-27dB
|3121|-26dB
|3901|-25dB
|4682|-24dB
|5462|-23dB
|6242|-22dB
|7022|-21dB
|7802|-20dB
|8582|-19dB
|9363|-18dB
|10143|-17dB
|10923|-16dB
|11703|-15dB
|12483|-14dB
|13263|-13dB
|14044|-12dB
|14824|-11dB
|15604|-10dB
|16384|-9dB
|17164|-8dB
|17944|-7dB
|18725|-6dB
|19505|-5dB
|20285|-4dB
|21065|-3dB
|21845|-2dB
|22625|-1dB
||23406||0dB
|24186|+1dB
|24966|+2dB
|25746|+3dB
|26526|+4dB
|27306|+5dB
|28087|+6dB
|28867|+7dB
|29647|+8dB
|30427|+9dB
|31207|+10dB
|31987|+11dB
|32767|+12dB

!See:
- w2cUsbM_GetVolume
- w2cUsbM_GetVolumeString
- HPEVT_VOLUME_CHANGED event

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_SetVolume(WORD wDeviceID,///< Device ID
							 unsigned char iSubDevice,///< Hi-Phone component such as HP_HeadsetOutVolume
							 DWORD dwVol///< Current volume.
							 );
/** Get volume value's textual description

!See:
- w2cUsbM_GetVolume
- w2cUsbM_SetVolume
- HPEVT_VOLUME_CHANGED event

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetVolumeString(DWORD dwVol,///< Volume value
								   char * pStrBuff,///< Pointer to string to be filled with result
								   unsigned char bStrBuffSize///<string buffer size in bytes.
								   );



/// DOXYS_OFF 
int WINAPI w2cUsbM_SetDeviceSN(WORD wDeviceID, char * lpSN, UINT cbSNSize);
/// DOXYS_ON


/** Monitor custom tones

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_MonitorTones(WORD wDeviceID,///< Device ID
								  DWORD dwToneListID,///< A generic list ID                  
								  LPMONITORTONE lpToneList,///< pointer to MONITORTONE array that specifies tones 
								  DWORD dwNumEntries///< Number of MONITORTONE array elements.
								);

/// The custom tone monitor threshold
#define W2C_HP_THRESHOLD_CUSTOM_TONE_MONITOR 0

/// Silent detection threshold.
#define W2C_HP_THRESHOLD_SILENT 1



/** Set Threshold
Use W2C_HP_THRESHOLD_CUSTOM_TONE_MONITOR or W2C_HP_THRESHOLD_SILENT for wIndex.
Vlaue range is from 0 to 32767.

!See:
- w2cUsbM_GetThreshold

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetThreshold(WORD wDeviceID,///< Device ID
								 unsigned short wIndex,///< can be W2C_HP_THRESHOLD_CUSTOM_TONE_MONITOR or W2C_HP_THRESHOLD_SILENT
								 unsigned int dwValue///< The value
								 );

/** Get Threshold
Use W2C_HP_THRESHOLD_CUSTOM_TONE_MONITOR or W2C_HP_THRESHOLD_SILENT for wIndex.
Vlaue range is from 0 to 32767.

!See:
- w2cUsbM_SetThreshold

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetThreshold(WORD wDeviceID,///< Device ID
								 unsigned short wIndex,///< can be W2C_HP_THRESHOLD_CUSTOM_TONE_MONITOR or W2C_HP_THRESHOLD_SILENT
								 unsigned int *lpDwValue///< Pointer to unsigned int to be filled with result.
								 );


/** Generate custom tones.


!See:
- HPCMD_GENERATE_STOP_ALL_TONES command.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GenerateTones(WORD wDeviceID, ///< Device ID
								   LPCLIENT_GENERATE_TONE lpToneList,///< Pointer to CLIENT_GENERATE_TONE array that specifies the tones.
                                   DWORD dwNumEntries///< number of CLIENT_GENERATE_TONE array elements.
								   );

/** Generate Caller ID to the local phone.

When CID generation is completed,
HP_EVENT_ASYNC_CID_GENERATION_DONE event is fired.

See ETSI_CID_MSG_tag

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GenerateCallerID(WORD wDeviceID,///< Device ID
									 LPETSI_CID_MSG lpCID///< Pointer to ETSI_CID_MSG_tag struct that specifies the CID message.
									 );

/// DOXYS_OFF 

long WINAPI w2cUsbM_SetLoopCurrentDropTime(WORD wDeviceID,DWORD dwTime);
long WINAPI w2cUsbM_ExchangeFirst2WaveDrvIndexes(void);

/// DOXYS_ON


//audio wave playback
/**Get Wave File End Position

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetWaveFileEndPosition(WORD wDeviceID,///< Device ID
										   char * pFileName,///<File's name, null terminated string.
										   long * pEndPos///<Pointer to a long to be filled with end position.
										   );


/**Play a Wave File to the specified audio device.

To play a wave file to the Hi-Phone,
set wPlayToWaveDrv to w2cDevCaps_tag.uWaveOutDrvID.

To play a wave file to the system prefered device, 
set wPlayToWaveDrv to -1.

When playback is done, HP_EVENT_ASYNC_PLAYBACK_DONE event is fired.

\note
Compressed audio (wave) files can only be played to the system prefered device.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_PlayWaveFile(WORD wDeviceID,///< Device ID 
								 char * pFileName,///< File's name, null terminated string.
								 long dwPlayFromPosition,///< Playback start position. See w2cUsbM_GetWaveFileEndPosition
								 short wPlayToWaveDrv///< The specified audio device.
								 );
/**Stop Playback

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_StopPlay(WORD wDeviceID///< Device ID
							 );

/**Pause Playback

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_PausePlay(WORD wDeviceID///< Device ID
							  );


/**Resume Playback

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_ResumePlay(WORD wDeviceID///< Device ID
							   );

/**Get Playback position

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetPlayPosition(WORD wDeviceID,///< Device ID
									long* pPosition///<Pointer to long to be filled with result.
									);


/**Set Playback position

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetPlayPosition(WORD wDeviceID,///< Device ID
									long  lPosition,///< The new position
									short bContinuePlay///<1== continu playback
									);

//Audio wave Recording
/**Turn recording compression on or off.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_RecordedAudioCompression(WORD wDeviceID,///< Device ID
											 short bOnOrOff///< 0==off, 1==on.
											 );


/**Get recording compression format string.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetRecAudioFormatString(WORD wDeviceID,///< Device ID
											char * pRecFmt,///<Pointer to recording compression format string
											short cbRecFmtSize///<String buffer size in bytes
											);

/**Display a  recording compression format dialog.
This allows the user to select the desired recording compression format.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SelectRecAudioFormatDlg(WORD wDeviceID,///< Device ID
											long hWndParent///<Parent window handle.
											);

/**Record a Wave File from the specified audio device.

To record a wave file from the Hi-Phone,
set wRecordFromWaveDrv to w2cDevCaps_tag.uWaveInDrvID.

To record a wave file from the system prefered device, 
set wRecordFromWaveDrv to -1.

\note
Compressed audio (wave) files can only be played to the system prefered device.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_RecordWaveFile(WORD wDeviceID,///< Device ID
								   char * pFileName,
								   short wRecordFromWaveDrv
								   );

/**Stop recording

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_StopRecord(WORD wDeviceID///< Device ID
							   );

/**Pause recording

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_PauseRecord(WORD wDeviceID///< Device ID
								);

/**Resume recording

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_ResumeRecord(WORD wDeviceID///< Device ID
								 );



/**Get Recording Signal Level.
Range is from 0 (minimum) to 255 (maximum).

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetRecordingSignalLevel(WORD wDeviceID,///< Device ID
											unsigned char * pByte///<Pointer to unsigned char to be filled with result.
											);


// Software AGC 
/**Turn software automatic gain on or off.
Software automatic gain improves audio recording quality.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetSoftAGC_OnOff(WORD wDeviceID,///< Device ID
									 short bObnOrOff///<0==off, 1==on.
									 );

/**Set software automatic gain parameters
See AGC_PARAMETER enum members.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetSoftAGC_Parameters(WORD wDeviceID,///< Device ID
										  short bParameter,///< The parameter
										  short bParameterValue///< Parameter's value
										  );


/**Get software automatic gain parameters
See AGC_PARAMETER enum members.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetSoftAGC_Parameters(WORD wDeviceID,///< Device ID
										  short bParameter,///< The parameter
										  short * pParameterValue///<Pointer to short to be filled with result.
										  );


/**Get software automatic gain activity
See AGC_PARAMETER enum members.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetSoftAGC_Activity(WORD wDeviceID,///< Device ID
										short *lpshBeforeAgcLevel,//<Pointer to short to be filled with signal before operation
										short *lpshAfterAgcLevel,//<Pointer to short to be filled with signal after operation
										short *lpshActive//<Pointer to short to be filled with active/not-active state
											);

/**Set Analysis view window handle.
!See:
- w2cUsbM_GetIndexFreq

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetAnalysis_hWnd(WORD wDeviceID,///< Device ID
									 long hWnd/// Analysis view window handle
									 );


/**Get the recent Caller ID string.

The returned string format is  "NAME  ; NUMBER ; DATE TIME".

The ‘;’ is a delimiter allowing name, number, and date/time seperation.

For countries using different Caller ID method,
only NUMBER will be available.

 \return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetCidString(WORD wDeviceID,///< Device ID
								 char * lpStr /// pointer to string to be filled with CID
								 );


/**Wait for a Hi-Phone Event.

When dwFlags == 1,
The GUI will still be active since this function calls
GetMessage, TranslateMessage and DispatchMessage.


\return W2C_ERR_SUCCESS or 0x102 for time out.
*/
long WINAPI w2cUsbM_WaitForHiPhoneEvent(WORD wDeviceID,///< Device ID
										DWORD dwEvent,///< Hi-Phone Event
										DWORD dwTimeOutMs,///< Timeout in milliseconds
										DWORD dwFlags///< 0==block calling thread,
										             /// 1==Block Calling thread but active GUI
										);



/**
Dial the specified number.

The Dialing will be done only if the line was opened by:

1. A relevant switching mode commands:
\n   HPCMD_SW_LINE_AudioStream
\n   HPCMD_SW_LINE_AudioStream_PHONE
\n   HPCMD_SW_LINE_AudioStream_PHONE_MONITOR

2. w2cUsbM_Answer

{Dial String specifications:{
0 1 2 3 4 5 6 7 8 9   == Pulse or DTMF digits
a,b,c,d or A,B,C,D    == DTMF A,B,C,D
'\#' and '*'           == DTMF '*' and '\#'
'T'                   == Tone Dial
'P'                   == pulse Dial
'W'                   == wait for dial tone
'-' or ','            == 2 seconds (interdigit) pause
'!'                   == Hook Flash
'@'                   == UK and Hong Kong Line Impedance

The dial string "TW123,abc,!-p789" means:
ToneDial, Wait for Dial Tone, Dial 123
Pause 2 sec, Dial abc, Pause 2 sec
Make Hook Flash, Pause 2 sec, Pulse Dial 789.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_Dial(WORD wDeviceID,///< Device ID
						 char * cDigitsString///< Dial String
						 );

/**
Open the line, dial the specified number, and start call progress analysis.
This function is asynchroneous.
When the initiated call dialing is done, HP_EVENT_ASYNC_CALL_DIALING_DONE
Event will be fired.


Depending on  bUseLocalPhone parameter value,
This function sets the device switching mode:
When bUseLocalPhone == HP_CALL_USE_LOCAL_PHONE
The switching mode is set to HPCMD_SW_LINE_AudioStream_PHONE_MONITOR .
When bUseLocalPhone == 0,
The switching mode is set to HPCMD_SW_LINE_AudioStream

{Dial String specifications:{
0 1 2 3 4 5 6 7 8 9   == Pulse or DTMF digits
a,b,c,d or A,B,C,D    == DTMF A,B,C,D
'\#' and '*'           == DTMF '*' and '\#'
'T'                   == Tone Dial
'P'                   == pulse Dial
'W'                   == wait for dial tone
'-' or ','            == 2 seconds (interdigit) pause
'!'                   == Hook Flash
'@'                   == UK and Hong Kong Line Impedance

The dial string "TW123,abc,!-p789" means:
ToneDial, Wait for Dial Tone, Dial 123
Pause 2 sec, Dial abc, Pause 2 sec
Make Hook Flash, Pause 2 sec, Pulse Dial 789.

\return
W2C_ERR_SUCCESS or
W2C_ERR_LINE_NOT_CONNECTED or
W2C_ERR_LINE_PARALLEL_DEVICE_OFF_HOOK or

or other W2C_ERR_XXX.

See Also:

w2cUsbM_GetDeviceLineWirePlugged
HPEVT_LINE_UNPLUGGED

*/
long WINAPI w2cUsbM_Call(WORD wDeviceID,///< Device ID
						 char * cAddress,///< Dial String
						 short bUseLocalPhone///< Determine if Local 'Phone' or local 'Headset' are used.
						                       /// See HP_CALL_USE_LOCAL_PHONE ,
											   /// HP_CALL_MUTE_PHONE_UNTILL_CALL_IS_CONNECTED for details.
						 );


/**Close the line and hang up a call.
Stops call progress analysis.

Depending on  bUseLocalPhone parameter value,
This function sets the device switching mode:
When bUseLocalPhone == HP_CALL_USE_LOCAL_PHONE
The switching mode is set to HPCMD_SW_PHONE_AudioStream .
When bUseLocalPhone == 0,
The switching mode is set to HPCMD_SW_DEFAULT_PHONE_LINE


*/
long WINAPI w2cUsbM_HangUp(WORD wDeviceID,		///< Device ID
						   short bUseLocalPhone	///< Determine if Local 'Phone' or local 'Headset' are used.
												/// See HP_CALL_USE_LOCAL_PHONE ,
												/// HP_CALL_MUTE_PHONE_UNTILL_CALL_IS_CONNECTED for details.
						   );



/**Open the 'Line' for answer incoming call or dial.

Depending on  bUseLocalPhone parameter value,
This function sets the device switching mode:
When bUseLocalPhone == HP_CALL_USE_LOCAL_PHONE
The switching mode is set to HPCMD_SW_LINE_AudioStream_PHONE_MONITOR .
When bUseLocalPhone == 0,
The switching mode is set to HPCMD_SW_LINE_AudioStream



\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_Answer(WORD wDeviceID, ///< Device ID
						   short bUseLocalPhone///< Determine if Local 'Phone' or local 'Headset' are used.
						                       /// See HP_CALL_USE_LOCAL_PHONE ,
											   /// HP_CALL_MUTE_PHONE_UNTILL_CALL_IS_CONNECTED for details.
						   );

// w2cUsbM_Call() bUseLocalPhone Usage:

/// w2cUsbM_Call() - Do not use local device
#define HP_CALL_DO_NOT_USE_LOCAL_PHONE				0x00	


/// w2cUsbM_Call() - Use local device
#define HP_CALL_USE_LOCAL_PHONE						0x01	

/// w2cUsbM_Call() - Use and Mute Local device's audio input untill call is connected.
#define HP_CALL_MUTE_PHONE_UNTILL_CALL_IS_CONNECTED	0x80	




/**Get call progress analysis state.

||bCpActive||State
|0|Not Acive
|1|Active

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_IsCallProgressActive(WORD wDeviceID,///< Device ID
										 short *bCpActive///< Pointer to short to be filled with result.
										 );

/**Set Local Country.
Setting the local country sets which set of tones will
be used for call progress analysis.

!See:
- w2cUsbM_InternationalTonesDlg
- "International Tones Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetLocalCountry(WORD wDeviceID,///< Device ID
									char *pCuntryCode///<Null terminated string country code.
									);

/**Set Destination Country.
Setting the destination country sets which set of tones will
be used for call progress analysis when calling to a different country
then the local country.

!See:
- w2cUsbM_InternationalTonesDlg
- w2cUsbM_SetLocalCountry
- "International Tones Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_SetDestinationCountry(WORD wDeviceID,///< Device ID
										  char *pCuntryCode///<Null terminated string country code.
										  );

/**Get Local Country code.

!See:
- w2cUsbM_InternationalTonesDlg
- w2cUsbM_SetLocalCountry
- "International Tones Setup"

\warning
The string size pointed by pCuntryCode, must be at lease 32 bytes.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetLocalCountry(WORD wDeviceID, ///< Device ID
									char *pCuntryCode///<Pointer to string to be filled with result.
									);


/**Get Destination Country code.

!See:
- w2cUsbM_InternationalTonesDlg
- w2cUsbM_SetDestinationCountry
- "International Tones Setup"

\warning
The string size pointed by pCuntryCode, must be at lease 32 bytes.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetDestinationCountry(WORD wDeviceID,///< Device ID
										  char *pCuntryCode
										  );


/**Display the International Tones setup Dialog.
Different countries can have different tones-sets for call progress analysis.

!See:
- "International Tones Setup"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_InternationalTonesDlg(HWND hWndParent///< Parent window handle.
										  );

/**Fills a Combo-Box with the International countries list.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_FillCbWithCountries(HWND hWndCb///< Combo - Box control handle.
										);



// All timing parameters are in milliseconds !
// iParameterIndex is one of W2C_AP_XXX constants

/** Set one of the Adjustable Parameters value.

Adjustable parameters:
||Parameter||Function
|W2C_AP_WAIT_DIALTONE_TIMEOUT|Dial Tone time out in milliseconds
|W2C_AP_WAIT_ANSWER_TIMEOUT|Detection Timeout (No Dial Tone) in milliseconds
|W2C_AP_DTMF_DIAL_TIME|DTMF Dial Time in milliseconds
|W2C_AP_DIAL_PAUSE_TIME|Dial Pause duration in milliseconds
|W2C_AP_DTMF_DETECT_TIME|DTMF detection time in milliseconds
|W2C_AP_HOOK_FLASH_TIME|Hook-Flash Dial time in milliseconds
|W2C_AP_HOOK_FLASH_PRE_TIME|Hook-Flash pre - dial time in milliseconds
|W2C_AP_HOOK_FLASH_POST_TIME|Hook-Flash post - Dial time in milliseconds
|W2C_AP_LITE_DTMF_TH_DAA_OFFHOOK|Hi-Phone Lite DTMF Threshold for Line opened
|W2C_AP_LITE_DTMF_TH_DAA_ONHOOK|Hi-Phone Lite DTMF Threshold for Line closed
|W2C_AP_LITE_DTMF_TH_CODEC|Hi-Phone Lite DTMF Threshold for CODEC
|W2C_AP_VOICE_THRESHOLD|Voice detection threshold
|W2C_AP_DETECTION_SNR_SINGLE|Call progress analysis signal to noise ratio for single tone
|W2C_AP_DETECTION_SNR_DUAL|Call progress analysis signal to noise ratio for dual tone
|W2C_AP_DETECTION_SNR_TRIPPLE|Call progress analysis signal to noise ratio for tripple tone
|W2C_AP_HEADSET_ECHO_SUPPRESSION_SILENCE_THRESHOLD|Headset echo suppression parameter: silence threshold
|W2C_AP_HEADSET_ECHO_SUPPRESSION_OUT2IN_DIFF_THRESHOLD|Headset echo suppression parameter: signal out-in difference threshold
|W2C_AP_HEADSET_ECHO_SUPPRESSION_OFF_TIME|Headset echo suppression parameter: signal supression off time
|W2C_AP_HEADSET_ECHO_SUPPRESSION_ON_TIME|Headset echo suppression parameter: signal supression on time

!See:
- w2cUsbM_GetParameter

*/
long WINAPI w2cUsbM_SetParameterValue(WORD wDeviceID,///< Device ID
									  int iParameterIndex,///<Parameter Index. Can be one of W2C_AP_XXX constants
									  DWORD dwValue///<Parameter value.
									  );

/**Get one of Adjustable Parameters value and other information.

!See:
- w2cUsbM_SetParameterValue


*/
long WINAPI w2cUsbM_GetParameter(WORD wDeviceID,///< Device ID
								 int iParameterIndex,///<Parameter Index. Can be one of W2C_AP_XXX constants
								 LPW2C_PARAMETER lpParameter,///< Point to a w2c_Parameter_tag struct to be filled with parameter information.
								 int iStructSizeInBytes///<Pointed w2c_Parameter_tag struct size in bytes
								 );



/// DOXYS_OFF 
long WINAPI w2cUsbM_InitCrossCorelationTest(WORD wDeviceID, unsigned short usFrequency);
long WINAPI w2cUsbM_GetCrossCorelationTestResults(WORD wDeviceID, unsigned int *ulMinResult, unsigned int *ulMaxResult);
long WINAPI w2cUsbM_CleanupCrossCorelationTest(WORD wDeviceID);



//	LS Byte LEDs Test (Lite / Pro and up)
//  LED#:
//        6   5   4   3   2   1   0
//  +---+---+---+---+---+---+---+---+	
//  | EN|LED|LED|LED|LED|LED|LED|POW|
//  +---+---+---+---+---+---+---+---+	
//    |   |   |   |   |   |   |   |
//    |   +---+---+---+---+---+---+---+---> LEDs bits starting from Power Led on LSB
//    |
//    +-----------------------------------> LEDs Test Mode Enable Bit. 1==Enable, 0==Disabled
// MS Byte
// LED#:
//    15  14  13  12  11  10  9   8
//  +---+---+---+---+---+---+---+---+	
//  |LED|LED|LED|LED|LED|LED|LED|LED|
//  +---+---+---+---+---+---+---+---+	
//    |   |   |   |   |   |   |   |
//    +---+---+---+---+---+---+---+---+---> LEDs bits starting from Power Led on LSB
long WINAPI w2cUsbM_SetLEDsTest(WORD wDeviceID, unsigned short usLEDs);



	

long WINAPI w2cUsbM_IsDeviceVirtual(WORD wDeviceID,///< Device ID
									int * piResult
									);



/// Callback mechanism for Input signal level
/// dwEventCode:
/// 0x300 == Phone
/// 0x301 == Headset
/// 0x302 == Line 0




/// 0x303 == Line 1
/// 0x304 == Line 2
/// 0x305 == Line 3

/// dwEventData is signal level 0-255 (8 LS bits).

#define HP_EVENT_IN_SIGNAL_LEVEL			0x300

#define HP_EVENT_IN_SIGNAL_LEVEL_PHONE		0
#define HP_EVENT_IN_SIGNAL_LEVEL_HEADSET	1
#define HP_EVENT_IN_SIGNAL_LEVEL_LINE0		2

#define HP_EVENT_IN_SIGNAL_LEVEL_PhoneOutVolume				3		
#define HP_EVENT_IN_SIGNAL_LEVEL_PhoneInVolume				4

#define HP_EVENT_IN_SIGNAL_LEVEL_PhoneLineVolume			5
#define HP_EVENT_IN_SIGNAL_LEVEL_PhonePlaybackVolume		6
#define HP_EVENT_IN_SIGNAL_LEVEL_PhoneRecordingVolume		7

/// Headset Control
#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetOutVolume			8
#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetInVolume			9

#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetSideToneVolume		10
#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetLineVolume			11
#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetPlaybackVolume		12
#define HP_EVENT_IN_SIGNAL_LEVEL_HeadsetRecordingVolume		13
	
#define HP_EVENT_IN_SIGNAL_LEVEL_LinePlaybackVolume			14
#define HP_EVENT_IN_SIGNAL_LEVEL_LineRecordingVolume		15

#define HP_EVENT_IN_SIGNAL_LEVEL_PcRecordMaster				16



/// Reserved for Way2call's exclusive use.
long WINAPI w2cUsbM_SetInputSignalCallback(WORD wDeviceID,///< Device ID
										   W2C_CALLBACK pCallbackFunction,
										   void * pParameter
										   );

/// Reserved for Way2call's exclusive use.
long WINAPI w2cUsbM_SetHardwareRegs(WORD wDeviceID,///< Device ID
									 unsigned char ucChipID,
									 unsigned char ucRegAddress,
									 unsigned char ucRegMask,
									 unsigned char ucRegValue);






int WINAPI w2cUsbM_WriteDesBuffer(WORD wDeviceID, unsigned char * pBuff, unsigned char bNumBytes);
int WINAPI w2cUsbM_GetFeaturesBytes(WORD wDeviceID, unsigned char * pBuff, unsigned char bNumBytes);


/// DOXYS_ON



/**Get Firmware Version String

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetFirmwareVersionString(WORD wDeviceID,///< Device ID
											 char *pDevFwVer,///<Pointer to string to be filled with result.
											 DWORD dwBufferSize///<string buffer size in bytes.
											 );

/**Get How many countries the system has.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetNumCountries(unsigned int *puiNumCountries///<Pointer to unsigned int to be filled with result.
									);

/**Get Country name and code

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
long WINAPI w2cUsbM_GetCountryNameAndCode(unsigned int uiCountryIndex,///< See w2cUsbM_GetNumCountries
										  char * pName,///<Pointer to string to be filled with name result.
										  unsigned int cbNameSize,///<Name string buffer size in bytes.
										  char * pCode,///<Pointer to string to be filled with code result.
										  unsigned int cbCodeSize///<Code string buffer size in bytes.
										  );



/**Get Device status

!See:
- w2cDevStatus_tag

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetDeviceStatus(WORD wDeviceID,///< Device ID
								   LPW2CDEVSTATUS  pStatus ///< pointer to W2CDEVSTATUS structure to be filled with result.
								   );
/**Get the Parallel Phone Hook switch state.
A parallel phone is a phone device connected
to the same line the Hi-Phone is connected to.

\note
Currently, the Hi-Phone devices that can detect Parallel Phone Hook switch state are:

- Hi-Phone Desktop Pro. (W2C_DEV_MODEL_PRO).
- Hi-Phone Maestro (W2C_DEV_MODEL_MAESTRO).

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_GetDeviceParallelHookState(WORD wDeviceID,///<Device ID
											  unsigned char * pParallelHook /**<Pointer to unsigned char to be filled with result.
																			0 == On-Hook
																			1 == Off-Hook.
											                                */
											  );



/** Get line wire plugged state.

!See:
- W2C_ERR_LINE_NOT_CONNECTED
- HPEVT_LINE_UNPLUGGED

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_GetDeviceLineWirePlugged(WORD wDeviceID,///<Device ID
											unsigned char * pLineWirePlugged /**<Pointer to unsigned char to be filled with result.
																			0 == Line wire is unplugged
																			1 == Line wire is plugged.
											                                */
											  );



/**Attach \ Detach a terminal (local phone or local headset) to \ from a line.

For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

The Hi-Phone Maestro device has 4 lines, 1 Phone and 1 Headset.
The Phone or Headset are described as a 'terminal'. 


When a terminal (Phone or Headset) is attached (set) to one of the lines,
it's like a physical connection between the line and that terminal.

Depends on "Device Switching Modes" specified for this line,

For local phone terminal:

1. Line and terminal exchange audio.

2. For HPCMD_SW_DEFAULT_PHONE_LINE mode:
   - Incomming call line Ring will ring the (on-hook) local phone.
   - Incomming call line Caller ID will be routed to the local phone.
   - When the local phone goes off-hook, the line will also be 'off-hook'
     (opened for answering a call or make a new call).
   - Local phone hook-flash will be dialed to the line.

6. Local phone dialed DTMF digits will be dialed to the line.

7. Phone Events will be generated within the line device entity.



For local Headset terminal:

1. Line and terminal exchange audio.
   This depends on "Device Switching Modes" specified for this line.

2. Headset plugged/unplugged events will be generated within the line device entity.

The terminal hardware events (Ringer, Hook-Switch, Headset Plugged),
can  be attched to a single line only.
Note that the terminal(s) audio can be attched to multiple lines simultaneously.

The line that had a terminal hardware events attached to,
will receive  HP_EVENT_LINE_TERMINAL_CHANGED
when other line called this function and 'took over' the terminal hardware events.

Hardware events
- HPEVT_PHONE_OFF_HOOK
- HPEVT_PHONE_ON_HOOK
- HPEVT_HEADSET1_OUT
- HPEVT_HEADSET1_IN
- HPEVT_HEADSET2_OUT
- HPEVT_HEADSET2_IN

Will be reported when a terminal is detached from a line.




The dwTerminalMode flags:
- W2C_TERMMODE_NONE
- W2C_TERMMODE_RINGER
- W2C_TERMMODE_HOOKSWITCH
- W2C_TERMMODE_MEDIATOLINE
- W2C_TERMMODE_MEDIAFROMLINE
- W2C_TERMMODE_PLUGGED
\n

!See:
- w2cUsbM_GetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- "Hi-Phone Maestro Features"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_SetTerminal(WORD wDeviceID,///<The (global) driver device ID
                            DWORD dwTerminalID,///<Terminal ID: W2C_TERMINAL_PHONE -or- W2C_TERMINAL_HEADSET
                            DWORD dwTerminalMode,///<Can be W2C_TERMMODE_NONE, or a logical OR combination of W2C_TERMMODE_RINGER , W2C_TERMMODE_HOOKSWITCH, W2C_TERMMODE_MEDIATOLINE, W2C_TERMMODE_MEDIAFROMLINE
                            DWORD dwReserved///<Reserved, must be zero
                            );



/**Query if and how a terminal is attached to a line.

For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

The dwTerminalMode flags:
- W2C_TERMMODE_NONE
- W2C_TERMMODE_RINGER
- W2C_TERMMODE_HOOKSWITCH
- W2C_TERMMODE_MEDIATOLINE
- W2C_TERMMODE_MEDIAFROMLINE
- W2C_TERMMODE_PLUGGED

\n
!See:
- w2cUsbM_SetTerminal
- HP_EVENT_LINE_TERMINAL_CHANGED
- "Hi-Phone Maestro Features"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_GetTerminal(WORD wDeviceID,///<The (global) driver device ID
                            DWORD dwTerminalID,///<Terminal ID: W2C_TERMINAL_PHONE -or- W2C_TERMINAL_HEADSET
                            LPDWORD lpdwTerminalMode,///<Pointer to be filled with result:W2C_TERMMODE_XXX flags
                            DWORD dwReserved///<Reserved, must be zero
                            );


/**Query if the number of devices present on the system has changed.

This function does not require any other driver function.
Since the function is very lite and fast,
application may poll this function periodically. 

If lpdwResult is not zero, the application should closed and then re-start or re configure.

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_FastIsNumDevsChanged(LPDWORD lpdwResult,///<Pointer to be filled with result:0==No change, 1==the number of devices present on the system has changed.
										DWORD dwReserved///<Reserved, must be zero
										); 

/**Add a line device to the specified lines conference.
For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

The function can be called multiple times in order to conference
multiple devices that belongs to the same maestro device.
(The devices will have the same serial number, but different name) 



!See:
- HP_EVENT_MATRIX_ERROR
- HP_EVENT_CONFERENCE_CONNECTED
- HP_EVENT_CONFERENCE_DISCONNECTED
- W2C_CONFERENCE_ID_MAESTRO_A
- W2C_CONFERENCE_ID_MAESTRO_B
- w2cUsbM_ConferenceRemove
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_ConferenceAdd(WORD  wDeviceID,///<The requesting device ID
								 WORD  wConferenceID,///<The Conference ID. Can be W2C_CONFERENCE_ID_MAESTRO_A or W2C_CONFERENCE_ID_MAESTRO_B
								 DWORD dwReserved///<Reserved, must be zero
								);



/**Remove a line device from the specified lines conference.
For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

The function can be called multiple times in order to
remove multiple members from a conference.




!See:
- W2C_CONFERENCE_ID_MAESTRO_A
- W2C_CONFERENCE_ID_MAESTRO_B
- HP_EVENT_CONFERENCE_CONNECTED
- HP_EVENT_CONFERENCE_DISCONNECTED
- w2cUsbM_ConferenceAdd
- w2cUsbM_ConferenceGetMembers
- "Hi-Phone Maestro Features"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_ConferenceRemove(WORD  wDeviceID,///<The requesting device ID
								    WORD  wConferenceID,///<The Conference ID. Can be W2C_CONFERENCE_ID_MAESTRO_A or W2C_CONFERENCE_ID_MAESTRO_B
								    DWORD dwReserved///<Reserved, must be zero
								    );



/**Get conferenc members devices.
For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.

The function queries which devices are members of conference W2C_CONFERENCE_ID_MAESTRO_A or W2C_CONFERENCE_ID_MAESTRO_B.

Number of IDs entries specified with pwNumDeviceIDs in pwDeviceIDsArray
Must be at least 4.

When the function returns, pwNumLineIDs specifies the number of IDs written to pwLineIDsArray.


!See:
- W2C_CONFERENCE_ID_MAESTRO_A
- W2C_CONFERENCE_ID_MAESTRO_B
- HP_EVENT_CONFERENCE_CONNECTED
- HP_EVENT_CONFERENCE_DISCONNECTED
- w2cUsbM_ConferenceAdd
- w2cUsbM_ConferenceRemove
- "Hi-Phone Maestro Features"

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX

*/
int WINAPI w2cUsbM_ConferenceGetMembers(WORD   wDeviceID,///<The requesting device ID
									    WORD   wConferenceID,///<The Conference ID. Can be W2C_CONFERENCE_ID_MAESTRO_A or W2C_CONFERENCE_ID_MAESTRO_B
								        LPWORD pwDeviceIDsArray,///<Pointer to WORD array to result with conference member device IDs
								        LPWORD pwNumDeviceIDs,///<Pointer to the Number of IDs entries in pwLineIDsArray, must be at least 4. Result.
									    DWORD  dwReserved///<Reserved, must be zero
								        );





/**Assign the Thumb Wheel to control a volume.
For Hi-Phone Maestro W2C_DEV_MODEL_MAESTRO device only.
  
The following volumes can be controlled by Thumb Wheel:

- HP_PhoneOutVolume
- HP_PhoneInVolume
- HP_PhoneLineVolume
- HP_PhonePlaybackVolume
- HP_PhoneRecordingVolume
- HP_HeadsetOutVolume
- HP_HeadsetInVolume
- HP_HeadsetSideToneVolume
- HP_HeadsetLineVolume
- HP_HeadsetPlaybackVolume
- HP_HeadsetRecordingVolume
- HP_LinePlaybackVolume
- HP_LineRecordingVolume

When the Thumb Wheel is moved (changed), the HPEVT_VOLUME_CHANGED event will be fired.

To remove the attachment specify 0xFF.

Device that has assigned the Thumb Weel for its use,
will receive HPEVT_THUMB_WHEEL_REASSIGNED when other device assign the Thumb Weel for its use,

!See:
- HPEVT_THUMB_WHEEL_REASSIGNED
- w2cUsbM_GetVolume
- w2cUsbM_SetVolume
- HPEVT_VOLUME_CHANGED event

\return W2C_ERR_SUCCESS or other W2C_ERR_XXX
*/
int WINAPI w2cUsbM_ThumbWheelAssign(WORD wDeviceID,///The (global) driver device ID
									unsigned char iSubDevice///< Hi-Phone component such as HP_HeadsetOutVolume
									);

#ifdef __cplusplus
}
#endif


#pragma message("\nWay2call Multiple Hi-Phone Devices DLL API version 1.06.02\n")

//---------------------------------------------------------------------
#endif	
