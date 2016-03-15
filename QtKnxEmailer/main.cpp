/* EMAIL MODULE
 * main.cpp
 *
 *  Created on: 03 Äåê 2010
 *      Author: Administrator
 */

#include "main.h"

typedef struct {
	QString to;
	QString subj;
	QString body;
	QString attachment;
	bool	sent;
} email_t;

GidtModule			*mod;
QString 			glb_watchFolder;
QTimer * 			glb_emailTimer;
QList<email_t> 		glb_emailList;
QString 			glb_emailerUrl;
QMap<QString, QString>	glb_charset;

void LoadConf(void);
bool SendMail(QString &to, QString &subject, QString &body);
void TestUnicode();
void LoadCharset(QString fileName);

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	qDebug() << "QtKnxEmailer started...";
	//TestUnicode();
    /*
    QStringList args = a.arguments();
    for (int i=0; i<args.count(); i++) {
    	if (args[i] == "-outbox") {
    		qDebug() << "outbox: " << args[i+1];
    	}
    	else if (args[i] == "-hbbox") {
    		qDebug() << "hbbox: " << args[i+1];
    	}
    }
    */

    MainSignalHandler slotHandler;	//create slot handler

    QString fname = "./emailer.ini";
    if (!Common::FileExists(fname)) {
        qDebug() << "[Emailer] Error: could not find ./emailer.ini file!";
        return 0;
    }

    mod = new GidtModule(&a, "./emailer.ini");

    QObject::connect(mod, SIGNAL(Output(QString)), &slotHandler, SLOT(Input(QString)) );

    //Set up timer
    glb_emailTimer = new QTimer();
    glb_emailTimer->start(1000);
	QObject::connect(glb_emailTimer, SIGNAL(timeout()), &slotHandler, SLOT(OnTimer()) );

	//Enable module
	mod->Enable();

	return a.exec();
}

bool SendMail(email_t &mail)
{
	bool resp = false;
#define IS_WINDOWS 1

	QString prg_uuencode = "uuencode";
	QString prg_sendmail = "sendmail";
	if (IS_WINDOWS) {
		prg_uuencode.append(".exe");
		prg_sendmail.append(".exe");
	}

	//Create header
	QFile header("./header.txt");
	if (!header.open(QIODevice::WriteOnly | QIODevice::Text)) {
		//qDebug() << "[SendMail] Could not create file: " << header.fileName();
	}
	else {
		QTextStream w_stream(&header);

		//put header
		w_stream << "To: " + mail.to + "\n";
		w_stream << "From: GiDT Homeserver\n";
		w_stream << "Subject: " + mail.subj + "\n\n";
		w_stream << mail.body + "\n";

		//add atachment
		if (!mail.attachment.isEmpty()) {
			QProcess uuencode;
			//qDebug() << "1";
			uuencode.start("uuencode.exe", QStringList() << mail.attachment << "./attachment.txt");
			if (!uuencode.waitForStarted())
				return false;

			//qDebug() << "2";

			if (!uuencode.waitForFinished())
				return false;
			//qDebug() << "3";

			QByteArray result = uuencode.readAll();
			if (result.contains("Result encoded")) {
				//add attachment to header
				QFile attachment("attachment.txt");
				if (!attachment.open(QIODevice::ReadOnly | QIODevice::Text)) {
					qDebug() << "[SendMail] Could not create file: " << attachment.fileName();
				}
				else {
					//qDebug() << "4";
					QTextStream r_stream(&attachment);
					w_stream << r_stream.readAll();
					attachment.close();
				}
			}

			w_stream.flush();
		}

		header.close();

		QProcess sendmail;
		//qDebug() << "5";
		sendmail.start("sendmail.exe", QStringList() << header.fileName());
		qDebug() << "header.fileName()= " << header.fileName();
		 if (!sendmail.waitForStarted())
			 return false;
			//qDebug() << "7";

		 if (!sendmail.waitForFinished())
			 return false;
			//qDebug() << "8";

		 QByteArray result = sendmail.readAll();
	}

	return(resp);
}

void QueueMail(QString data)
{

}


void MainSignalHandler::Input(QString data)
{
	qDebug() << data;
	//create new mail
	email_t tmpMail;
    if ((Common::GetParam(data, Common::PARAM_CMD) == "WRITE") && (Common::GetParam(data, Common::PARAM_DEST) == "EMAIL")){

        tmpMail.to = Common::GetParam(data,Common::PARAM_DATA_START);
        tmpMail.subj = Common::GetParam(data,Common::PARAM_DATA_START+1);
        tmpMail.body = Common::GetParam(data,Common::PARAM_DATA_START+2);
        QString tmpStr = Common::GetParam(data,Common::PARAM_DATA_START+3);
        if (tmpStr.length() > 1) tmpMail.attachment = Common::GetParam(data,Common::PARAM_DATA_START+3);
		else tmpMail.attachment.clear();

		tmpMail.sent = false;

		//add it to list
		glb_emailList << tmpMail;

		qDebug() << "[MainSignalHandler::OnEmailCommand] to=" << tmpMail.to << ", subject=" << tmpMail.subj << ", body=" << tmpMail.body;
	}
}


void MainSignalHandler::OnTimer()
{
	glb_emailTimer->stop();

	if (!glb_emailList.isEmpty()) {
		if (!glb_emailList.first().sent) {
			if ( SendMail(glb_emailList.first()) ) {
				//delete from list
				glb_emailList.first().sent = true;
				glb_emailList.removeAt(0);
			}
			else {
				glb_emailList.first().sent = false;
				glb_emailList.removeAt(0);
			}
		}
	}

	glb_emailTimer->start();
}

void LoadCharset(QString fileName)
{
	//Open file
	QFile file(fileName);
	if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
		qDebug() << "[Watcher] Could not open charset file: " << fileName;
		exit(0);
	}
	else {
		QTextStream stream(&file);
		QString line;
		line = stream.readLine();
		while (!line.isNull()) {
			QStringList tmpList = line.split(",");
			glb_charset[tmpList.at(2)] = tmpList.at(3);		//Change column for charset hereS
			line = stream.readLine();
			//qDebug() << tmpList.at(1) << "," << tmpList.at(2);
		};
	}
	qDebug() << "Loaded charset: " << fileName;
}


void TestUnicode()
{
	//QString text = "ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÓÔÕÖ×ØÙáâãäåæçèéêëìíîïðñóôõö÷øù¢¸¹º¼¾¿ÚÛÜÝÞßüýþúûÀà";
	QString text = "ÁÂÃÄÅÆÇÈÉÊËÌÍÎÏÐÑÓÔÕÖ×ØÙáâãäåæçèéêëìíîïðñóôõö÷øù¢¸¹º¼¾¿ÚÛÜÝÞßüýþúûÀà";
	for (int i=0; i<text.length(); i++) {
		qDebug() << i << ", " << text.mid(i, 1) << ": " << text.mid(i, 1).toUtf8().toHex();
	}
}
