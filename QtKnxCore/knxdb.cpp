/*
 * knxdb.cpp
 *
 *  Created on: 23 Ιουλ 2010
 *      Author: Administrator
 */
#include "knxdb.h"


bool KnxDB::m_lastLogicValue = 0;
QVariant KnxDB::m_lastReadValue = 0;
QString KnxDB::m_lastStringValue = "";

QTimer * KnxDB::m_actionTimer = NULL;
QList<KnxDB::tmrAction_t> * KnxDB::m_actionList = NULL;

KnxDB::KnxDB(QString user, QString password, QString dataBaseName, QString hostName)
{
	m_dbUserName = user;
    //m_dbPassword = password;
    //m_dbName = dataBaseName;
    //m_dbHostName = hostName;
	m_db = QSqlDatabase::database();
	//m_modManager = modManager;

	if (m_actionTimer == NULL) {
		m_actionList = new QList<tmrAction_t>();
		m_actionTimer = new QTimer();
		connect(m_actionTimer, SIGNAL(timeout()), this, SLOT(OnTimer()));
		m_actionTimer->start(1000);
	}
    m_db = QSqlDatabase::addDatabase("QSQLITE", "LogicDB");
//	m_db.setHostName(m_dbHostName);
//	m_db.setDatabaseName(m_dbName);
//	m_db.setUserName(m_dbUserName);
//	m_db.setPassword(m_dbPassword);


    m_db.setDatabaseName("./gidt.db");

	if(!m_db.open())
		qFatal("[ModuleDB::ModuleDB] Failed to connect to database. Aborting.");
}


KnxDB::~KnxDB()
{
	Disconnect();
}

void KnxDB::AddLog(QString logMsg)
{
	emit Log("[KnxDB::" + logMsg);
}

bool KnxDB::Connect()
{
	bool res = true;

	if (!m_db.isOpen()) {
		if (!m_db.open()) {
			AddLog(":Connect] Failed to connect to database. Aborting...");
			qFatal("[KnxDB::ModuleDB] Failed to connect to database. Aborting.");
			res = false;
		}
		else {
			AddLog("Connect] Connected to database.");
		}
	}
	return(res);
}

bool KnxDB::Disconnect()
{
	m_db.close();

	bool res = m_db.isOpen();

	return(res);
}

bool KnxDB::CheckIfExists(QString dbParam)
{
	if (!m_db.open())
		Connect();

	bool res = false;
	bool resp = false;
	QSqlQuery query(m_db);

	res = query.prepare("SELECT * FROM tbl_log WHERE fld_paramName=:parm");
	query.bindValue(":parm", dbParam);

	res = query.exec();

	if (!res) {
		AddLog("CheckIfExists] query error." + query.lastError().text());
	}
	else {
		if (query.size() > 0) {
			resp = true;
		}
		else {
			resp = false;
		}
	}
	query.clear();
	return(resp);
}

int KnxDB::GetValue(QString dbParam, QString & value)
{
	int res = -1;
	//GET from database
	QSqlQuery query(m_db);
	QT_TRY {

		if (!m_db.open())
			Connect();
		QString selectField = dbParam.mid(0, dbParam.indexOf("("));
		QString whereField = dbParam.mid(dbParam.indexOf("(") + 1, dbParam.indexOf("=") - dbParam.indexOf("(") - 1);
		QString valueName = dbParam.mid(dbParam.indexOf("=") + 1, dbParam.indexOf(")") - dbParam.indexOf("=") - 1);
		//qDebug() << "SELECT " + selectField + " FROM tbl_log WHERE " + whereField + "=" + valueName;

		query.prepare("SELECT " + selectField + ",fld_dataType FROM tbl_log WHERE " + whereField + "=:val");
		query.bindValue( ":val", valueName );
		if (query.exec()) {
			while (query.next()) {
				QSqlRecord rec = query.record();
				value = query.value(rec.indexOf(selectField)).toByteArray();
				res = query.value(rec.indexOf("fld_dataType")).toInt();
				qDebug() << "[KnxDB::GetValue]: value= " << value << ",type= " << res;
				return(res);
			}

		}
		else
			AddLog("GetValue]: query error." + query.lastError().text());
	}
	QT_CATCH (...){

	}

	query.clear();
	return(res);
}


