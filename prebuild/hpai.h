/*
 * hpai.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef HPAI_H_
#define HPAI_H_

#include "common.h"

#define HPAI_LENGTH     8
#define HPAI_IP_PROTOCOL_IPV4_UDP 1

/**
* \struct tp_HPAI
* \brief The tp_HPAI object contains information about an endpoint.
* End points are used for communication between the client and the gateway and describe each one
*/
#pragma pack(push, 8)
typedef struct {
    unsigned char   length:8;	/*!< Endpoint length */
    unsigned char   protocol:8;	/*!< Protocol used (TCP or UDP) */
    unsigned int    ip:32;		/*!< Endpoint ip address */
    unsigned short  port:16;	/*!< Endpoint ip port */
} tp_HPAI;
#pragma pack(pop)


/**
* \class Hpai
* \brief This class creates an object that contains the data of an endpoint (client or knx/ip gateway).
*/
class Hpai {
public:
    tp_HPAI hpai_t;		/*!< Hpai endpoint container structure */

    /**
    * \brief Hpai constructor
    * This constructor creates an Hpai object from the given data
    * @param[in]	ipAddr	The ip address of the endpoint
    * @param[in]	ipPort	The ip port of the endpoint
    * @param[in]	protocol	The ip protocol 1: UDP, 2: TCP
    */
    Hpai(QString ipAddr, unsigned short ipPort, unsigned char protocol);

    /**
    * \brief Hpai constructor
    * This constructor creates an Hpai object from the given data
    * @param[in]	data	The data buffer that contains the raw endpoint data
    * @param[in]	dataLen	The data length
    */
    Hpai(const unsigned char * data, qint64 dataLen);	//create hpai from raw data

    /**
    * \brief Hpai destructor
    */
    ~Hpai();

    int SetHpaiData(const unsigned char * data, qint64 dataLen);

    /**
    * \brief Extract ip address from the endpoint
    * @param[out]	ipAddr	The ip address string
    */
    void GetAddr(char * ipAddr);
    QString GetAddr();

    /**
    * \brief Retrieve endpoint's ip port
    * @retval	<unsigned short>	The ip port
    */
    unsigned short GetPort(void);

    /**
    * \brief Retrieve protocol
    * @retval	<unsigned char>	The endpoint protocol. 1: UDP, 2:TCP
    */
    unsigned char GetProtocol(void);

    /**
    * \brief Retrieve endpoint's data
    * @param[out]	data	The endpoint's data
    * @retval	<size_t>	The data size
    */
    size_t GetHpaiData(unsigned char * data);

private:
    unsigned char buffer[HPAI_LENGTH];		/*!< The buffer that contains the endpoint's raw data */

    /**
    * \brief Convert an ip string to integer
    * @param[in]	ipStr	The ip string buffer
    * @retval	<int>	An integer that corresponds to the ip address
    */
    unsigned int IpStrToInt(const unsigned char * ipStr);

};

#endif /* HPAI_H_ */
