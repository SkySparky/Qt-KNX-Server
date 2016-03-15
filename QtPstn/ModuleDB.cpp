#include "ModuleDB.h"

ModuleDB::ModuleDB(QString &dbName, QString &dbHostName, QString &dbUserName, QString &dbPassword, QString &sqlName)
{
	m_dbName = dbName;
	m_dbHostName = dbHostName;
	m_dbUserName = dbUserName;
	m_dbPassword = dbPassword;
	m_sqlName = sqlName;
	//qDebug() << "m_dbName: " << m_dbName;

	m_db = QSqlDatabase::addDatabase("QMYSQL", m_sqlName);
	m_db.setHostName(m_dbHostName);
	m_db.setDatabaseName(dbName);
	m_db.setUserName(m_dbUserName);
	m_db.setPassword(m_dbPassword);
	if(!m_db.open())
		qFatal("[ModuleDB::ModuleDB] Failed to connect to database. Aborting.");
}


void ModuleDB::AddLog(QString logMsg)
{
	emit Log("[ModuleDB\\" + m_sqlName + "]: " + logMsg);
}

bool ModuleDB::Connect(void)
{
	bool res = true;

	if (!m_db.isOpen()) {
		//qDebug() << "dbHostName: " << dbHostName << ", dbName: " << dbName << ", dbUserName: " << dbUserName << ", dbPassword: " << dbPassword;

		if (!m_db.open()) {
			AddLog("[ModuleDB::Connect] Failed to connect to database. Aborting...");
			res = false;
		}
		else {
			AddLog("[ModuleDB::Connect] Connected to database.");
			//res = true;
		}
	}

	return(res);
}

bool ModuleDB::Disconnect(void)
{
	m_db.close();
	return(m_db.isOpen());
}

QSqlQuery ModuleDB::ExecuteQuery(QString sqlQuery)
{
	QSqlQuery newQuery(sqlQuery, m_db);
	bool res;

	qDebug() << "InExecuteQuery " << sqlQuery;
	newQuery.exec();
	return(newQuery);
}
