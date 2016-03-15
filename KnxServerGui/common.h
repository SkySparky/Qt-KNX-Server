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

#define PARAM_CMD		1
#define PARAM_SENDER	2
#define PARAM_DEST		3
#define PARAM_DATA_START	4

#define MSG_TYPE_ERROR  1
#define MSG_TYPE_WARNING  2
#define MSG_TYPE_INFO  3

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

namespace Common {

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
}
#endif /* COMMON_H_ */
