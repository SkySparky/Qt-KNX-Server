/*
 * logger.cpp
 *
 *  Created on: 28 Δεκ 2010
 *      Author: Administrator
 */
#include "logger.h"

QMutex Logger::m_logMutex;

Logger::Logger(QString logPath) : m_logPath(logPath)
{
	//Check if path exists
	QDir logpath(logPath);
	if (!logpath.exists()) {
		//The path doesn't exists
		qDebug() << "[Logger] The log path (" << m_logPath << ") doesn't exist";
		exit(-1);
	}
}

Logger::~Logger() {};


void Logger::AddToLog(QString logText)
{
	AddLog(logText);

}

void Logger::AddLog(QString logText)
{
	m_logMutex.lock();
	QDate nowDate = QDate::currentDate();
	qDebug() << "[Logger]: " + logText;

	QFile file(m_logPath + "/" + 
		QString::number(nowDate.year()) + 
		QString::number(nowDate.month()) + 
		QString::number(nowDate.day()) + 
		".txt" );
	if ( file.open(QIODevice::Append | QIODevice::Text) == true) {
		QTextStream out(&file);
		QString msg = QTime::currentTime().toString() + ": " + logText + "\n";
		out << msg;
		out.flush();
		file.close();
	}
	else {
		qDebug() << "[LOG] Failed to add entry.";
	}
	m_logMutex.unlock();
}
