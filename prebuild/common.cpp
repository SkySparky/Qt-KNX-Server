/*
 * common.cpp
 *
 *  Created on: Jun 14, 2010
 *      Author: jaco
 */
#include "common.h"

using namespace std;

namespace Common {

int extractNumber(int index, const char * fromStr, size_t startPos, size_t endPos, size_t * nextPos);

/*
\brief Common_DirExists
Checks if the given directory exists
\param: dirName, the directory name to check
\retval: true if directory exists, else false
*/
bool DirExists(const char * dirName)
{
	QDir dir(dirName);
	bool ret = true;
	if(!dir.exists())
		ret = false;

	return(ret);
}

bool FileExists(QString &fName)
{
	bool resp = true;
	QFile file(fName);

	if (!QFile::exists(fName)) resp = false;

	return(resp);
}

/*
int EraseSpaces(unsigned char * data, int dataLen)
{
	char tmpData[dataLen];
	int k = 0;
	for(int i=0; (data[i] != 0); i++) {
		if (data[i] != ' ') {
			tmpData[k] = data[i];
			k++;
		}
	}
	memcpy(data, tmpData, k);
	data[k] = 0;
	return(k);
}
*/

int StrValueToBytes(QString &data, unsigned char * value)
{
	int k = 0;
	data.remove(QChar(' '), Qt::CaseInsensitive);
	for (int i=0; i<data.length(); i+=2) {
		//qDebug() << value[k];
		value[k] = (unsigned char) data.mid(i, 2).toInt(0, 16);
		k++;
	}
	return(k);
}

int StrValueToUint(QString &knxData)
{
	int nBytes = 0;
	int retVal = -1;

	unsigned char bData[255];
	nBytes = StrValueToBytes(knxData, bData);
	if (nBytes > 1) {
		for (int i=0; i<nBytes; i++) {
			retVal += bData[i+1] << (8*i);	//always skip byte0
		}
	}
	qDebug() << "[Common:StrValueToUint] retVal=" << retVal;
	return(retVal);
}

QString ByteValueToString(unsigned char * data, int dataLen)
{
	QString res;
	char tmp[5];

	res.clear();

	for (int i=0; i<dataLen; i++) {
        //snprintf(tmp, 5, "%02X ", data[i]);
        sprintf(tmp, "%02X ", data[i]);
		res += tmp;
	}

	return(res.trimmed());
}


string IntToStr(int intToConvert)
{
	QString out(intToConvert);
	return(out.toStdString());
}

QString IntToStrValue(int intValue)
{
	QString result;
	char tmpVal[10];
    //snprintf(tmpVal, 10, "%02X %02X", (unsigned char)(intValue >> 8), (unsigned char)(intValue));
    sprintf(tmpVal, "%02X %02X", (unsigned char)(intValue >> 8), (unsigned char)(intValue));
	result = tmpVal;
	qDebug() << "[Common:IntToStrValue] val=" << result;
	return(result);
}


int PhysAddrToInt(QString &strAddr)
{
	QStringList nums = strAddr.split('.');
	return(nums[0].toInt() * 4096 + nums[1].toInt() * 256 + nums[2].toInt());
}


unsigned int GroupAddrToInt(QString &groupAddr)
{
	QStringList nums = groupAddr.split('/');
	return(nums[0].toInt() * 2048 + nums[1].toInt() * 256 + nums[2].toInt());
}

unsigned int GroupAddrToInt(const char * groupAddr)
{
	QString tmpStr(groupAddr);
	unsigned int ret = GroupAddrToInt(tmpStr);
	return(ret);
}


unsigned int GroupAddrToStr(const unsigned int groupAddr, char * strAddr, const size_t strAddrLen)
{
	// 5bits/3bits/8bits
    //snprintf(strAddr, strAddrLen, "%d/%d/%d", (char)(groupAddr >> 11), (char) ((groupAddr >> 8) & 0x07), (char)(groupAddr & 0xFF));
    sprintf(strAddr, "%d/%d/%d", (char)(groupAddr >> 11), (char) ((groupAddr >> 8) & 0x07), (char)(groupAddr & 0xFF));
    return(strAddrLen);
}

QString GroupAddrToStr(const unsigned int groupAddr)
{
	// 5bits/3bits/8bits
	char tmpStr[20];
    //snprintf(tmpStr, 20, "%d/%d/%d", (char)(groupAddr >> 11), (char) ((groupAddr >> 8) & 0x07), (char)(groupAddr & 0xFF));
    sprintf(tmpStr, "%d/%d/%d", (char)(groupAddr >> 11), (char) ((groupAddr >> 8) & 0x07), (char)(groupAddr & 0xFF));
	QString result = tmpStr;
	return(result);
}

int extractNumber(int index, const char * fromStr, size_t startPos, size_t endPos, size_t * nextPos)
{
    int result;
    char tmpChr[4];
    size_t i, k;

    for (i=startPos; i<=endPos; i++) {
        if (fromStr[i] == '/') {

            for (k=startPos; k<i; k++) tmpChr[k-startPos] = fromStr[k];

            *nextPos = i + 1;
            tmpChr[k-startPos] = 0;
            result = atoi(tmpChr);

            return result;
        }
        else if (fromStr[i] == 0) { //end of string
            if ( index == 3 ) {   //last char
                for (k=startPos; k<i; k++) tmpChr[k-startPos] = fromStr[k];
                tmpChr[k-startPos] = 0;
                result = atoi(tmpChr);

                return result;
            }
            else
                result = -1;
        }
        //else result = -2;
    }
    return result;
}

QString ConvertGaValue(QString &strValue, int type)
{
	QString resp;
	if (type == PARAM_TYPE_UNKNOWN) {

	}
	else if (type == PARAM_TYPE_INT) {

	}
	else if (type == PARAM_TYPE_STRING) {

	}
	else if (type == PARAM_TYPE_STRING) {

	}
	else if (type == PARAM_TYPE_DOUBLE) {

	}
	else if (type == PARAM_TYPE_DATE) {

	}
	else if (type == PARAM_TYPE_TIME) {

	}
	else if (type == PARAM_TYPE_GPS) {

	}
	else if (type == PARAM_TYPE_TIMESTAMP) {

	}
	else if (type == PARAM_TYPE_KNX_1BIT) {
		int val = strValue.toInt();
		if (val) resp = "01";
		else resp = "00";
	}
	else if (type == PARAM_TYPE_KNX_8BIT) {
		resp = IntToStrValue(strValue.toInt());
	}
	else if (type == PARAM_TYPE_KNX_DATE) {

	}
	else if (type == PARAM_TYPE_KNX_TIME) {

	}
	else if (type == PARAM_TYPE_KNX_TEMP) {

	}

	return(resp);
}

int CnvGroupAddrType(QString &strType)
{
	int type = PARAM_TYPE_UNKNOWN;
	if (strType == "PARAM_TYPE_INT")
		type = PARAM_TYPE_INT;
	else if (strType == "PARAM_TYPE_STRING")
		type = PARAM_TYPE_STRING;
	else if (strType == "PARAM_TYPE_DOUBLE")
		type = PARAM_TYPE_DOUBLE;
	else if (strType == "PARAM_TYPE_DATE")
		type = PARAM_TYPE_DATE;
	else if (strType == "PARAM_TYPE_TIME")
		type = PARAM_TYPE_TIME;
	else if (strType == "PARAM_TYPE_GPS")
		type = PARAM_TYPE_GPS;
	else if (strType == "PARAM_TYPE_TIMESTAMP")
		type = PARAM_TYPE_TIMESTAMP;
	else if (strType == "PARAM_TYPE_KNX_1BIT")
		type = PARAM_TYPE_KNX_1BIT;
	else if (strType == "PARAM_TYPE_KNX_4BIT")
		type = PARAM_TYPE_KNX_4BIT;
	else if (strType == "PARAM_TYPE_KNX_8BIT")
		type = PARAM_TYPE_KNX_8BIT;
	else if (strType == "PARAM_TYPE_KNX_DATE")
		type = PARAM_TYPE_KNX_DATE;
	else if (strType == "PARAM_TYPE_KNX_TIME")
		type = PARAM_TYPE_KNX_TIME;
	else if (strType == "PARAM_TYPE_KNX_TEMP")
		type = PARAM_TYPE_KNX_TEMP;

	return(type);
}

QString GetParam(QString inString, int param, QString separator)
{
    QString strResult;

    QT_TRY {
        QStringList params = inString.split(separator);
        //QString retString = params.at(param+1);
        if (params.isEmpty() == false) {
            //qDebug() << "inString: " << inString;
            strResult = params.at(param-1);
            QStringList splitParms = strResult.split("=");
            if (splitParms.count() == 2) {
                //QString dbParamName = splitParms[0];	//get param name
                strResult = splitParms[1];		//get param value
            }
        }
    }
    QT_CATCH(...) {
        qDebug() << "GetParam error with: " + inString;
    }
    return(strResult);
}


}
