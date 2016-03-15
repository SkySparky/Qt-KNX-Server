/*
 * httpResponse.h
 *
 *  Created on: 27 Σεπ 2010
 *      Author: Administrator
 */

#ifndef HTTPRESPONSE_H_
#define HTTPRESPONSE_H_

#include "../KnxCommon/common.h"
#include <QByteArray>

class HttpResponse {
public:
	HttpResponse(QString & responseData);
	~HttpResponse();
	const char * GetHeader();

private:
	QByteArray httpData;
};

#endif /* HTTPRESPONSE_H_ */
