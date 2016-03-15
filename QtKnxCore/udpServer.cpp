#include "udpServer.h"


#define UDP_BUFFER			1600
#define UDP_WAIT_TIME_MSEC	5000

UdpServer::UdpServer(QString & localIp, quint16 port)
{
	m_localIp = localIp;
	m_port = port;
	m_state = UDP_STATE_DISCONNECTED;
}

void UdpServer::Input(QString data)
{
	QByteArray datagram;
	datagram.append(data);

	QUdpSocket broadSocket;
	QUdpSocket clientSocket;

	broadSocket.writeDatagram(datagram.data(), datagram.size(),
		QHostAddress::Broadcast, 8989);


	qDebug() << "[UdpServer::Input]";

	QMapIterator<QString, tp_clients> i(m_udpClients);

	uint now = QDateTime::currentDateTime().toTime_t();
	uint previous;

	while (i.hasNext()){
		i.next();
		previous = i.value().lastTime;
		if ((now - previous) < 10) {
			qDebug() << "[UdpServer::Input] updating " << i.key() << "," << i.value().lastTime << "," << i.value().port;
			clientSocket.writeDatagram(datagram.data(), datagram.size(),QHostAddress(i.key()), i.value().port);
		}
		else {
			qDebug() << "[UdpServer::Input] removing " << i.key() << "," << QString::number(now) << "," << QString::number(previous);
			m_udpClients.remove(i.key());
		}
	}
	
}

void UdpServer::OnUdpData(void)
{
	QUdpSocket socket;
	qint64 dataLen = 0;
	quint16 waitTimeMs = UDP_WAIT_TIME_MSEC;
	QHostAddress sender;
	quint16 senderPort;
	QByteArray respOK("OK\n");

	//Create local socket
	m_state = UDP_STATE_CONNECTING;
	if (!socket.bind(QHostAddress(m_localIp), m_port) ) {//
	//if (!socket.bind(QHostAddress::Any, m_port) ) {
		qDebug() << "[OnUdpData::Connect] Failed to bind to m_localIp: " << m_localIp << ", m_port:" << m_port;
		exit(-1);
	}
	else
		m_state = UDP_STATE_CONNECTED;

	while (m_state == UDP_STATE_CONNECTED) {
		if (!socket.waitForReadyRead(waitTimeMs) ) {
			if ( socket.error() != QAbstractSocket::SocketTimeoutError) {
				//qDebug() << "[KnxGateway::UdpThread] Error: " << socket.errorString() << "," << socket.error();
				QString msg = "Socket error: '";
				msg.append(socket.error());
				msg.append("'. Aborting");
				AddLog("OnUdpData]: " + msg);
				exit(0);
			}
		}
		while( socket.hasPendingDatagrams() )
		{
			char datagram[UDP_BUFFER];
			dataLen = socket.readDatagram(datagram, UDP_BUFFER, &sender, &senderPort);
			datagram[dataLen] = 0;
			QString tmpData(datagram);
			qDebug() << "[UdpServer::OnUdpData] incoming data: " << tmpData;

			//check if client is still connected

			if (m_udpClients.contains(sender.toString())) {
				m_udpClients[sender.toString()].lastTime = QDateTime::currentDateTime().toTime_t();	//update alive timer
				qDebug() << "[UdpServer::OnUdpData] updating " << sender;
			}
			else {
				tp_clients tmpClient;
				tmpClient.port = senderPort;
				tmpClient.lastTime = QDateTime::currentDateTime().toTime_t();
				m_udpClients[sender.toString()] = tmpClient;
				qDebug() << "[UdpServer::OnUdpData] add client " << sender;
			}

			//forward the message to destination
			emit Output(tmpData);
		}
	}
	socket.deleteLater();
	qDebug() << "[UdpServer::OnUdpData] Thread exiting...";
}


QString UdpServer::GetParam(QString &inString, int param)
{
	QString strResult;

	QT_TRY {
		QStringList params = inString.split(",");
		//QString retString = params.at(param+1);
		if (param <= params.length()) {
			//qDebug() << "inString: " << inString;
			strResult = params.at(param-1);
		}
	}
	QT_CATCH(...) {
		Log("GetParam error with: " + inString);
	}
	return(strResult);
}


void UdpServer::AllQuit(void)
{
	m_state = UDP_STATE_DISCONNECTING;
}

void UdpServer::AddLog(QString logMsg)
{
	emit Log("[UdpServer::" + logMsg);
}