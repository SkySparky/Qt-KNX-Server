#include <QtCore/QCoreApplication>
#include "../KnxCommon/common.h"
#include "../QtKnxModule/gidt_module.h"
#include "pstn.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("ISO 8859-7");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);

	QString iniFile = "./module.ini";

    if (!Common::FileExists(iniFile)) {
        qDebug() << "[PSTN] Error: could not found pstn.ini!";
    }

	GidtModule mod(&a, iniFile);

	PSTN pstnMod(iniFile, &mod);

	/*
	QThread pstnThread;
	pstnMod->moveToThread(&pstnThread);
	QObject::connect(&pstnThread, SIGNAL(started()),pstnMod, SLOT(handlePstn()), Qt::DirectConnection);
	pstnThread.start();
	*/


	QObject::connect(&mod, SIGNAL(Output(QString)),&pstnMod, SLOT(Input(QString)) );

	//Enable module
	mod.Enable();

	return a.exec();
}
