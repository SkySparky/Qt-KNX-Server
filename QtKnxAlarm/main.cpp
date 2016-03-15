#include <QtCore/QCoreApplication>
#include <QtCore>
#include <QSettings>
#include "../QtKnxModule/gidt_module.h"
#include "XSocket.h"
#include "pdxalarm.h"

XSocket		* xsocket;
GidtModule	* mod;
PdxAlarm	* alarm;

xport_t LoadXportData(QString &iniName);

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("ISO 8859-7");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);

    QString iniFile = "./pdxalarm.ini";
    if (!Common::FileExists(iniFile)) {
        qDebug() << "[PDXALARM] Error: could not find pdxalarm.ini file!";
    }


    mod = new GidtModule(&a, iniFile);      //create new module
    alarm = new PdxAlarm(iniFile, mod);     //create alarm obj

    QObject::connect(mod, SIGNAL(Output(QString)),alarm, SLOT(Input(QString)) );	//mod -> alarm

    xport_t xportData = LoadXportData(iniFile);     //read ini and get xport conf

    XSocket * xportSock = new XSocket(xportData);	//Create a new xport

    QObject::connect(xportSock, SIGNAL(Output(QByteArray)),alarm, SLOT(AlrmInput(QByteArray)) );            //xport -> alarm
    QObject::connect(alarm, SIGNAL(Output(QString,uint,uint)),xportSock, SLOT(Input(QString,uint,uint)) );	//alarm -> xport

    //Enable module
    mod->Enable();

	return a.exec();
}


xport_t LoadXportData(QString &iniName)
{
	QSettings settings(iniName, QSettings::IniFormat);
	bool ok;

	xport_t xport;
	xport.id = settings.value("Config/id").toString();
	if (xport.id.isEmpty()) {
		qDebug() << "[LoadXportData] couldn't load xport.id";
		exit(-1);
	}
	xport.remoteHost = settings.value("Config/ip_address").toString();
	if (xport.remoteHost.isEmpty()) {
		qDebug() << "[LoadXportData] couldn't load xport.remoteHost";
		exit(-1);
	}
	xport.remotePort = settings.value("Config/port").toUInt(&ok);
	if (!ok) {
		qDebug() << "[LoadXportData] couldn't load xport.remotePort";
		exit(-1);
	}
	return(xport);
}
