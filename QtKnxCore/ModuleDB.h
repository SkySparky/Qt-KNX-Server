#ifndef MODULEDB_H_
#define MODULEDB_H_

#include <QtCore>
#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include "../KnxCommon/common.h"

class ModuleDB : public QObject
{
	Q_OBJECT
private:
	QSqlDatabase	m_db;
	QString			m_dbName;
	QString			m_dbHostName;
	QString			m_dbUserName;
	QString			m_dbPassword;
	QString			m_sqlName;
	QList<QString>  m_existingParams;

	bool			CheckIfExists(QString &dbParamName);
	void			AddLog(QString logMsg);

public:
    ModuleDB(QString  sqlName, QString  dbName, QString  dbHostName = "", QString  dbUserName = "", QString  dbPassword = "");
	bool			Connect(void);
	bool			Disconnect(void);
	QSqlQuery		ExecuteQuery(QString sqlQuery);

signals:
	void Log(QString logString);
};

#endif //MODULEDB_H_