QVariant KnxDB::ConvertVal(QString value, int valType)
{
	QVariant result;
	bool ok;
    if (valType == Common::PARAM_TYPE_INT) {
		result = value.toInt(&ok);
	}
    else if (valType == Common::PARAM_TYPE_STRING) {
		result = value;
	}
    else if (valType == Common::PARAM_TYPE_DOUBLE) {
		result = value.toDouble(&ok);
	}
    else if (valType == Common::PARAM_TYPE_DATE) {
		//result = value.to(&ok);
	}
    else if (valType == Common::PARAM_TYPE_TIME) {
		result = value.toDouble(&ok);
	}
    else if (valType == Common::PARAM_TYPE_GPS) {
		result = value.toDouble(&ok);
	}
    else if (valType == Common::PARAM_TYPE_TIMESTAMP) {
		result = value.toInt(&ok);
	}
    else if (valType == Common::PARAM_TYPE_KNX_1BIT) {
		result = value.toInt(&ok);
	}
    else if (valType == Common::PARAM_TYPE_KNX_4BIT) {
		result = Common::StrValueToUint(value);
	}
    else if (valType == Common::PARAM_TYPE_KNX_8BIT) {
		result = Common::StrValueToUint(value);
	}
    else if (valType == Common::PARAM_TYPE_KNX_DATE) {
		unsigned char bValue[10];
        Common::StrValueToBytes(value, bValue);
		QDate date(bValue[3] + 2000, bValue[2], bValue[1]);

		result = date.toString("dd/MM/yyyy");
	}
    else if (valType == Common::PARAM_TYPE_KNX_TIME) {

		unsigned char bValue[10];
        Common::StrValueToBytes(value, bValue);
		QDate time(bValue[1] & 0x0f, bValue[2], bValue[3]);

		result = time.toString("HH:mm:ss");
	}
    else if (valType == Common::PARAM_TYPE_KNX_TEMP) {

		//result = value.toDouble(&ok);
	}
	return(result);
}

bool KnxDB::Compare(QVariant val1, QVariant val2, int type, QString sign)
{
    if (type == Common::PARAM_TYPE_STRING) {
		QString tmpVal1 = val1.toString();
		QString tmpVal2 = val2.toString();
		if (sign == "=") {
			if (tmpVal1 == tmpVal2) return(true);
		}
	}
    else if ( (type == Common::PARAM_TYPE_INT) ||
                (type == Common::PARAM_TYPE_TIMESTAMP) ||
                (type == Common::PARAM_TYPE_KNX_1BIT) ||
                (type == Common::PARAM_TYPE_KNX_4BIT) ||
                (type == Common::PARAM_TYPE_KNX_8BIT) ) {
		int tmpVal1 = val1.toInt();
		int tmpVal2 = val2.toInt();
		qDebug() << "[KnxDB::Compare] " << tmpVal1 << " " << sign << " " << tmpVal2;
		if (sign == ">") {
			if (tmpVal1 > tmpVal2) return(true);
		}
		else if (sign == "=") {
			if (tmpVal1 == tmpVal2) return(true);
		}
		else if (sign == "<") {
			if (tmpVal1 < tmpVal2) return(true);
		}
	}
    else if (type == Common::PARAM_TYPE_DOUBLE) {
		double tmpVal1 = val1.toDouble();
		double tmpVal2 = val2.toDouble();
		if (sign == ">") {
			if (tmpVal1 > tmpVal2) return(true);
		}
		else if (sign == "=") {
			if (tmpVal1 == tmpVal2) return(true);
		}
		else if (sign == "<") {
			if (tmpVal1 < tmpVal2) return(true);
		}
	}
    else if (type == Common::PARAM_TYPE_GPS) {
		//result = value.toDouble(&ok);
	}
    else if (type == Common::PARAM_TYPE_KNX_DATE) {
		//val2 always must be string
		QDate dVal1;
		dVal1.fromString(val1.toString(), "ddMMyyyy");
		QDate dVal2;
		dVal2.fromString(val1.toString(), "ddMMyyyy");

        //qDebug("[KnxDB::Compare] dVal1=", dVal1.toString("ddMMyyyy"));
        //qDebug("[KnxDB::Compare] dVal2=", dVal2.toString("ddMMyyyy"));

		if (sign == ">") {
			if (dVal1 > dVal2) return(true);
		}
		else if (sign == "=") {
			if (dVal1 == dVal2) return(true);
		}
		else if (sign == "<") {
			if (dVal1 < dVal2) return(true);
		}
	}
    else if (type == Common::PARAM_TYPE_KNX_TIME) {
		//val2 always must be string
		QTime tVal1;
		tVal1.fromString(val1.toString(), "HH:mm:ss");
		QTime tVal2;
		tVal2.fromString(val1.toString(), "HH:mm:ss");

        //qDebug("[KnxDB::Compare] tVal1=", tVal1.toString("HH:mm:ss"));
        //qDebug("[KnxDB::Compare] tVal2=", tVal2.toString("HH:mm:ss"));

		if (sign == ">") {
			if (tVal1 > tVal2) return(true);
		}
		else if (sign == "=") {
			if (tVal1 == tVal2) return(true);
		}
		else if (sign == "<") {
			if (tVal1 < tVal2) return(true);
		}

	}

	return(false);
}


