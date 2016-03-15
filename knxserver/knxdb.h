/*
 * knxdb.h
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */

#ifndef KNXDB_H_
#define KNXDB_H_

#include <QObject>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QSqlField>
#include <QList>
#include <QTimer>
#include "common.h"
//#include "gidt_mod_manager.h"


class KnxDB : public QObject {
	Q_OBJECT
private:
	typedef struct {
		uint timeToWait;
		uint timeStamp;
		QString action;
	} tmrAction_t;

	QString m_dbName;
	QString	m_dbHostName;
	QString m_dbUserName;
	QString m_dbPassword;
	QSqlDatabase m_db;
	static QTimer * m_actionTimer;
	static QList<tmrAction_t> * m_actionList;
	static bool m_lastLogicValue;
	static QVariant m_lastReadValue;
	static QString m_lastStringValue;

	bool	CheckIfExists(QString dbParam);
	QSqlQuery ExecuteQuery(QString &sqlQuery);
	bool	AddDbLog(QString &dbParamName, QString &dbParamValue);
	QString PrintfExt(const QString &inString, const QString &param, const QVariant tmpValue, const QString &trueValue, const QString &falseValue,
		const QVariant fixedParameter, const QString &tmpDestination, const QVariant lastReadValue, const bool logicResult);
	void	AddTmrAction(QString action, uint timeToWait);
	void	AddLog(QString logMsg);
	QString GetParamType(QString paramName);
	QVariant ConvertVal(QString value, int valType);
    bool	Compare(QVariant val1, QVariant val2, int type, QString sign);

	QString HandleAirData(QString &request);
	QSqlQuery Db_GetBuildings(void);
	QSqlQuery Db_GetApartments(QString & buildingId);
	QSqlQuery Db_GetRooms(QString & buildingId, QString & apartmentId);
	QSqlQuery Db_GetDevices(QString & buildingId, QString & apartmentId, QString & roomId);
	QSqlQuery Db_GetDeviceData(QString & deviceId);

public:
	KnxDB(QString user, QString password, QString dataBaseName, QString hostName);
	~KnxDB();
	bool Connect();
	bool Disconnect();
	void ProcessCommand(int cmd, QString &param, int processID = 1);
	void ProcessCommand(QString &dbParamName, QString &dbParamValue, int dbParamType, QString cmdSender);
	int GetValue(QString dbParam, QString & value);

signals:
	void OutputKnx(QString);
	void OutputUdp(QString);
	void OutputMod(QString);
	void Log(QString logString);
	void SendEvent(QString moduleName, QString params);

public slots:
	void OnTimer();
	void Input(QString sysEvent);

};

#endif /* KNXDB_H_ */
