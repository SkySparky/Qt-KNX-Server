/*
 * httpResponse.cpp
 *
 *  Created on: 27 Σεπ 2010
 *      Author: Administrator
 */
#include "httpResponse.h"

HttpResponse::HttpResponse(QString & responseData)
{
	QDateTime now = QDateTime::currentDateTime();

	httpData.append("HTTP/1.1 200 OK\r\nDate: ");
	httpData.append(now.date().toString("ddd, dd MMM yyyy "));
	httpData.append(now.time().toString("HH:mm:ss GMT\r\n"));
	httpData.append("Server: Apache/2.2.11 (Win32) PHP/5.3.0\r\n");
	httpData.append("Last-Modified: Fri, 24 Sep 2010 23:56:34 GMT\r\n");
	//ETag: "21000000032dd8-157-4910a20e66ea9"
	httpData.append("Accept-Ranges: bytes\r\n");
	httpData.append("Content-Length: ");
	httpData.append( QString::number(responseData.length()) );
	httpData.append("\r\nContent-Type: application/xml\r\n");
	httpData.append("X-Pad: avoid browser bug\r\n\r\n");
}

HttpResponse::~HttpResponse()
{
	httpData.clear();
}

const char * HttpResponse::GetHeader()
{
	return((const char*) httpData.data());
}
