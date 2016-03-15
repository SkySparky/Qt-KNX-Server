/*
 * tcpServer.cpp
 *
 *  Created on: 02 Αυγ 2010
 *      Author: Administrator
 */
#include "tcpServer.h"

char XML_CROSS_DOMAIN[] = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>"
        "<cross-domain-policy xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:noNamespaceSchemaLocation=\"http://www.adobe.com/xml/schemas/PolicyFileSocket.xsd\">"
        "<allow-access-from domain=\"*\" to-ports=\"*"" secure=\"false\" />"
        "<site-control permitted-cross-domain-policies=\"master-only\" />"
        "</cross-domain-policy>";

TcpServer::TcpServer()
{
	//Read conf
	Conf config;
	this->svrPort = config.GetParameter("WEB/listen_port").toInt();
	this->svrAddr = config.GetParameter("WEB/listen_ip").toString();
	this->maxConnections = config.GetParameter("WEB/max_connections").toInt();

	//qDebug() << "[TcpServer::TcpServer] Creating tcp server (" << this->svrAddr.toString() << "," << this->svrPort << "," << this->maxConnections << ")";
}

/*
TcpServer::~TcpServer()
{

}
*/

bool TcpServer::Start(void)
{
	bool resp;


	this->server.setMaxPendingConnections(this->maxConnections);
	resp = this->server.listen(this->svrAddr, this->svrPort);
	if (!resp) {
		QString tmpStr;
		tmpStr = "[TcpServer::Start] Server error: " + this->server.errorString();
		Common::AddToLog(tmpStr);
		abort();
	}
	//this->justConnected = new bool[this->maxConnections];
	//qDebug() << "[TcpServer::Start] Max pending connections: " << this->maxConnections;
	Common::AddToLog("[TcpServer::Start] Server started (" + svrAddr.toString() + "," + this->svrPort);
    connect(&server, SIGNAL(newConnection()), this, SLOT(OnClientConnection()) );

	return(resp);
}

bool TcpServer::Stop(void)
{
	this->server.close();
	return(this->server.isListening());
}

void TcpServer::OnClientConnection()
{
	qDebug() << "[TcpServer::Stop] New connection.";

	QTcpSocket * connection  = server.nextPendingConnection();
	if(connection)
	{
		//this->justConnected = true;
		connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(OnClientError(QAbstractSocket::SocketError)) );
		// we assume Server has a slot readyRead()
		connect(connection, SIGNAL(readyRead()), this, SLOT(OnClientData()));
		//we assume Server has a slot disconnected()
		connect(connection, SIGNAL(disconnected()), this, SLOT(OnClientDisconnection()));
	}
}


void TcpServer::OnClientData()
{
	QTcpSocket* connection = qobject_cast<QTcpSocket*>(sender());
	quint64 bufferSize = 2048;
	char buffer[bufferSize];
	quint64 dataRead = 0;

	dataRead = connection->read(buffer, bufferSize);
	buffer[dataRead] = 0;

	//qDebug() << "[WEB] Incoming data[" << dataRead << "]: " << buffer;

	QString value;

	//Check if it's a Flash policy request, only the first time
	//if (this->justConnected == true) {
		value = buffer;
		if (value.contains("<policy-file-request/>")) {
			connection->write(XML_CROSS_DOMAIN);
			qDebug() << "[TcpServer::OnClientData] Sent xml cross domain file";
			//this->justConnected = false;
			return;
		}
		else if ( value.contains("HTTP") ) {	//then its HTTP request

			QString response;

			//Check the data and create response
			DataHandler(value, response);
			HttpResponse httpHeader(response);

			connection->write( httpHeader.GetHeader() );
			connection->write( response.toUtf8().constData() );

			connection->close();
		}
	//}
	//Other requests that are not http requests or posts
	// This may be deleted
	//else {
		else if (value == "CORE") {
			XmlParser xml(buffer, dataRead);
			int action = CEMI_ACTION_WRITE;
			int groupAddr = 0;

			xml.GetValue("cmd", value);
			if (value == "write") action = CEMI_ACTION_WRITE;
			else if (value == "read") action = CEMI_ACTION_READ;

			xml.GetValue("groupAddr", value);
			groupAddr = Common::GroupAddrToInt(value);
			//qDebug() << "groupAddr: " << value;

			xml.GetValue("value", value);

			emit TcpServerData((int)action, groupAddr, value);
		}
	//}
	//this->justConnected = false;
}

