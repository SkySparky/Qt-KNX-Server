/*
 * conf.cpp
 *
 *  Created on: 22 Ιουλ 2010
 *      Author: Administrator
 */
#include "conf.h"


/*
 * Create default configuration reader writer
 * Constructor
 * If conf file doesn't exists then it creates it
 */
Conf::Conf(QString iniFile) : m_iniFile(iniFile)
{

	settings = new QSettings(m_iniFile, QSettings::IniFormat);
	if (!QFile::exists(settings->fileName())) {
		AddLog("[Conf] Creating new conf file");
		CreateDefault();
	}
	else {
		AddLog("[Conf] Reading from existing file.");
	}
}

/*
 * Destroy object and free any memory used
 */
Conf::~Conf()
{
	delete settings;
}

void Conf::AddLog(QString logMsg)
{
	emit Log("[UdpServer]: " + logMsg);
}

QVariant Conf::GetParameter(QString parameter)
{
	//qDebug() << "[LOG dbg] " << settings->value(parameter).toString();
	return(settings->value(parameter));
}

void Conf::SetParameter(QString parameter, QVariant value)
{
	settings->setValue(parameter, value);
}

void Conf::CreateDefault()
{
	settings->beginGroup("Folders");
	settings->setValue("core_folder","./_inbox");
	settings->setValue("heartbeat_folder","./_heartbeat");
	settings->setValue("log_folder","./_logs");
	settings->endGroup();

	settings->beginGroup("MySQL");
	settings->setValue("mysql_db","testdb");
	settings->setValue("mysql_ip","127.0.0.1");
	settings->setValue("mysql_user","knxserver");
	settings->setValue("mysql_pass","warwick");
	settings->endGroup();

	settings->beginGroup("Gateway");
	settings->setValue("home_server_udp_port","3658");
	settings->setValue("knx_ip","*");
	settings->setValue("last_channel","0");
	settings->setValue("send_time_date","no");
	settings->setValue("date_time_period_min","0");
	settings->setValue("date_address","0");
	settings->setValue("time_address","0");
	settings->endGroup();

	settings->beginGroup("Web");
	settings->setValue("listen_ip","127.0.0.1");
	settings->setValue("listen_port","7700");
	settings->setValue("max_connections","3");
	settings->endGroup();

	settings->beginGroup("rcon");
	settings->setValue("rcon_port","7700");
	settings->endGroup();

	settings->beginGroup("Visualization");
	settings->setValue("vis_port","7701");
	settings->endGroup();

	settings->beginGroup("Calendar");
	settings->setValue("web_folder", "C:/wamp/www/calendar");
	settings->endGroup();


	settings->beginGroup("Modules");
	settings->setValue("hb_dir", "C:/Documents and Settings/Administrator/workspace/knxip/_heartbeat");
	settings->setValue("hb_polling_ms", "1000");
	settings->setValue("ps_polling_sec", "5");
	settings->setValue("size", "0");
	settings->endGroup();

	settings->sync();	//save buffered info
}
