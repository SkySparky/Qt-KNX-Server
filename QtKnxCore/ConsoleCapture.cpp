#include "consoleCapture.h"

ConsoleCapture::ConsoleCapture() 
{
	m_quit = false;
}


void ConsoleCapture::AddLog(QString logMsg)
{
	emit Log("[Console]: " + logMsg);
}


void ConsoleCapture::AllQuit() 
{
	m_quit = true;
}

void ConsoleCapture::ReadLoop(void) {
	QString msg;
	AddLog("Staring console capture.");
	while (!m_quit) {
		std::string tmpStr;
		msg.clear();
		std::cin >> tmpStr;
		msg = QString::fromStdString(tmpStr);
		qDebug() << "msg: " << msg;
		emit ConsoleMsg(msg);
	}
	qDebug() << "[ConsoleCapture]: exit";
}