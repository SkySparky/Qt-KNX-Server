/*
 * cemi.h
 *
 *  Created on: 22 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef CEMI_H_
#define CEMI_H_

#include <QtCore>
#include <QDebug>
#include "common.h"

#define CEMI_GROUPADDR_STRLEN	10

/**
* \class This object is used when transmitting or receiving data from the bus.
* cEMI contains info about the data, the command type and the receiver/sender of a datagram.
*/
class cEMI {
	/**
	* \brief Converts the group address from int to string
	*/
	void SetGroupAddStr(void);
public:
    typedef enum {
        L_DATA_REQ = 0x11,	//used to set value
        L_DATA_CON = 0x2E,	//is comming only from gateway to confirm that the client cmd is retrieved
        L_DATA_IND = 0x29	//is comming only from gateway to send a packet from the bus
    } tp_L_Data;

    /**
    * \enum This byte defines the action of the command on the bus.
    * According to the action the system will read or write the given group address.
    */
    typedef enum {
        CEMI_ACTION_READ = 0,		/*!< Read the value of the group address */
        CEMI_ACTION_RESP = 0x40,	/*!< Not used int this implementation */
        CEMI_ACTION_WRITE = 0x80	/*!< Write the value of the group address */
    } en_cemiAction;

    /**
    * \struct This is the control byte 1 that all cEMI frames are using.
    */
    typedef struct {
        unsigned char frameType:1;		/*!< 0: normal frame type, 1: extended frame */
        unsigned char reserved:1;		/*!< Not used. */
        unsigned char repeatFlag:1;		/*!< 0: do not repeat datagram */
        unsigned char sysBroadcast:1;	/*!< 0: system broadcast, 1: broadcast */
        unsigned char priority:2;		/*!< 0: alarm, 1: system, 2: high, 3: normal */
        unsigned char reqAck:1;			/*!< 0: don't need ACK, 1: request ACK */
        unsigned char confirm:1;		/*!< 0: don't need confirm, 1: request confirmation */
    } tp_ctrl1;

    /**
    * \union This union is used to resolve the control byte 1 to it's bits.
    */
    typedef union {
        tp_ctrl1 		bits;			/*!< CTRL1 bits */
        unsigned char	byte;			/*!< CTRL1 byte */
    } un_ctrl1;

    /**
    * \struct This is the control byte 2 that all cEMI frames are using.
    */
    typedef struct {
        unsigned char addrType:1;		/*!< 0: ,1: */
        unsigned char hopCount:3;		/*!< Number of hops on the bus */
        unsigned char extFrameFormat:4;	/*!< Extended frame format */
    } tp_ctrl2;

    /**
    * \union This union is used to resolve the control byte 2 to it's bits.
    */
    typedef union {
        tp_ctrl2 	bits;				/*!< CTRL2 bits */
        unsigned char	byte;			/*!< CTRL2 byte */
    } un_ctrl2;

    /**
    * \struct This is a cEMI container. cEMI contains the command that will transmit on the bus
    */
    typedef struct {
        unsigned char 	l_data;			/*!< L_Data.req, L_Data.con or L_Data.ind */
        unsigned char 	additionalInfo;	/*!< Always 0 */
        un_ctrl1		ctrl1;			/*!< Control Byte 1 */
        un_ctrl2		ctrl2;			/*!< Control byte 2 */
        unsigned short	srcAddr;		/*!< Source physical address */
        unsigned short	destAddr;		/*!< Destination group address */
        unsigned char	dataLen;		/*!< Length of the data */
        unsigned char * data;			/*!< Data buffer */
        en_cemiAction	action;
    } tp_cEMI;

	tp_cEMI	cemi;					/*!< cEMI container */
	char groupAddr[CEMI_GROUPADDR_STRLEN];	/*!< the cEMI group address in byte string */

	/**
	* \brief This is a simple cEMI constructor. After creation the cEMI contains no data.
	*/
	cEMI();

	//cEMI(const cEMI& copy);

	/**
	* \brief This constructor creates a cEMI from a given tp_cEMI structure
	* \param[in]	cemiData	The tp_cEMI structure from which the object will be created
	*/
	cEMI(tp_cEMI * cemiData);

	/**
	* \brief This constructor creates a cEMI object from raw binary data.
	* @param[in]	data	The data buffer
	* @param[in]	dataLen	The data length
	*/
	cEMI(unsigned char * data, size_t dataLen);

	/**
	* \brief This constructor creates a cEMI object from the given parameters
	*	l_data = L_DATA_REQ
	*	ctrl1 = 0xBC
	*	ctrl2 = 0xE0
	*	srcAddr = 0.0.0
	* @param[in]	rwAction	CEMI_ACTION_READ: read from bus, CEMI_ACTION_WRITE: write to bus
	* @param[in]	groupAddr	The group address that will be used for the operation
	* @param[in]	data		The data that will be written on the bus
	* @param[in]	dataLen		The data length
	*/
	cEMI(en_cemiAction rwAction, unsigned int groupAddr, const unsigned char * data, size_t dataLen);

    cEMI(QString groupAddr, QString data, en_cemiAction rwAction);

	/**
	* \brief Destructor
	*/
	~cEMI();

	/**
	* \brief This function just prints the cEMI content on the console
	*/
	void DebugPrintCEMI(void);

	/**
	* \brief Update cEMI content with new one
	* @param[in]	cemiData	The new contents
	*/
	void RenewcEMI(tp_cEMI * cemiData);

	/**
	* \brief Fills the given buffer with the cEMI raw data
	* @param[out]	buffer	The output buffer which will be filled with the data
	* @retval	<size_t>	The size of the buffer
	*/
	size_t FillBuffer(unsigned char * buffer);
};

Q_DECLARE_METATYPE(cEMI)

#endif /* CEMI_H_ */
