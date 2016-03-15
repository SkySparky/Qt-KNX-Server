/*
 * hpai.cpp
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */
#include "hpai.h"

Hpai::Hpai(const unsigned char * data, qint64 dataLen)
{
    if (dataLen < 8) return;

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

    hpai_t.port = data[6];
    hpai_t.port <<= 8;
    hpai_t.port += data[7];
}

Hpai::Hpai(QString ipAddr, unsigned short ipPort, unsigned char protocol)
{
    hpai_t.length = HPAI_LENGTH;
    hpai_t.protocol = protocol;

    //qDebug() << "Segmentation";

    QByteArray byteArray = ipAddr.toLatin1();
    const unsigned char* cString = (unsigned char*) byteArray.data();
    hpai_t.ip = IpStrToInt(cString);
    hpai_t.port = ipPort;


    //qDebug() << "Segmentation?";
}

Hpai::~Hpai()
{

}

int Hpai::SetHpaiData(const unsigned char * data, qint64 dataLen)
{
    if (dataLen < 8) return 0;

    hpai_t.length = (unsigned char) data[0];
    hpai_t.protocol = (unsigned char) data[1];

    hpai_t.ip = data[2];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[3];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[4];
    hpai_t.ip <<= 8;
    hpai_t.ip += data[5];


    hpai_t.port = data[6];
    hpai_t.port <<= 8;
    hpai_t.port += data[7];

    return(sizeof(hpai_t));
}

size_t Hpai::GetHpaiData(unsigned char * data) {
    data[0] = hpai_t.length;
    data[1] = hpai_t.protocol;
    data[2] = (unsigned char)(hpai_t.ip >> 24);
    data[3] = (unsigned char)(hpai_t.ip >> 16);
    data[4] = (unsigned char)(hpai_t.ip >> 8);
    data[5] = (unsigned char)(hpai_t.ip);
    data[6] = (unsigned char)(hpai_t.port >> 8);
    data[7] = (unsigned char)(hpai_t.port);

    return(HPAI_LENGTH);
}

void Hpai::GetAddr(char * ipAddr)
{
    //snprintf(ipAddr, 20, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));
    sprintf(ipAddr, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));

}

QString Hpai::GetAddr()
{
    //snprintf(ipAddr, 20, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));
    //sprintf(ipAddr, "%d.%d.%d.%d", 0xff&(hpai_t.ip >> 24), 0xff&(hpai_t.ip >> 16), 0xff&(hpai_t.ip >> 8), 0xff&(hpai_t.ip));
    QString addr = QString::number(0xff&(hpai_t.ip >> 24)) + "." +
            QString::number(0xff&(hpai_t.ip >> 16)) + "." +
            QString::number(0xff&(hpai_t.ip >> 8)) + "." +
            QString::number(0xff&(hpai_t.ip));
    return(addr);
}

unsigned short  Hpai::GetPort(void)
{
    return(hpai_t.port);
}

unsigned char  Hpai::GetProtocol(void)
{
    return(hpai_t.protocol);
}


unsigned int Hpai::IpStrToInt(const unsigned char * ipStr)
{
    unsigned int ipInt;
    int vals[4];

    sscanf((char*)ipStr,"%d.%d.%d.%d",
    &vals[0],&vals[1],
    &vals[2],&vals[3]);

    ipInt = 0xff & vals[0];
    ipInt <<= 8;
    ipInt += 0xff & vals[1];
    ipInt <<= 8;
    ipInt += 0xff & vals[2];
    ipInt <<= 8;
    ipInt += 0xff & vals[3];

    return ipInt;
}