void TcpServer::OnClientDisconnection()
{
	qDebug() << "[TcpServer::OnClientDisconnection] Disconnected.";
	QTcpSocket* connection = qobject_cast<QTcpSocket*>(sender());
	connection->close();
	connection->deleteLater();
}


void TcpServer::OnClientError(QAbstractSocket::SocketError)
{
	QTcpSocket* connection = qobject_cast<QTcpSocket*>(sender());
	qDebug() << "[TcpServer::OnClientError] Client error: " << connection->errorString();
	connection->close();
	connection->deleteLater();
}



void TcpServer::DataHandler(QString incomingData, QString & response)
{
	//Calendar data
	if ( incomingData.contains("calendar.cmd") ) {
		CalendarDataHandler(incomingData, response);
	}
	//knx data
	else if (incomingData.contains("knx.cmd")) {
		KnxDataHandler(incomingData, response);
	}
	else if (incomingData.contains("room.data")) {
		RoomDataHandler(incomingData, response);
	}
}

void TcpServer::RoomDataHandler(QString incomingData, QString & response)
{
	int startPos = 0;
	int endPos = 0;

	if (incomingData.contains("GET")) {
		startPos = incomingData.indexOf("?") + 1;	//+1 skip ?
		endPos = incomingData.indexOf("HTTP");
		QString urlVariables = incomingData.mid(startPos, endPos-startPos);
		qDebug() << "[TcpServer::RoomDataHandler] READ: urlVariables: " << urlVariables;
		QStringList args = urlVariables.split('&');

		QString roomId;

		for (int i=0; i<args.length(); i++) {
			if (args[i].contains("roomId")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				roomId = args[i].mid(startPos, endPos);
			}
		}

		KnxDB db;
		if (!db.Connect()) {
			qDebug() << "[TcpServer::KnxDataHandler]: failed to connect to DB";	//if it can't connect to db then exit
			abort();
		}
		QList<QString> strResult;
		//qDebug() << "groupAddr: " << groupAddr << " and to int= " << groupAddr.toInt();
		db.GetRoomAddresses(roomId.toInt(), strResult);
		db.Disconnect();

		response = "<ROOM>";
		for (int i = 0; i<strResult.length(); i++) {
			response += strResult[i];
		}
		response += "</ROOM>";
		qDebug() << response;
	}
}

