/*
 * hpai.cpp
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */
#include "hpai.h"

Hpai::Hpai(const unsigned char * data, qint64 dataLen)
{
	//create hpai from raw data
	hpai_t.length = (unsigned char) data[0];
	hpai_t.protocol = (unsigned char) data[1];

	hpai_t.ip = data[2];
	hpai_t.ip <<= 8;
	hpai_t.ip += data[3];
	hpai_t.ip <<= 8;
	hpai_t.ip += data[4];
	hpai_t.ip <<= 8;
	hpai_t.ip += data[5];

	char tmpChar[100];
    //snprintf(tmpChar, 100, "%d.%d.%d.%d", data[2], data[3], data[4], data[5]);
    sprintf(tmpChar, "%d.%d.%d.%d", data[2], data[3], data[4], data[5]);

	hpai_t.port = data[6];
	hpai_t.port <<= 8;
	hpai_t.port += data[7];
}

Hpai::Hpai(QString & ipAddr, unsigned short ipPort, unsigned char protocol)
{
	hpai_t.length = HPAI_LENGTH;
	hpai_t.protocol = protocol;
	hpai_t.ip = IpStrToInt(ipAddr.toLatin1());
	hpai_t.port = (unsigned char) (ipPort & 0xFF);
	hpai_t.port <<= 8;
	hpai_t.port += (unsigned char)(ipPort >> 8);

	/*
	TRACE(("HPAI bytes(%du):", sizeof(tp_HPAI) ));
	for (size_t i=0; i<sizeof(tp_HPAI); i++) {
		printf("%02X ", buffer[i]);
	}
	printf("\n");
	*/
}

Hpai::~Hpai()
{

}

int Hpai::SetHpaiData(const unsigned char * data, qint64 dataLen)
{
    hpai_t.length = (unsigned char) data[0];
    hpai_t.protocol = (unsigned char) data[1];

    hpai_t.ip = data[2];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[3];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[4];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[5];

    char tmpChar[100];
    //snprintf(tmpChar, 100, "%d.%d.%d.%d", data[2], data[3], data[4], data[5]);
    sprintf(tmpChar, "%d.%d.%d.%d", data[2], data[3], data[4], data[5]);

    hpai_t.port = data[6];
    hpai_t.port <<= 8;
    hpai_t.port += data[7];

    return(sizeof(hpai_t));
}

size_t Hpai::GetHpaiData(unsigned char * data) {
	data[0] = hpai_t.length;
	data[1] = hpai_t.protocol;
	data[2] = (unsigned char)(hpai_t.ip);
	data[3] = (unsigned char)(hpai_t.ip >> 8);
	data[4] = (unsigned char)(hpai_t.ip >> 16);
	data[5] = (unsigned char)(hpai_t.ip >> 24);
	data[6] = (unsigned char)(hpai_t.port);
	data[7] = (unsigned char)(hpai_t.port >> 8);

	return(HPAI_LENGTH);
}

void Hpai::GetAddr(char * ipAddr)
{
    //snprintf(ipAddr, 20, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));
    sprintf(ipAddr, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));

}

unsigned short  Hpai::GetPort(void)
{
	return(hpai_t.port);
}

unsigned char  Hpai::GetProtocol(void)
{
	return(hpai_t.protocol);
}


int Hpai::IpStrToInt(const char * ipStr)
{
    unsigned char buffer[4];
    int ipInt;

    sscanf(ipStr,"%d.%d.%d.%d",
    (unsigned char *)&buffer[0],(unsigned char *)&buffer[1],
    (unsigned char *)&buffer[2],(unsigned char *)&buffer[3]);

    ipInt = buffer[3];
    ipInt <<= 8;
    ipInt += buffer[2];
    ipInt <<= 8;
    ipInt += buffer[1];
    ipInt <<= 8;
    ipInt += buffer[0];

    return ipInt;
}
