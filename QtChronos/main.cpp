#include <QtCore/QCoreApplication>
#include <QDebug>
#include "chronos.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	Chronos chronosAP("");

	QThread chronosThread;
	chronosAP.moveToThread(&chronosThread);
	QObject::connect(&chronosThread, SIGNAL(started()),&chronosAP, SLOT(StartAP()), Qt::DirectConnection);
	chronosThread.start();


	return a.exec();
}
