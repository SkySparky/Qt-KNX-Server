/*
 * logger.h
 *
 *  Created on: 28 Δεκ 2010
 *      Author: Administrator
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <QtCore>
#include <QObject>
#include <QDir>

class Logger : public QObject {
	Q_OBJECT
private:
	static QMutex m_logMutex;
	QString m_logPath;

public:
	Logger(QString logPath);
	~Logger();
	void AddToLog(QString logText);

public slots:
	void AddLog(QString logText);
};


#endif /* LOGGER_H_ */