QSqlQuery KnxDB::ExecuteQuery(QString &sqlQuery)
{
    QSqlQuery newQuery(sqlQuery, m_db);

	newQuery.exec();
	qDebug() << "[KnxDB::ExecuteQuery] results: " << newQuery.size() << ", " << sqlQuery;
	return(newQuery);
}

bool KnxDB::AddDbLog(QString &dbParamName, QString &dbParamValue)
{
	if (!m_db.isOpen())
		Connect();

	bool res = CheckIfExists(dbParamName);

	QT_TRY {

		QSqlQuery query(m_db);
		QDateTime now = QDateTime::currentDateTime();

		if (res) {	//just update
			res = query.prepare("UPDATE tbl_log SET fld_paramValue=:pv,fld_timestamp=:ts"
				" WHERE fld_paramName=:pn");
		}
		else {	//insert
			res = query.prepare("INSERT INTO tbl_log (fld_logId,fld_paramName,fld_paramValue,fld_timestamp)"
				" VALUES (NULL,:pn,:pv,:ts)");
		}

		query.bindValue(":pn", dbParamName);
		query.bindValue(":pv", dbParamValue);
		query.bindValue(":ts", now.toTime_t());

		res = query.exec();
		//qDebug() << "[ModuleDB::AddDbLog] query: " << query.executedQuery();

		if (!res) {
			AddLog("[ModuleDB::AddDbLog] query error: " + query.lastError().text());
		}

	} QT_CATCH (...){
		qDebug() << "[ModuleDB::AddDbLog]: catch error";
	}

	return(res);
}

