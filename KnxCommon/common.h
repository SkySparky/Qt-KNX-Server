/*
 * common.h
 *
 *  Created on: 22 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <cstdio>
#include <QtCore>
#include <QDir>
#include <QFile>
#include <QMutex>

#define snprintf _snprintf

//#define DEBUG	1

#ifndef OK
#define OK		            1
#endif

#ifndef FAIL
#define FAIL	            -1
#endif

#ifndef FALSE
#define FALSE               0
#endif

#ifndef TRUE
#define TRUE                1
#endif

#ifndef NULL
#define NULL                ( (void*) 0 )
#endif

#ifndef EXIT_FAILURE
#define EXIT_FAILURE        1
#endif

#ifndef EXIT_SUCCESS
#define EXIT_SUCCESS        0
#endif

#define TRACE(_X_) {\
                if (DEBUG) {\
                    printf _X_;\
                    printf("\n");\
                }\
                }

#define TRACERR(_X_) {\
                if (DEBUG) {\
                    printf _X_;\
                    printf("\n");\
                    exit(0);\
                }\
                }

#define APPEND(X, Y) X##Y



namespace Common {

    typedef enum {
        PARAM_CMD = 1,
        PARAM_SENDER,
        PARAM_DEST,
        PARAM_DATA_START
    } en_param_type;

    typedef enum {
        MSG_TYPE_ERROR = 1,
        MSG_TYPE_WARNING,
        MSG_TYPE_INFO
    } en_msg_type;

    typedef enum {
        SCREEN_ID_STAGE,
        SCREEN_ID_BACKSTAGE
    } en_screenId;

    typedef enum {
        NOTIFY_KNX_SEARCH_REQ = 0,
        NOTIFY_KNX_SEARCH_RESULT,
        NOTIFY_KNX_DESCR_REQ = 2,
        NOTIFY_KNX_DESCR_RESULT,
        NOTIFY_SETTINGS_REQ = 4,
        NOTIFY_SETTINGS_SAVE_REQ,
        NOTIFY_START_MONITORING_REQ = 6,
        NOTIFY_SEND_DATA_TO_KNX,
        NOTIFY_RESET_ALL = 8,
        NOTIFY_ADD_DEVICE,
        NOTIFY_AUTOSEARCH = 10,
        NOTIFY_IMPORT_CONFIG,
        NOTIFY_EXPORT_CONFIG = 12,
        NOTIFY_KNX_CONNECTED,
        NOTIFY_KNX_DISCONNECTED = 14,
        NOTIFY_REMOVE_DEVICE,
        NOTIFY_EDIT_DEVICE = 16,
        NOTIFY_BACKSTAGE_COMPLETED,

        //For stag/backstage only
        NOTIFY_STAGE_BACK = 18,
        NOTIFY_STAGE_UPDATE_SCREEN,
        NOTIFY_STAGE_UPDATE_VALUE = 20,
        NOTIFY_STAGE_EXIT,
        NOTIFY_STAGE_QUIT = 22,
        NOTIFY_STAGE_RECONNECT,
        NOTIFY_STAGE_USE_CONF = 24
    } en_notifyType;


    typedef enum {
        PARAM_TYPE_UNKNOWN = 0,
        PARAM_TYPE_INT,
        PARAM_TYPE_STRING,
        PARAM_TYPE_DOUBLE,
        PARAM_TYPE_DATE,
        PARAM_TYPE_TIME = 5,
        PARAM_TYPE_GPS,
        PARAM_TYPE_TIMESTAMP,
        PARAM_TYPE_KNX_1BIT,
        PARAM_TYPE_KNX_4BIT,
        PARAM_TYPE_KNX_8BIT = 10,
        PARAM_TYPE_KNX_DATE,
        PARAM_TYPE_KNX_TIME,
        PARAM_TYPE_KNX_TEMP
    } paramType_en;


    /**
     * \bDirExists
     */
    bool			DirExists(const char * dirName);
    bool 			FileExists(QString &fName);
    int 			ReadFileLines(std::string fName, std::vector<std::string> & contents);
    //int 			EraseSpaces_c(unsigned char * data, int dataLen);
    QString 		ByteValueToString(unsigned char * data, int dataLen);
    int				StrValueToBytes(QString &data, unsigned char * value);
    int				StrValueToUint(QString &knxData);
    std::string  	IntToStr(int intToConvert);
    int 			PhysAddrToInt(QString &strAddr);
    unsigned int	GroupAddrToInt(QString &groupAddr);
    unsigned int 	GroupAddrToInt(const char * groupAddr);
    unsigned int	GroupAddrToStr(const unsigned int groupAddr, char * strAddr, const size_t strAddrLen);
    QString			GroupAddrToStr(const unsigned int groupAddr);
    int				CnvGroupAddrType(QString &strType);
    QString			ConvertGaValue(QString &strValue, int type);
    QString			GetParam(QString inString, int param, QString separator = ",");
}
#endif /* COMMON_H_ */