void TcpServer::KnxDataHandler(QString incomingData, QString & response)
{
	int startPos = 0;
	int endPos = 0;

	if ( incomingData.contains("POST") ) {
		startPos = 0;
		endPos = incomingData.length();
		startPos = incomingData.indexOf("\r\n\r\n") + 1;	//+1 skip ?
		QString urlVariables = incomingData.mid(startPos, endPos-startPos);
		qDebug() << "[TcpServer::KnxDataHandler] WRITE: urlVariables: " << urlVariables;
		QStringList args = urlVariables.split('&');

		QString groupAddr;
		QString value;

		for (int i=0; i<args.length(); i++) {
			if (args[i].contains("groupAddr")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				groupAddr = args[i].mid(startPos, endPos);
				qDebug() << "groupAddr: " << groupAddr;
			}
			else if (args[i].contains("value")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				value = args[i].mid(startPos, endPos);
				value.replace("%20", " ");
				qDebug() << "value: " << value;
			}
		}

		int action = CEMI_ACTION_WRITE;
		emit TcpServerData((int)action, groupAddr.toInt(), value);
		response = "<KNX><DATA groupAddr=\"" + groupAddr + "\" value=\"" + value + "\" /></KNX>";
	}
	else if (incomingData.contains("GET")) {
		startPos = incomingData.indexOf("?") + 1;	//+1 skip ?
		endPos = incomingData.indexOf("HTTP");
		QString urlVariables = incomingData.mid(startPos, endPos-startPos);
		qDebug() << "[TcpServer::KnxDataHandler] READ: urlVariables: " << urlVariables;
		QStringList args = urlVariables.split('&');

		QString groupAddr;
		QString value;

		for (int i=0; i<args.length(); i++) {
			if (args[i].contains("groupAddr")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				groupAddr = args[i].mid(startPos, endPos);
			}
		}

		KnxDB db;
		if (!db.Connect()) {
			qDebug() << "[TcpServer::KnxDataHandler]: failed to connect to DB";	//if it can't connect to db then exit
			abort();
		}
		QString strResult;
		//qDebug() << "groupAddr: " << groupAddr << " and to int= " << groupAddr.toInt();
		db.GetValue(groupAddr.toInt(), strResult);
		db.Disconnect();

		//qDebug() << "[Tcp]: strResult: " + strResult;


		response = "<KNX><DATA groupAddr=\"" + groupAddr + "\" value=\"" + strResult + "\" /></KNX>";
	}
}


void TcpServer::CalendarDataHandler(QString incomingData, QString & response)
{
	int startPos = 0;
	int endPos = incomingData.indexOf("HTTP");

	if ( incomingData.contains("POST") ) {	//app is sending data
		startPos = incomingData.indexOf("\r\n\r\n") + 1;	//+1 skip ?
		QString urlVariables = incomingData.mid(startPos, endPos-startPos);
		qDebug() << "[TcpServer::CalendarDataHandler] vars: " << urlVariables;
		QStringList args = urlVariables.split('&');

		//Create a calendar objet
		Calendar cal("knx","127.0.0.1", "root", "");

		QString action;
		QString eventTime;
		QString eventText;
		QString eventAction;
		QString eventPostAction;

		for (int i=0; i<args.length(); i++) {
			if (args[i].contains("action")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				action = args[i].mid(startPos, endPos);
			}
			else if (args[i].contains("eventTimestamp")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				eventTime = args[i].mid(startPos, endPos);
			}
			else if (args[i].contains("eventText")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				eventText = args[i].mid(startPos, endPos);
			}
			else if (args[i].contains("eventAction")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				eventAction = args[i].mid(startPos, endPos);
			}
			else if (args[i].contains("postEventAction")) {
				startPos = args[i].indexOf('=')+1;
				endPos = args[i].length() - startPos;
				eventPostAction = args[i].mid(startPos, endPos);
			}
		}
		/*
		qDebug() << "action: " << action;
		qDebug() << "eventTimestamp: " << eventTime;
		qDebug() << "eventText: " << eventText;
		qDebug() << "eventAction: " << eventAction;
		qDebug() << "eventPostAction: " << eventPostAction;
		*/

		cal.SetEvent(action, eventTime, eventText, eventAction, EVENT_KEEP, response);

	}
	else if ( incomingData.contains("GET") ) {	//set data

		//the data that are received here have the following format
		// http://serverip:serverport/calendar/filename.xml

		startPos = incomingData.indexOf("calendar/") + 9;	//+1 skip ?
		endPos = incomingData.indexOf(".xml?");

		QString datefile;
		datefile = incomingData.mid(startPos, endPos-startPos);

		qDebug() << "[TcpServer::CalendarDataHandler] vars: " << datefile;

		QString xmlData;

		//Create a calendar objet
		Calendar cal("knx","127.0.0.1", "root", "");
		cal.GetEvent(datefile, xmlData);

		response = "<Calendar></Calendar>\r\n";
	}
}