QString KnxDB::HandleAirData(QString &request)
{
	QString resp;
	QString respData;
	bool ok = false;


	qDebug() << "[HandleAirData] " + request;

	//Check request
    QString tmpStr = GetParam(request, Common::PARAM_CMD);
	if (tmpStr == "READ") {
		QString result;
		QSqlQuery qresult;
		QString buildingId; 
		QString apartmentId;
		QString roomId;
		QString deviceId;

        tmpStr = GetParam(request, Common::PARAM_DATA_START);
		if (tmpStr == "BUILDINGS") {	//READ,AIR,DB,BUILDINGS
			qresult = Db_GetBuildings();
		}
		else if (tmpStr == "APARTMENTS") {
            buildingId = Common::GetParam(request, Common::PARAM_DATA_START+1);

			qresult = Db_GetApartments(buildingId);

			while (qresult.next()) {	//EVENT,DB,AIR,buildingId,apartmentId,apartmentName,apartmentImage,apartmentMask
				QSqlRecord rec = qresult.record();
				tmpStr = qresult.value(rec.indexOf("fld_id")).toString();
				if (tmpStr.length() > 0) {
					result = "EVENT,DB,AIR,APARTMENT," + tmpStr;
					result.append("," + qresult.value(rec.indexOf("fld_name")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_image")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_mask")).toString() + "\n");
					emit OutputUdp(result);
				}
			};
		}
		else if (tmpStr == "ROOMS") {	//READ,AIR,DB,APARTMENTS,BUILDINGSx
            buildingId = Common::GetParam(request, Common::PARAM_DATA_START+1);
            apartmentId = Common::GetParam(request, Common::PARAM_DATA_START+2);
			qresult = Db_GetRooms(buildingId, apartmentId);

			while (qresult.next()) {	//EVENT,DB,AIR,buildingId,apartmentId,apartmentName,apartmentImage,apartmentMask
				QSqlRecord rec = qresult.record();
				tmpStr = qresult.value(rec.indexOf("fld_id")).toString();
				if (tmpStr.length() > 0) {
					result = "EVENT,DB,AIR,ROOM," + tmpStr;
					result.append("," + qresult.value(rec.indexOf("fld_name")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_image")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_mask")).toString() + "\n" );
					emit OutputUdp(result);
				}
			};

		}
		else if (tmpStr == "DEVICE") {	//READ,AIR,DB,DEVICE,ROOMSx,APARTMENTSx,BUILDINGSx
            buildingId = Common::GetParam(request, Common::PARAM_DATA_START+1);
            apartmentId = Common::GetParam(request, Common::PARAM_DATA_START+2);
            roomId =  Common::GetParam(request, Common::PARAM_DATA_START+3);
			qresult = Db_GetDevices(buildingId, apartmentId, roomId);

			while (qresult.next()) {	//EVENT,DB,AIR,buildingId,apartmentId,apartmentName,apartmentImage,apartmentMask
				QSqlRecord rec = qresult.record();
				tmpStr = qresult.value(rec.indexOf("fld_roomId")).toString();
				if (tmpStr.length() > 0) {
					result = "EVENT,DB,AIR,DEVICE," + tmpStr;
					result.append("," + qresult.value(rec.indexOf("fld_deviceId")).toString() + "\n" );
					emit OutputUdp(result);
				}
			};

		}
		else if (tmpStr == "DEVICEDATA") {	//READ,AIR,DB,DEVICEDATA
            deviceId = Common::GetParam(request, Common::PARAM_DATA_START+1);
			qresult = Db_GetDeviceData(deviceId);
			while (qresult.next()) {	//EVENT,DB,AIR,buildingId,apartmentId,apartmentName,apartmentImage,apartmentMask
				QSqlRecord rec = qresult.record();
				tmpStr = qresult.value(rec.indexOf("fld_id")).toString();
				if (tmpStr.length() > 0) {
					result = "EVENT,DB,AIR,DEVICEDATA," + tmpStr;
					result.append("," + qresult.value(rec.indexOf("fld_groupAddrDesc")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_groupAddr")).toString() );
					result.append("," + qresult.value(rec.indexOf("fld_groupAddrStatus")).toString());
					result.append("," + qresult.value(rec.indexOf("fld_groupAddrType")).toString() + "\n" );
					emit OutputUdp(result);
				}
			};
		}
		else if (tmpStr == "ALL") {
			//qresult = Db_GetBuildings();

		}
	}

	if (ok) resp = "EVENT,DB,AIR," + respData;
	else resp.clear();

	return(resp);
}


QSqlQuery KnxDB::Db_GetBuildings(void)
{
	QSqlQuery res(m_db);
	QString queryString = "SELECT fld_id FROM tbl_buildings WHERE 1";
	res = ExecuteQuery(queryString);
	return(res);
}

QSqlQuery KnxDB::Db_GetApartments(QString &buildingId)
{
	QSqlQuery res(m_db);
	QString queryString = "SELECT * FROM tbl_apartments WHERE fld_buildingId='" + buildingId + "'";
	res = ExecuteQuery(queryString);
	return(res);
}

