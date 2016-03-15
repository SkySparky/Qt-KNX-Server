#include "main.h"
#include <QtCore/QCoreApplication>

//Conf * cfg;
KnxDB * db;
KnxGateway * gw[10];
//TcpServer  * webServer;
ModuleManager * modManager;
Logger * logger;
knxCore_t glb_core;
UdpServer * udpServer;

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	QTextCodec *codec = QTextCodec::codecForName("ISO 8859-7");
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForLocale(codec);

	bool ok;
	QString tmpStr;

	QString iniFile = "./GiDT.ini";

	qDebug() << "Main Thread id: " << QThread::currentThreadId();

	MainSignalHandler slotHandler;


	QObject::connect(&slotHandler, SIGNAL(MainQuit()), &a, SLOT(quit()),Qt::DirectConnection);


	/***************** CONFIGURATION *****************/
	//read config file
	QSettings settings(iniFile, QSettings::IniFormat);
	glb_core.inbox = settings.value("Folders/inbox").toString();
	glb_core.hbbox = settings.value("Folders/hbbox").toString();
	glb_core.logbox = settings.value("Folders/logbox").toString();

	logger = new Logger(glb_core.logbox);

	logger->AddToLog("Program started.");

    //QSqlDatabase maindbHandler = QSqlDatabase::addDatabase("QSQLITE");	//create db object

	/***************** MODULE MANAGER *****************/

	//Start module manager
	modManager = new ModuleManager(&a, iniFile);
	QObject::connect(modManager, SIGNAL(Log(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);
	QObject::connect(modManager, SIGNAL(Output(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);

	/***************** DATABASE *****************/
	//Connect to MySQL database
	glb_core.dbName = settings.value("Database/dbName").toString();
	glb_core.dbServer = settings.value("Database/dbServer").toString();
	glb_core.dbUser = settings.value("Database/dbUser").toString();
	glb_core.dbPassword = settings.value("Database/dbPassword").toString();

	db = new KnxDB(glb_core.dbUser, glb_core.dbPassword, glb_core.dbName, glb_core.dbServer);
	QObject::connect(modManager, SIGNAL(Output(QString)), db, SLOT(Input(QString)), Qt::DirectConnection);		//MOD -> DB
	QObject::connect(db, SIGNAL(OutputMod(QString)),modManager, SLOT(Input(QString)), Qt::DirectConnection);	//DB -> MOD
	QObject::connect(db, SIGNAL(Log(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);
	if (!db->Connect()) {
		qDebug() << "WTF?!?";	//if it can't connect to db then exit
		abort();
	}
	

    /***************** KNX/IP GATEWAYS *****************/
    //Create a new knx/ip client
    int size = settings.beginReadArray("KnxGateways");
    qDebug() << "Found " << size << " gateways.";
    if (size > 0) {
        for (int i = 0; i < size; ++i) {
            settings.setArrayIndex(i);
            qDebug() << "KnxGateways ini[" << i << "]: " << settings.value("iniFile").toString();
            gw[i] = new KnxGateway(settings.value("iniFile").toString());
        }
        settings.endArray();
    }
    //gw = new KnxGateway(settings.value("KnxGateways/iniFile").toString());
    //Use only first gateway
    QObject::connect(gw[0], SIGNAL(Output(QString)), db, SLOT(Input(QString)),Qt::DirectConnection);		//GW -> DB
    QObject::connect(db, SIGNAL(OutputKnx(QString)), gw[0], SLOT(Input(QString)), Qt::DirectConnection);	//DB -> GW
    QObject::connect(gw[0], SIGNAL(Log(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);
    QObject::connect(&slotHandler, SIGNAL(AllQuit()), gw[0], SLOT(AllQuit()),Qt::DirectConnection);


//	QThread gatewayThread;
//	gw[0]->moveToThread(&gatewayThread);
//	QObject::connect(&gatewayThread, SIGNAL(started()),gw[0], SLOT(UdpThread()), Qt::DirectConnection);
//	gatewayThread.start();


//	/***************** UDP SERVER *****************/
//	QString udpServerIp = settings.value("UdpServer/listenIp").toString();
//	quint16 udpServerPort = settings.value("UdpServer/listenPort").toInt();

//	udpServer = new UdpServer(udpServerIp, udpServerPort);
//	QObject::connect(udpServer, SIGNAL(Output(QString)), db, SLOT(Input(QString)), Qt::DirectConnection);		//UDP -> DB
//	QObject::connect(db, SIGNAL(OutputUdp(QString)), udpServer, SLOT(Input(QString)), Qt::DirectConnection);	//UDP <- DB
//	QObject::connect(udpServer, SIGNAL(Log(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);
//	QObject::connect(&slotHandler, SIGNAL(AllQuit()), udpServer, SLOT(AllQuit()),Qt::DirectConnection);
//	//QObject::connect(udpServer, SIGNAL(Output(QString, QString)), modManager, SLOT(Input(QString)), Qt::DirectConnection);


//	QThread udpServerThread;
//	udpServer->moveToThread(&udpServerThread);
//	QObject::connect(&udpServerThread, SIGNAL(started()),udpServer, SLOT(OnUdpData()), Qt::DirectConnection);
//	udpServerThread.start();







//	/***************** CONSOLE *****************/

    ConsoleCapture * console = new ConsoleCapture();
    QObject::connect(console, SIGNAL(Log(QString)), logger, SLOT(AddLog(QString)), Qt::DirectConnection);
    QObject::connect(&slotHandler, SIGNAL(AllQuit()), console, SLOT(AllQuit()),Qt::DirectConnection);
    QObject::connect(console, SIGNAL(ConsoleMsg(QString)), &slotHandler, SLOT(ConsoleMsg(QString)),Qt::DirectConnection);

    QThread captureThread;
    console->moveToThread(&captureThread);
    QObject::connect(&captureThread, SIGNAL(started()),console, SLOT(ReadLoop()), Qt::DirectConnection);
    // go!
    captureThread.start();

    //Start ModuleManager
    if (modManager->Begin() < 0) {
        logger->AddToLog("Could not start Module Manager.");
        return(-1);
    }
    QThread modThread;

    modManager->moveToThread(&modThread);
    QObject::connect(&modThread, SIGNAL(started()),modManager, SLOT(ManagerThread()), Qt::DirectConnection);
    modThread.start();

	qDebug() << "[Main] Functioning with timestamp: " << QDateTime::currentDateTime().toTime_t();
	//QTimer::singleShot(0, console, SLOT(ReadLoop()));
	
	return a.exec();
}


void MainSignalHandler::ConsoleMsg(QString msg)
{
	qDebug() << "[MainSignalHandler]: cmd=" << msg;
	if (msg=="q") {
		emit AllQuit();
		QTimer::singleShot(2000, this, SLOT(TimerMainQuit()));
	}
}

/*
void MainSignalHandler::ExecuteDB(QString cmd, QString param)
{
	db->ProcessCommand(cmd, 1, param, 0);
}

void MainSignalHandler::ModuleAlert(QString targetModule, QString moduleMsg)
{
	if (moduleMsg.length() > 1) {
		QDir modulePath;
		if (targetModule == "BUS") {
			modulePath = CorePath;
		}
		else if (targetModule == "SMS") {
			modulePath = SmsPath;
		}
		else if (targetModule == "EMAIL") {
			modulePath = EmailPath;
		}
		else if (targetModule == "ALARM") {
			modulePath = AlarmPath;
		}
		else if (targetModule == "TV") {
			modulePath = TvPath;
		}
		QFile file(CorePath + "/" + QUuid::createUuid ());
		if ( file.open(QIODevice::WriteOnly | QIODevice::Text) == true) {
			 QTextStream out(&file);
			 out << moduleMsg << "/r/n";
			 out.flush();
			 file.close();
		}
		else {
			Common::AddToLog("[MainSignalHandler::ModuleAlert] Failed to add entry(" +
					targetModule + "," + moduleMsg);
		}
	}
}

// Passes the command to the knxdb object
void MainSignalHandler::KnxDataHandler(int action, int groupAddr, QString data)
{
	//Search in DB for actions to do and send the command
	//qDebug() << "[main] found file ";
	unsigned char cdata[256];

	if (gw->IsConnected()) {
		size_t dataLen = Common::StrValueToBytes(data, cdata);
		qDebug() << "[MAIN]: dataLen: " << dataLen;
		for (size_t i = 0; i<dataLen; i++) qDebug() << "data[" << i << "]: " << cdata[i];
		gw->Send((en_cemiAction)action, groupAddr, cdata, dataLen);
	}
}

void MainSignalHandler::WebServerConnection()
{
	qDebug() << "[Main] new tcp connection.";
}

*/
