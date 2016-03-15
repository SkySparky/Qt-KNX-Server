/* TV MODULE
 * main.cpp
 *
 *  Created on: 03 Δεκ 2010
 *      Author: Administrator
 */

#include "main.h"

#define PARAM_TV_ID			4
#define PARAM_TV_CMD		5
#define PARAM_TV_DATA		6
#define PARAM_TV_PREDELAY	7
#define PARAM_TV_POSTDELAY	8

void GetXportTVs(QString &iniName, QList<xport_t> &list);

QMap<QString, XSocket*> xsockets;
GidtModule * mod;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QList<xport_t> xportList;
    QString iniFile = "./module.ini";

	mod = new GidtModule(&a, iniFile);


    GetXportTVs(iniFile, xportList);	//read ini and get tv sets
    for (int i=0; i<xportList.length(); i++) {
    	XSocket * tvSocket = new XSocket(xportList.at(i));	//Create a new xsocket
    	xsockets[xportList.at(i).id] = tvSocket;			//Keep the socket to a map list
    }
    qDebug() << "All sockets created";

    MainSignalHandler slotHandler;	//create slot handler
	//Send data to bus
	//QObject::connect(mod,  SIGNAL(OnData(QString)),&slotHandler, SLOT(OnTvCommand(QString)) );
	QObject::connect(mod, SIGNAL(Output(QString)),&slotHandler, SLOT(Input(QString)) );
	
	//Enable module
	mod->Enable();

    return a.exec();
}

QString MainSignalHandler::GetParam(QString inString, int param, QString separator)
{
	QString strResult;

	QT_TRY {
		QStringList params = inString.split(separator);
		//QString retString = params.at(param+1);
		if (params.isEmpty() == false) {
			//qDebug() << "inString: " << inString;
			strResult = params.at(param-1);
			QStringList splitParms = strResult.split("=");
			if (splitParms.count() == 2) {
				//QString dbParamName = splitParms[0];	//get param name
				strResult = splitParms[1];		//get param value
			}
		}
	}
	QT_CATCH(...) {
		mod->Log("KnxTV/MainSignalHandler::GetParam error with: " + inString);
	}
	return(strResult);
}

void MainSignalHandler::Input(QString data)
{
	bool ok;
	//WRITE,DB,TV,PARAM_TV_ID,PARAM_TV_CMD,PARAM_TV_DATA,PARAM_TV_PREDELAY,PARAM_TV_POSTDELAY
	xsockets[GetParam(data, PARAM_TV_ID)]->SendData(GetParam(data,PARAM_TV_CMD),
						GetParam(data,PARAM_TV_DATA), 
						GetParam(data,PARAM_TV_PREDELAY).toInt(&ok), 
						GetParam(data,PARAM_TV_POSTDELAY).toInt(&ok)
						);
}

void GetXportTVs(QString &iniName, QList<xport_t> &list)
{
	QSettings settings(iniName, QSettings::IniFormat);
	int size = settings.beginReadArray("Config");
	bool ok;
	for (int i = 0; i < size; ++i) {
		settings.setArrayIndex(i);
		xport_t xport;
		xport.id = settings.value("id").toString();
		xport.remoteHost = settings.value("ip_address").toString();
		xport.remotePort = settings.value("port").toUInt(&ok);
		xport.iniFile = settings.value("ini").toString();

		//qDebug() << "ip: " << xport.remoteHost << ", port: " << QString::number(xport.remotePort);
		list << xport;
	}
	settings.endArray();
}
