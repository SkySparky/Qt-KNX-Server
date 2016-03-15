#include "cemi.h"

#define CEMI_L_DATA_REQ		0x11
#define CEMI_L_DATA_CON		0x2E
#define CEMI_L_DATA_IND		0x29

cEMI::cEMI()
{
	//TRACE(("[cEMI]: create default cemi."));
	cemi.data = new unsigned char[256];
}

/*
cEMI::cEMI(const cEMI& copy)
{
	memcpy(&cemi, &copy.cemi, sizeof(tp_cEMI)-1);
	cemi.data = new unsigned char[256];
	qDebug() << "previous pointer: " << copy.cemi.data << ", now: " << cemi.data;
}
*/

cEMI::cEMI(tp_cEMI * cemiData)
{
	//qDebug() << "create";
	cemi.l_data = cemiData->l_data;
	cemi.additionalInfo = cemiData->additionalInfo;	//should be zero
	cemi.ctrl1.byte = cemiData->ctrl1.byte;
	cemi.ctrl2.byte = cemiData->ctrl2.byte;
	cemi.srcAddr = cemiData->srcAddr;
	cemi.destAddr = cemiData->destAddr;
	cemi.dataLen = cemiData->dataLen;

	cemi.data = new unsigned char[cemi.dataLen+1];
	for (size_t i=0; i<=cemi.dataLen; i++) cemi.data[i] = cemiData->data[i];

	SetGroupAddStr();
}


void cEMI::RenewcEMI(tp_cEMI * cemiData)
{
	cemi.l_data = cemiData->l_data;
	cemi.additionalInfo = cemiData->additionalInfo;	//should be zero
	cemi.ctrl1.byte = cemiData->ctrl1.byte;
	cemi.ctrl2.byte = cemiData->ctrl2.byte;
	cemi.srcAddr = cemiData->srcAddr;
	cemi.destAddr = cemiData->destAddr;
	cemi.dataLen = cemiData->dataLen;
	SetGroupAddStr();

	delete [] cemi.data;
	cemi.data = new unsigned char[cemi.dataLen+1];
	for (size_t i=0; i<=cemi.dataLen; i++) cemi.data[i] = cemiData->data[i];
}

cEMI::cEMI(unsigned char * data, size_t dataLen)
{
	cemi.l_data = data[0];
	cemi.additionalInfo = data[1];	//should be zero
	cemi.ctrl1.byte = data[2];
	cemi.ctrl2.byte = data[3];

	cemi.srcAddr = 0;
	cemi.srcAddr = data[4];
	cemi.srcAddr <<= 8;
	cemi.srcAddr += data[5];

	cemi.destAddr = 0;
	cemi.destAddr = data[6];
	cemi.destAddr <<= 8;
	cemi.destAddr += data[7];

	cemi.dataLen = data[8];
	SetGroupAddStr();

	cemi.data = new unsigned char[cemi.dataLen+1];
    for (size_t i=9; i<dataLen; i++) {
        //qDebug() << "cemi data: " << data[i];
        cemi.data[i-9] = data[i];
    }
}


/// \brief cEMI constructor
/// This is the constructor a standard cEMI frame with the following:
///		l_data = L_DATA_REQ
/// 	ctrl1 = 0xBC
///		ctrl2 = 0xE0
///		srcAddr = 0.0.0
/// \param: rwAction, which action to obtain CEMI_ACTION_READ or CEMI_ACTION_WRITE
/// \param: groupAddr, which groupAddr command to send
/// \param: value, the value to send. If it's CEMI_ACTION_READ then it can be null or empty (it's not used)
/// \param: dataLen, the value's length. If it's CEMI_ACTION_READ then it can be 0 or emtpy (it's not used)
/// \return:	-
cEMI::cEMI(en_cemiAction rwAction, unsigned int groupAddr, const unsigned char * data = NULL, size_t dataLen = 0)
{
	cemi.l_data = L_DATA_REQ;	//by default create a cemi that will be sent to bus
	cemi.additionalInfo = 0;	//no additional info
	cemi.ctrl1.byte = 0x8C;		//frameType = 1
								//reserved = 0
								//repeatFlag = 0
								//systemBroadcast = 0
								//priority = 3 (normal)
								//acknowledge = 0
								//confirm = 0

	cemi.ctrl2.byte = 0xE0;		//addressType = 1 (groupAddress)
								//hopCount = 6
								//extFrameFormat = 0 (standard format - not extended)
	cemi.srcAddr = 0;			//this tells to gateway to use it's own physical address
	cemi.destAddr = (unsigned short) groupAddr;
	SetGroupAddStr();

	if (rwAction == CEMI_ACTION_READ) {
		cemi.dataLen = 1;
		cemi.data = new unsigned char[cemi.dataLen+1];
		cemi.data[0] = 0;
		cemi.data[1] = CEMI_ACTION_READ;

	}
	else if (rwAction == CEMI_ACTION_WRITE) {
		cemi.data = new unsigned char[cemi.dataLen+1];
		cemi.data[0] = 0;	//always
		cemi.data[1] = CEMI_ACTION_WRITE;
		if (dataLen == 1) {
			cemi.dataLen = dataLen;
			cemi.data[1] |= data[0];
		}
		else{
			//cemi.dataLen = dataLen + 1;	//add the read/write byte
			//for (size_t i=0; i<dataLen; i++) cemi.data[2+i] = data[i];

			//This works from flash when sending "00 " + value
			cemi.dataLen = dataLen;	//add the read/write byte
			for (size_t i=0; i<dataLen; i++) cemi.data[2+i] = data[i+1];
		}

		/*
		if (dataLen == 1) {
			cemi.dataLen = dataLen;
			for (size_t i=0; i<dataLen; i++) cemi.data[1+i] = data[i];
			cemi.data[1] |= CEMI_ACTION_WRITE;
		}
		else {
			cemi.dataLen = dataLen;
			for (size_t i=0; i<dataLen; i++) cemi.data[1+i] = data[i];
			cemi.data[1] = CEMI_ACTION_WRITE;
		}
		*/
		//qDebug() << "cemi.datalen: " << cemi.dataLen;
	}

}

