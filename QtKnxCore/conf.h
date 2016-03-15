/*
 * conf.h
 *
 *  Created on: 22 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef CONF_H_
#define CONF_H_

#include <QtCore>
#include <QDebug>
#include <QFile>
#include <QSettings>


class Conf {
private:
	QSettings * settings;
	QString m_iniFile;
	void CreateDefault();
	void	AddLog(QString logMsg);
public:
	Conf(QString iniFile);
	~Conf();
	QVariant GetParameter(QString parameter);
	void SetParameter(QString parameter, QVariant value);

signals:
	void Log(QString logString);
};

#endif /* CONF_H_ */
