#include "main.h"

//GSM MAIN

GidtModule * mod;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	GidtModule mod(&a, "./module.ini");

	//Load config data
	QSettings settings("./module.ini", QSettings::IniFormat);
	QString comPort = settings.value("Config/com_port").toString();
	QStringList smsTel;
	
	int size = settings.beginReadArray("Config");
	qDebug() << "size: " << size;
	for (int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		smsTel << settings.value("valid_tel").toString();
	}


	Gsm gsm(&mod, comPort, smsTel);
	QObject::connect(&mod, SIGNAL(Output(QString)), &gsm, SLOT(Input(QString)) );

	//Enable module
	mod.Enable();
    gsm.Start();

    return a.exec();
}