cEMI::~cEMI()
{
	if (cemi.data != NULL) {
		delete [] cemi.data;
		//TRACE(("[cEMI]: deleted data"));
	}
}


void cEMI::SetGroupAddStr(void)
{
	char strGroupAddr[CEMI_GROUPADDR_STRLEN];
	Common::GroupAddrToStr(cemi.destAddr, strGroupAddr, CEMI_GROUPADDR_STRLEN);
	for (int i = 0; i<CEMI_GROUPADDR_STRLEN; i++) groupAddr[i] = strGroupAddr[i];

}


size_t cEMI::FillBuffer(unsigned char * buffer)
{
	buffer[0] = cemi.l_data;
	buffer[1] = cemi.additionalInfo;
	buffer[2] = cemi.ctrl1.byte;
	buffer[3] = cemi.ctrl2.byte;
	buffer[4] = static_cast<unsigned char>(cemi.srcAddr >> 8);
	buffer[5] = static_cast<unsigned char>(cemi.srcAddr & 0xFF);
	buffer[6] = static_cast<unsigned char>(cemi.destAddr >> 8);
	buffer[7] = static_cast<unsigned char>(cemi.destAddr & 0xFF);
	buffer[8] = cemi.dataLen;
    buffer[9] = 0;
    for (size_t i=10; i<(size_t)(10+cemi.dataLen+1); i++) {
        buffer[i] = cemi.data[i-10];
		//TRACE(("buffer[%d]=%02X", i, cemi.data[i-9]));
	}

	return(cemi.dataLen + 10);
}


void cEMI::DebugPrintCEMI(void)
{
	qDebug("[cEMI]: L_DATA: 0x%02X", cemi.l_data);

	qDebug("[cEMI]: additional info: %d", (int)cemi.additionalInfo);

	qDebug("[cEMI]: ctrl1.frametype: %d", (int)cemi.ctrl1.bits.frameType);
	qDebug("[cEMI]: ctrl1.repeatFlag: %d", (int)cemi.ctrl1.bits.repeatFlag);
	qDebug("[cEMI]: ctrl1.sysBroadcast: %d", (int)cemi.ctrl1.bits.sysBroadcast);
	qDebug("[cEMI]: ctrl1.priority: %d", (int)cemi.ctrl1.bits.priority);
	qDebug("[cEMI]: ctrl1.reqAck: %d", (int)cemi.ctrl1.bits.reqAck);
	qDebug("[cEMI]: ctrl1.confirm: %d", (int)cemi.ctrl1.bits.confirm);

	qDebug("[cEMI]: ctrl2.addrType: %d", (int)cemi.ctrl2.bits.addrType);
	qDebug("[cEMI]: ctrl2.hopCount: %d", (int)cemi.ctrl2.bits.hopCount);
	qDebug("[cEMI]: ctrl2.extFrameFormat: %d", (int)cemi.ctrl2.bits.extFrameFormat);

	qDebug("[cEMI]: dest addr: %d", cemi.destAddr);
	qDebug("[cEMI]: src addr: %d", cemi.srcAddr);

	qDebug("[cEMI]: dataLen: %d", cemi.dataLen);


	QString tmpStr;
	char tmpcStr[20];
	for (int i=0; i<cemi.dataLen+1; i++) {
		sprintf(tmpcStr, "%02X", (int)cemi.data[i]);
		tmpStr += tmpcStr;
	}
	qDebug() << "[cEMI::DebugPrintCEMI]: data= " << tmpStr;
}
