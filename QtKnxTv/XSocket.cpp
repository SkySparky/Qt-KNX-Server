#include "XSocket.h"

#define CMD_TIMER_POLLING_TIME 250

XSocket::XSocket(const xport_t &tvSet)
{
	//copy all data
	m_xport.id = tvSet.id;
	m_xport.remoteHost = tvSet.remoteHost;
	m_xport.remotePort = tvSet.remotePort;
	m_xport.iniFile = tvSet.iniFile;

	//Read ini file
	QSettings settings(m_xport.iniFile, QSettings::IniFormat);
	//Load supported commands
	settings.beginGroup("Commands");
	QStringList keys = settings.allKeys();	//get all keys from Commads

	for (int i=0; i<keys.length(); i++) {
		m_commands[keys[i]] = settings.value(keys[i]).toString();	//create map with keys and values
		//qDebug() << "cmd: " << keys[i] << ", " << settings.value(keys[i]).toString();
	}

	m_timeout = new QTimer(this);
	connect(m_timeout, SIGNAL(timeout()), this, SLOT(OnTimeout()));

	m_cmdTimer = new QTimer(this);
	connect(m_cmdTimer, SIGNAL(timeout()), this, SLOT(OnCmdTimer()));
	m_cmdTimer->start(CMD_TIMER_POLLING_TIME);


	connect(&m_socket, SIGNAL(error(QAbstractSocket::SocketError)),this, SLOT(OnClientError(QAbstractSocket::SocketError)) );
	connect(&m_socket, SIGNAL(readyRead()), this, SLOT(OnClientData()));
	//connect(&m_socket, SIGNAL(disconnected()), this, SLOT(OnClientDisconnection()));
}


XSocket::~XSocket()
{
	if (m_socket.isOpen()) {
		Disconnect();
	}
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
	QByteArray buffer = m_socket.readAll();

	m_inBuffer.append(buffer.constData());

	if (m_xport.iniFile.contains("lg.ini")) {
		if (m_inBuffer.contains(QChar('x'))) {
			if (m_inBuffer.contains("OK")) {
				qDebug() << "[XSocket::OnClientData] data ok: " << m_inBuffer;
			}
			m_inBuffer.clear();
		}
	}

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

quint64 XSocket::SendData(QString &cmd, QString &data, uint preDelay, uint postDelay)
{
	QString outData;

	if (m_xport.iniFile.contains("lg.ini")) {
		outData = m_commands[cmd];
		qDebug() << "m_commands[cmd]: " << m_commands[cmd] << ", cmd=" << cmd;
		outData.replace("%id", m_xport.id);
		outData.replace("%d", data);
		outData.replace("%cr", QChar(13));
		cmd_t tmpCmd;
		tmpCmd.cmd = outData;
		tmpCmd.postDelay = postDelay;
		tmpCmd.preDelay = preDelay;
		tmpCmd.sent = false;

		m_commandList << tmpCmd;
	}
	return(m_commandList.length());
}

void XSocket::OnCmdTimer()
{
	//qDebug() << "XSocket::OnCmdTimer";
	//Get top command
	if (!m_commandList.isEmpty()) {
		//predelay
		if (!m_commandList.first().sent) {
			if (m_commandList.first().preDelay > 0) {
				m_commandList.first().preDelay -= CMD_TIMER_POLLING_TIME;
				//qDebug() << "[XSocket::OnCmdTimer] " << QString::number(m_commandList.first().preDelay);
			}
			else {
				m_timeout->stop();	//stop to refresh

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
					m_timeout->start(m_commandList.first().preDelay + m_commandList.first().postDelay + 2000);
				}
			}
		}
		//postdelay
		else {
			if (m_commandList.first().postDelay > 0) {
				m_commandList.first().postDelay -= CMD_TIMER_POLLING_TIME;
			}
			else {
				m_timeout->stop();
				//remove command
				qDebug() << "Removing: " << m_commandList.first().cmd.toLatin1();
				m_commandList.removeAt(0);
				m_timeout->start(5000);
			}
		}
	}
}