QSqlQuery KnxDB::Db_GetRooms(QString &buildingId, QString &apartmentId)
{
	QSqlQuery res(m_db);
	QString queryString = "SELECT * FROM tbl_room WHERE fld_apartmentId='" + apartmentId + "'";
	res = ExecuteQuery(queryString);
	return(res);

}

QSqlQuery KnxDB::Db_GetDevices(QString &buildingId, QString &apartmentId, QString &roomId)
{
	QSqlQuery res(m_db);
	QString queryString = "SELECT * FROM tbl_roomdevices WHERE fld_roomId='" + roomId + "'"; 
	res = ExecuteQuery(queryString);
	return(res);

}

QSqlQuery KnxDB::Db_GetDeviceData(QString &deviceId)
{
	QSqlQuery res(m_db);
	QString queryString = "SELECT * FROM tbl_knx WHERE fld_id='" + deviceId + "' GROUP BY fld_id"; 
	res = ExecuteQuery(queryString);
	return(res);

}

void KnxDB::Input(QString sysEvent)
{
    QString tmpStr = GetParam(sysEvent, Common::PARAM_DEST);

	if (tmpStr.contains("DB")) {

		//Check from who
        QString sender = GetParam(sysEvent, Common::PARAM_SENDER);

		if (sender.contains("AIR")) {
			HandleAirData(sysEvent);
		}
		else {
			AddLog(sysEvent);
			qDebug() << "[KnxDB::IncomingEvent] " << sysEvent;

			QString paramName, paramValue, paramType, paramSender;
            paramName = Common::GetParam(sysEvent, Common::PARAM_DATA_START);
            paramValue = Common::GetParam(sysEvent, Common::PARAM_DATA_START+1);
            paramType = Common::GetParam(sysEvent, Common::PARAM_DATA_START+2);
            paramSender = Common::GetParam(sysEvent, Common::PARAM_SENDER);
			ProcessCommand(paramName,paramValue,paramType.toInt(),paramSender);
		}
	}
	if (tmpStr.contains("KNX")) {
		emit OutputKnx(sysEvent);
	}
	if (tmpStr.contains("UDP")) {
		emit OutputUdp(sysEvent);
	}

	//if (tmpStr.contains("AIR")) {	//from web interface
	//	HandleAirData(sysEvent);	//emits events it's self
	//}
	emit OutputMod(sysEvent);
}

