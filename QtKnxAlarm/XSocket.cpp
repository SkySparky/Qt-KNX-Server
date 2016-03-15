#include "XSocket.h"

#define CMD_TIMER_POLLING_TIME 250
#define TCP_RECONNECT_TIMER 5

XSocket::XSocket(const xport_t &target) : m_xport(target), m_timeoutTmr(0)
{
	//copy all data
	if (m_timeoutTmr) {
		m_timeout = new QTimer(this);
		connect(m_timeout, SIGNAL(timeout()), this, SLOT(OnTimeout()));
	}

	m_cmdTimer = new QTimer(this);
	connect(m_cmdTimer, SIGNAL(timeout()), this, SLOT(OnCmdTimer()));
	m_cmdTimer->start(CMD_TIMER_POLLING_TIME);
	m_reconnectTimer = 0;

	connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(OnClientError(QAbstractSocket::SocketError)) );
	connect(&m_socket, SIGNAL(readyRead()), this, SLOT(OnClientData()));

	if (!Connect() ) {
		qDebug() << "Failed to connect. Will retry in " << QString::number(TCP_RECONNECT_TIMER);
	}
}


XSocket::~XSocket()
{
	//if (m_socket.isOpen()) {
		Disconnect();
	//}
}

bool XSocket::Connect()
{
	bool resp = false;

	m_socket.connectToHost(m_xport.remoteHost, m_xport.remotePort);
	if (m_socket.waitForConnected(5000)) {
	     qDebug("[XSocket::Connected]");
	     resp = true;
	}
	else {
		m_socket.close();
	}
	return(resp);
}

bool XSocket::Disconnect(void)
{
	bool resp = false;
	m_socket.disconnectFromHost();
	if (m_socket.state() == QAbstractSocket::UnconnectedState || m_socket.waitForDisconnected(3000)) {
		qDebug("[XSocket::Disconnected]");
		m_socket.close();
	    resp = true;
	}
	return(resp);
}


void XSocket::OnClientData()
{
	//m_socket.waitForReadyRead(100);
	QByteArray buffer = m_socket.readAll();

	//QString inBuffer;
	//inBuffer.append(buffer.constData());
	emit Output(buffer);
}

void XSocket::OnClientDisconnection()
{
	qDebug() << "[XSocket::OnClientDisconnection] Disconnected.";
	QTcpSocket* connection = qobject_cast<QTcpSocket*>(sender());
	connection->close();
	connection->deleteLater();
}


void XSocket::OnClientError(QAbstractSocket::SocketError)
{
	QTcpSocket* connection = qobject_cast<QTcpSocket*>(sender());
	qDebug() << "[XSocket::OnClientError] Client error: " << connection->errorString();
	connection->close();
	connection->deleteLater();
}

void XSocket::OnTimeout()
{
	Disconnect();
	m_timeout->stop();
}

void XSocket::Input(QString data, uint preDelay, uint postDelay)
{
	cmd_t tmpCmd;
	tmpCmd.cmd = data;
	tmpCmd.postDelay = postDelay;
	tmpCmd.preDelay = preDelay;
	tmpCmd.sent = false;

	m_commandList << tmpCmd;
}

void XSocket::OnCmdTimer()
{
	//qDebug() << "XSocket::OnCmdTimer: " << QString::number(m_reconnectTimer);
	//Get top command
	if ((m_reconnectTimer++) >= TCP_RECONNECT_TIMER) {
		m_reconnectTimer = 0;
		if (m_socket.state() != QAbstractSocket::ConnectedState) {
			qDebug() << "Reconnecting to xport";
			Connect();
		}
	}

	if (!m_commandList.isEmpty()) {
		//predelay
		if (!m_commandList.first().sent) {
			if (m_commandList.first().preDelay > 0) {
				m_commandList.first().preDelay -= CMD_TIMER_POLLING_TIME;
				//qDebug() << "[XSocket::OnCmdTimer] " << QString::number(m_commandList.first().preDelay);
			}
			else {
				if (m_timeoutTmr) {
					m_timeout->stop();	//stop to refresh
				}

				//Send Command
				QByteArray bytes;
				bool resp = m_socket.isOpen();

				if (!resp)
					resp = Connect();

				if (resp) {
					bytes = m_commandList.first().cmd.toLatin1();

					if (bytes.length() > 0) {
						qDebug() << "Sending: " << m_commandList.first().cmd.toLatin1();
						m_socket.write(bytes);
						m_commandList.first().sent = true;
					}
					//Check model
					if (m_timeoutTmr) {
						m_timeout->start(m_commandList.first().preDelay + m_commandList.first().postDelay + m_timeoutTmr);
					}
				}
			}
		}
		//postdelay
		else {
			if (m_commandList.first().postDelay > 0) {
				m_commandList.first().postDelay -= CMD_TIMER_POLLING_TIME;
			}
			else {
				if (m_timeoutTmr) {
					m_timeout->stop();
					m_timeout->start(m_timeoutTmr);
				}
				//remove command
				qDebug() << "Removing: " << m_commandList.first().cmd.toLatin1();
				m_commandList.removeAt(0);
			}
		}
	}
}
