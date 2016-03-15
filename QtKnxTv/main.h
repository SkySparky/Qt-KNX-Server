/* TV MODULE
 * main.h
 *
 *  Created on: 03 Δεκ 2010
 *      Author: Administrator
 */

#ifndef MAIN_H_
#define MAIN_H_

#include <QtCore>
#include <QCoreApplication>
#include <QSettings>
#include "../QtKnxModule/gidt_module.h"
#include "XSocket.h"

class MainSignalHandler : public QObject {
	Q_OBJECT
	QString GetParam(QString inString, int param, QString separator=",");
public slots:
	void Input(QString data);
};

#endif /* MAIN_H_ */