void KnxDB::ProcessCommand(QString &dbParamName, QString &dbParamValue, int dbParamType, QString cmdSender)	//ported from vb6 project
{
	QSqlQuery query(m_db);
	QSqlRecord rec;
	QString tmpStr;
	int tmpInt;
	QVariant tmpReadValue;
	QString logicOpStr;
	bool 	logicResult;
	QVariant fixedParameterValue;
	QVariant userParameterValue;
	QString destinationStr;
	QString tmpDestination;
	QList<int> idFound;
	bool ok;
	int res = 0;


	//add to log
	AddDbLog(dbParamName, dbParamValue);

	//Find all transaction ids with the given value
	query.prepare("SELECT fld_transactionId FROM tbl_Commands WHERE fld_inCommand=:inCmd ORDER BY fld_transactionId");
	query.bindValue( ":inCmd", dbParamName );
	if ( (res = query.exec()) ) {
		QString value;
		while (query.next()) {
			QSqlRecord rec = query.record();
			tmpInt = query.value(rec.indexOf("fld_transactionId")).toInt(&ok);
			if (tmpInt > 0) {
				idFound << tmpInt;
			}
		};
	}
	//Has any ids been found?
	if (!idFound.isEmpty()) {
		//Then for each one retrieve job list
		for (int i=0; i<idFound.count(); i++) {
			query.prepare("SELECT * FROM tbl_Commands WHERE fld_transactionId=:id ORDER BY fld_transactionSeqNo ASC");
			query.bindValue( ":id", idFound[i] );
			if ( (res = query.exec()) ) {
				QString value;
				while (query.next()) {
					QSqlRecord rec = query.record();
					//Get fld_readParameter if any

					logicResult = true;
					logicOpStr = query.value(rec.indexOf("fld_logicOperation")).toString();
					if (logicOpStr.length()) {
						logicResult = false;
						int valueType = dbParamType;

						tmpStr = query.value(rec.indexOf("fld_fixedParameter")).toString();
						if (logicOpStr.contains("IP")) {
							userParameterValue = ConvertVal(dbParamValue, valueType);
							qDebug() << "[KnxDB::ProcessCommand] userParameterValue= " << userParameterValue;
						}
						if (logicOpStr.contains("RV")) {
							tmpStr = query.value(rec.indexOf("fld_readParameter")).toString();
							if (tmpStr.length() > 1) {	//Is there input value defined
								QString tmpVal;
								valueType = GetValue(tmpStr, tmpVal);
								tmpReadValue = tmpVal;
								tmpReadValue = ConvertVal(tmpVal, valueType);
								qDebug() << "[KnxDB::ProcessCommand] tmpReadValue= " << tmpReadValue;
							}
						}
						if (logicOpStr.contains("FP")) {
							fixedParameterValue = ConvertVal(tmpStr, valueType);
							qDebug() << "[KnxDB::ProcessCommand] fixedParameterValue= " << fixedParameterValue;
						}

						if (!m_lastLogicValue && (logicOpStr == "BRLLO")) {
							//return
							return;
						}

						if (logicOpStr == "RV>FP") {
							if (Compare(tmpReadValue, fixedParameterValue, valueType, ">")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV=FP") {
							if (Compare(tmpReadValue, fixedParameterValue, valueType, "=")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV<FP") {
							if (Compare(tmpReadValue, fixedParameterValue, valueType, "<")) {
								logicResult = true;
							}
						}

						//uint time = QDateTime::currentDateTime().
						if (logicOpStr == "FP>TIME") {
							if ((uint)fixedParameterValue.toInt() > QDateTime::currentDateTime().toTime_t()) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "FP=TIME") {
							if ((uint)fixedParameterValue.toInt() == QDateTime::currentDateTime().toTime_t()) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "FP<TIME") {
							if ((uint)fixedParameterValue.toInt() < QDateTime::currentDateTime().toTime_t()) {
								logicResult = true;
							}
						}

						else if (logicOpStr == "RV>IP") {
							if (Compare(tmpReadValue, userParameterValue, valueType, ">")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV=IP") {
							if (Compare(tmpReadValue, userParameterValue, valueType, "=")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV<IP") {
							if (Compare(tmpReadValue, userParameterValue, valueType, "<")) {
								logicResult = true;
							}
						}

						else if (logicOpStr == "RV>LRV") { //
							if (Compare(tmpReadValue, m_lastReadValue, valueType, ">")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV=LRV") {
							if (Compare(tmpReadValue, m_lastReadValue, valueType, "=")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "RV<LRV") {
							if (Compare(tmpReadValue, m_lastReadValue, valueType, "<")) {
								logicResult = true;
							}
						}

						else if (logicOpStr == "IP>FP") { //
							if (Compare(userParameterValue, fixedParameterValue, valueType, ">")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "IP=FP") {
							if (Compare(userParameterValue, fixedParameterValue, valueType, "=")) {
								logicResult = true;
							}
						}
						else if (logicOpStr == "IP<FP") {
							if (Compare(userParameterValue, fixedParameterValue, valueType, "<")) {
								logicResult = true;
							}
						}
						qDebug() << "[KnxDB::ProcessCommand] logic result: " << logicResult;
					}
					QString outputText = query.value(rec.indexOf("fld_outputText")).toString();
					qDebug() << "outputText: " << outputText;
					if (logicResult 
						|| (outputText.contains("%LTF") )
						|| (outputText.contains("%TF") ) ) {

						destinationStr = query.value(rec.indexOf("fld_operationtarget")).toString();

						QString inString = query.value(rec.indexOf("fld_outputText")).toString();
						
						QString printfRes = PrintfExt(
								inString,
								dbParamValue, 
								tmpReadValue,
								query.value(rec.indexOf("fld_trueValue")).toString(),
								query.value(rec.indexOf("fld_falseValue")).toString(),
								query.value(rec.indexOf("fld_fixedParameter")),
								tmpDestination,
								m_lastReadValue,
								logicResult);
								

						if (destinationStr == "BUS") {
							emit OutputUdp(printfRes);
							emit OutputKnx(printfRes);
						}
						/*
						else if (destinationStr == "SMS") {
							emit OnDbResult(destinationStr, tmpStr);
						}
						else if (destinationStr == "TV") {
							emit OnDbResult(destinationStr, tmpStr);
						}
						else if (destinationStr == "EMAIL") {
							emit OnDbResult(destinationStr, tmpStr);
						}
						else if (destinationStr == "ALARM") {
							emit OnDbResult(destinationStr, tmpStr);
						}
						*/
						else if (destinationStr == "TMR") {
							AddTmrAction(query.value(rec.indexOf("fld_trueValue")).toString(),
									query.value(rec.indexOf("fld_falseValue")).toUInt(&ok));
						}
						else if (destinationStr == "STR") {
							m_lastStringValue = printfRes;
							//tmpDestination = tmpDestination.append(tmpStr);
						}
						else if (destinationStr == "LRV") {
							m_lastReadValue = tmpReadValue;
						}
						else {	//GSM,EMAIL,TV,ALARM,HIFI
							emit SendEvent(destinationStr, printfRes);
						}
						qDebug() << "Target: " << destinationStr << " : " << printfRes;
					}
					m_lastLogicValue = logicResult;
				}
			}
		}
	}
	/*
	else {
		qDebug() << "[KnxDB::ProcessCommand] query failed sending on bus (" << dbParamName << "," << dbParamValue;
		QString knxValue = "knx.groupAddr="+dbParamName+",knx.value="+dbParamValue;
		emit OutputKnx(knxValue); 
		emit OutputUdp(knxValue);
	}
	*/
}


QString KnxDB::PrintfExt(const QString &inString, const QString &param, const QVariant tmpValue, const QString &trueValue, const QString &falseValue,
		const QVariant fixedParameter, const QString &tmpDestination, const QVariant lastReadValue, const bool logicResult)
{
	QString retStr = inString;
	
	qDebug() << "[KnxDB::PrintfExt] retStr before: " << retStr;
	retStr.replace(QString("%UP"), param);
	retStr.replace(QString("%RV"), tmpValue.toString());
	retStr.replace(QString("%TV"), trueValue);
	retStr.replace(QString("%FV"), falseValue);
	retStr.replace(QString("%FP"), fixedParameter.toString());
	retStr.replace(QString("%STR"), tmpDestination);
	retStr.replace(QString("%LSTR"), m_lastStringValue);
	retStr.replace(QString("%LVR"), lastReadValue.toString());

	//QString
	retStr.replace("%TF", logicResult ? trueValue : falseValue);
	retStr.replace("%LTF", m_lastLogicValue ? trueValue : falseValue);

	qDebug() << "[KnxDB::PrintfExt] tmpValue: " << tmpValue.toString();
	qDebug() << "[KnxDB::PrintfExt] retStr after: " << retStr;
	
	return(retStr);
}

//Action timer callback every 500ms
void KnxDB::OnTimer()
{
	//qDebug() << "OnTimer";
	uint now = QDateTime::currentDateTime().toTime_t();

	tmrAction_t tmpAction;
	for(int i = 0; i<m_actionList->size(); i++) {
		tmpAction = m_actionList->at(i);
		if (now - tmpAction.timeStamp >= tmpAction.timeToWait) {
			QString strNothing = "";
			ProcessCommand(tmpAction.action, strNothing, 0, "TIMER");
			qDebug() << "[KnxDB::OnTimer] action: " << tmpAction.action;
			//remove action
			m_actionList->removeAt(i);
		}
	}
}

//Adds a new timer action to the list
void KnxDB::AddTmrAction(QString action, uint timeToWait)
{
	if (m_actionList != NULL) {
		tmrAction_t tmpAction;
		tmpAction.action = action;
		tmpAction.timeToWait = timeToWait;
		tmpAction.timeStamp = QDateTime::currentDateTime().toTime_t();
		*m_actionList << tmpAction;
		qDebug() << "[KnxDB::AddTmrAction] new action added.";
	}
}
















