/* EMAIL MODULE
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
#include <QMap>

#include "../KnxCommon/common.h"
#include "../QtKnxModule/gidt_module.h"

class MainSignalHandler : public QObject {
    Q_OBJECT
public slots:
	void Input(QString data);
	void OnTimer();
};

#endif /* MAIN_H_ */
