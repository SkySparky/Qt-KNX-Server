#include "screenHandler.h"

/**
    - HOW THE FUCK IT WORKS -

    [Stages SIGNAL]         --->        [ScreenHandler SLOTS]                       [Description]
    quit                                onQuit                                      Quits application
    exit(int,int)                       onScreenChange(int,int)                     Changes between screenhandler's screens
    sendDataToKnx(int,QString,QString)  onDataFromScreenObj(int,QString,QString)    Sends KNX req/resp/ack to screenhandler that forwards them to knxgateway
    Notify(int,QString)                 onNotify(int,QString)                       Sends notification to screenhandler (see common.h)


    [ScreenHandler SIGNALS]      --->       [Stages SLOTS]                          [Description]
    sendDataToScreenObj(QString,QString)    onDataFromKnx(QString,QString)          Forwards data from KNX to running stage
    Notify(int,QString)                     onNotify(int,QString)                   Sends notifications to running stage
    SendMsg(QString,QString)                onMsg(QString,QString)                  Display a message box on the running stage


*/

typedef enum {
    MODE_KNXIP_GATEWAY = 0,
    MODE_GIDT_GATEWAY
} en_conn_mode;

int glb_editIndex = -1; //keeps the index that it's about to be edited

ScreenHandler::ScreenHandler(QString iniFile)
{
    m_scrStageSettings.conf = iniFile;
    m_scrBackstageSettings.conf = iniFile;

    m_conf = iniFile;
    m_currentScreenObj = NULL;

    //Check if ini file exists and if it is then start with the stage page
    QFile ini(iniFile);

    //Read ini file
    QSettings settings(iniFile, QSettings::IniFormat);

    //Get gateway mode
    m_gatewayMode = settings.value("Gateway/mode", 0).toInt();

    bool exists = ini.exists();
    // Choose start screen depending on the ini file
    if (exists) {
        qDebug() << "[ScreenHandler]: Loading SCREEN_STAGE";
        onScreenChange(Common::SCREEN_ID_STAGE);
    }
    else {
        qDebug() << "[ScreenHandler]: Loading SCREEN_BACKSTAGE";
        onScreenChange(Common::SCREEN_ID_BACKSTAGE, Backstage::MENU_BACKSTAGE);
        onMsg(Common::MSG_TYPE_INFO, tr("Please specify a KNX gateway from settings."));
    }

    m_connectTmr.setInterval(5000);

    //Create KNX gateway object
    //
    m_gw = new KnxGateway(m_conf);
    QObject::connect(m_gw, SIGNAL(Msg(int,QString)),
            this, SLOT(onMsg(int,QString)));
    QObject::connect(m_gw, SIGNAL(KnxIpState(KnxGateway::en_knxGatewayState)),
            this, SLOT(onKnxStateChange(KnxGateway::en_knxGatewayState)));
    QObject::connect(m_gw, SIGNAL(DataFromKnx(QString)),
            this, SLOT(onDataFromKnx(QString)), Qt::DirectConnection);  //KNX -> here [data] //here -> KNX [data]
    QObject::connect(m_gw, SIGNAL(Notify(int,QString)),
            this, SLOT(onKnxNotify(int,QString)), Qt::DirectConnection);    //KNX -> here [error]
    QObject::connect(this, SIGNAL(sendDataToKnx(QString,QString,cEMI::en_cemiAction)),
            m_gw, SLOT(onSendData(QString,QString,cEMI::en_cemiAction)), Qt::DirectConnection);

    QObject::connect(&m_autosearchTmr, SIGNAL(timeout()),
            this, SLOT(onAutosearchTimer()));
    QObject::connect(&m_connectTmr, SIGNAL(timeout()),
            this, SLOT(onConnectTimer()));


    //Create UDP gateway object
    //
    m_ugw = new UdpGateway(m_conf);
    QObject::connect(m_ugw, SIGNAL(Msg(int,QString)), this, SLOT(onMsg(int,QString)));
    QObject::connect(m_ugw, SIGNAL(UdpState(KnxGateway::en_knxGatewayState)),
                     this, SLOT(onKnxStateChange(KnxGateway::en_knxGatewayState)));
    QObject::connect(m_ugw, SIGNAL(DataFromUdp(QString)),
                     this, SLOT(onDataFromKnx(QString)), Qt::DirectConnection);
    QObject::connect(m_ugw, SIGNAL(Notify(int,QString)),
                     this, SLOT(onKnxNotify(int,QString)), Qt::DirectConnection);
    QObject::connect(this, SIGNAL(sendDataToUdp(QString,QString,cEMI::en_cemiAction)),
            m_ugw, SLOT(onSendData(QString,QString,cEMI::en_cemiAction)), Qt::DirectConnection);


    QString gwexists = settings.value("Gateway/gwIp").toString();
    if (!gwexists.isEmpty()) {
        if (m_gatewayMode == MODE_KNXIP_GATEWAY) m_gw->Identify();
        else m_ugw->Identify();
    }
    else {
        onMsg(Common::MSG_TYPE_INFO, "No config/gateway found! Use settings.");
    }
}


void ScreenHandler::onKnxStateChange(KnxGateway::en_knxGatewayState state)
{
    switch (state) {
    case KnxGateway::KNXIP_STATE_SEARCHING:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_SEARCHING";
        SendMsg("INFO", "Searching for gateway.");
        m_connectTmr.start();
        break;

    case KnxGateway::KNXIP_STATE_IDENTIFY:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_IDENTIFY";
//        if (m_gatewayMode == MODE_KNXIP_GATEWAY) m_gw->Connect();
//        else m_ugw->Connect();
//        m_connectTmr.start();
        break;

    case KnxGateway::KNXIP_STATE_FOUND_GW:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_FOUND_GW";
        SendMsg("INFO", "Found Gateway");
        break;

    case KnxGateway::KNXIP_STATE_CONNECTING:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_CONNECTING";
        SendMsg("INFO", "Trying to connect to gateway.");

        break;

    case KnxGateway::KNXIP_STATE_CONNECTED:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_CONNECTED";
        m_connectTmr.stop();
        emit Notify(Common::NOTIFY_KNX_CONNECTED, "");
        SendMsg("INFO", "Connected to gateway.");
        break;

    case KnxGateway::KNXIP_STATE_DISCONNECTING:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_DISCONNECTING";

        break;

    case KnxGateway::KNXIP_STATE_DISCONNECTED:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_DISCONNECTED";
        SendMsg("INFO", "No connection with gateway.");
        emit Notify(Common::NOTIFY_KNX_DISCONNECTED, "");

        break;
    case KnxGateway::KNXIP_STATE_ERROR:
        qDebug() << "[ScreenHandler::onKnxStateChange] KNXIP_STATE_ERROR";
        KnxGateway::en_knxGatewayError error = KnxGateway::KNXIP_ERR_NONE;
        if (m_gatewayMode == MODE_KNXIP_GATEWAY) error = m_gw->GetError();

        SendMsg("INFO", "Gateway error");
        if (error == KnxGateway::KNXIP_ERR_WRONG_SEQ_NUMBER) {
            if (m_gatewayMode == MODE_KNXIP_GATEWAY) m_gw->Connect();
            else m_ugw->Connect();
            m_connectTmr.start();
        }
        break;
    }
}

//On messages from QML
void ScreenHandler::onMsg(int type, QString msg)
{
    QString title;
    if (type == Common::MSG_TYPE_ERROR) title = "ERROR";
    else if (type == Common::MSG_TYPE_WARNING) title = "WARNING";
    else if (type == Common::MSG_TYPE_INFO) title = "INFO";

    emit SendMsg(title, msg);

    qDebug() << title << " : " << msg;
}


void ScreenHandler::onQuit()
{
    qDebug() << "Quiting...";
    if (m_gatewayMode == MODE_KNXIP_GATEWAY) m_gw->Disconnect();
    else m_ugw->Disconnect();
}


//When stage or backstage send an exit signal to change from one stage to another
//
void ScreenHandler::onScreenChange(int wantedScreen, int wantedSubScreen)
{
    qDebug() << "[ScreenHandler/onScreenChange] reloading screen";

    switch(wantedScreen) {
    case Common::SCREEN_ID_STAGE: {
        if (wantedSubScreen == 5) { //reconnect
            if (m_gatewayMode == MODE_KNXIP_GATEWAY) {
                m_gw->Disconnect();
                if (!m_gw->IsConnected()) {
                    m_gw->Connect();
                    m_connectTmr.start();
                }
            }
            else {
                m_ugw->Disconnect();
                if (!m_ugw->IsConnected()) {
                    m_ugw->Connect();
                    m_connectTmr.start();
                }
            }

            return;
        }
        m_currentStage = Common::SCREEN_ID_STAGE;
        if (m_currentScreenObj != NULL) {
            DisconnectSignals();
            m_currentScreenObj->deleteLater();
            m_currentScreenObj = NULL;
        }
        m_currentScreenObj = qobject_cast<QObject*>(new Stage(m_scrStageSettings));
        ConnectSignals();
    }
        break;

    case Common::SCREEN_ID_BACKSTAGE:
        m_currentStage = Common::SCREEN_ID_BACKSTAGE;
        if (m_currentScreenObj != NULL) {
            DisconnectSignals();
            m_currentScreenObj->deleteLater();
            m_currentScreenObj = NULL;
        }

        m_currentScreenObj = qobject_cast<QObject*>(new Backstage(m_scrBackstageSettings, wantedSubScreen));
        ConnectSignals();
        onNotify(Common::NOTIFY_BACKSTAGE_COMPLETED, "");
        if (wantedSubScreen != 0) {

        }
        break;
    }
}

void ScreenHandler::onDataFromKnx(QString data)
{
    qDebug() << "[ScreenHandler::onDataFromKnx] data: " << data;
    QString groupAddr = Common::GetParam(data, Common::PARAM_DATA_START);
    QString value = Common::GetParam(data, Common::PARAM_DATA_START+1);
    emit sendDataToScreenObj(groupAddr, value);
    if (m_autosearch) { //if autosearch is enabled then collect the addresses
        m_autosearchAddr.append(groupAddr);
    }
}


void ScreenHandler::onDataFromScreenObj(int type, QString groupAddr, QString value,cEMI::en_cemiAction action)
{
    //QString data = "WRITE,KNX,UDP," + groupAddr + "," + value;

    if (groupAddr.isEmpty()) return;    //skip empty group addresses

    if (m_gatewayMode == MODE_KNXIP_GATEWAY)
        emit sendDataToKnx(groupAddr, value, action);
    else
        emit sendDataToUdp(groupAddr, value, action);
    //qDebug() << "[ScreenHandler::onDataFromScreenObj] groupAddr: " << groupAddr << ", value" << value;
}


//Receive Notifications from KNX and forward them to screens
//
void ScreenHandler::onKnxNotify(int notifyType, QString notifyData)
{
    qDebug() << "[ScreenHandler::onKnxNotify] type: " << notifyType
             << ", data: " << notifyData;

    //Warning DATA HANDLING IS DONE IN [Backstage::onNotify] !!!!
    emit Notify(notifyType, notifyData);
}

//Receive notifications from Stages
//
void ScreenHandler::onNotify(int notifyType, QString notifyData)
{
    qDebug() << "[ScreenHandler::onNotify] type: " << notifyType
             << ", data: " << notifyData;

    switch(notifyType) {
    case Common::NOTIFY_SETTINGS_SAVE_REQ: {
        //Change gateway ip in configuration and save to ini
        qDebug() << "[ScreenHandler::onNotify] save " << Common::GetParam(notifyData, 1) << " to "
                    << m_conf;
        QSettings settings(m_conf, QSettings::IniFormat);
        settings.setValue("Gateway/gwIp", Common::GetParam(notifyData, 1));  //save ip to config
        onMsg(Common::MSG_TYPE_INFO, "Settings are saved!");
    }
        break;

    case Common::NOTIFY_KNX_SEARCH_REQ:
        if (m_gatewayMode == MODE_KNXIP_GATEWAY) {
            if (!m_gw->IsConnected())
                m_gw->Search(); //This will trigger a search and signal the result from knx to ScreenHandler::onKnxNotify
            else
                onMsg(Common::MSG_TYPE_INFO, tr("Is already connected!"));
        }
        else {
            if (!m_ugw->IsConnected())
                m_ugw->Search(); //This will trigger a search and signal the result from knx to ScreenHandler::onKnxNotify
            else
                onMsg(Common::MSG_TYPE_INFO, tr("Is already connected!"));
        }
        break;

    case Common::NOTIFY_SETTINGS_REQ: {
            QSettings settings(m_conf, QSettings::IniFormat);
            emit Notify(notifyType, settings.value("Gateway/gwIp").toString());
        }
        break;

    case Common::NOTIFY_RESET_ALL: {
        ClearConf(m_conf, 0);
        onMsg(Common::MSG_TYPE_INFO, tr("Configuration is reseted."));
    }
        break;

    case Common::NOTIFY_REMOVE_DEVICE: {
//        tp_knxDevice device;    //create a new device struct
//        device.descr = Common::GetParam(notifyData, 1);
//        device.type = Common::GetParam(notifyData, 2);
//        device.ga = Common::GetParam(notifyData, 3);
        bool ok = false;
        int index = Common::GetParam(notifyData, 1).toInt(&ok);
        if (ok) {
            if (RemoveDevice(m_conf, index) ) {
                onMsg(Common::MSG_TYPE_INFO, tr("Device removed."));
            }
            else {
                onMsg(Common::MSG_TYPE_WARNING, tr("Couldn't remove device."));
            }
        }
        else {
            onMsg(Common::MSG_TYPE_ERROR, tr("Couldn't remove device from index"));
        }

    }
        break;
    case Common::NOTIFY_ADD_DEVICE: {
        tp_knxDevice device;    //create a new device struct
        int index = Common::GetParam(notifyData, 15).toInt();

        device.descr = Common::GetParam(notifyData, 1);     //extract device params from notifyData [descr=,root=,tags=,ga=,type]
        device.root = Common::GetParam(notifyData, 2);
        QString tmpstr = Common::GetParam(notifyData, 3);
        int len = tmpstr.indexOf("/");
        tmpstr.remove(0, len+1);  //remove first "/"
        device.tags = tmpstr;
        device.type = Common::GetParam(notifyData, 4);
        device.ga = Common::GetParam(notifyData, 5);
        if (device.type.isEmpty()) device.type = "switch";
        if (device.descr.isEmpty() || device.ga.isEmpty() ) { //incomplete device data
            onMsg(Common::MSG_TYPE_ERROR, tr("Device could not be added."));
        }
        else {  //add new device
            int type = device.type.toInt();
            if (type == GroupAddrObject::DEV_SWITCH) {
                device.type = "switch";
                device.sa = Common::GetParam(notifyData, 10);
            }
            else if ( (type == GroupAddrObject::DEV_DIMMER)
                     || (type == GroupAddrObject::DEV_SHUTTER) ) {
                device.type = (type == GroupAddrObject::DEV_DIMMER) ? "dimmer" : "shutter";
                device.ga1 = Common::GetParam(notifyData, 6);
                device.sa = Common::GetParam(notifyData, 10);
                device.sa1 = Common::GetParam(notifyData, 11);
            }
            else if (type == GroupAddrObject::DEV_RGB) {
                device.type = "rgb";
                device.ga1 = Common::GetParam(notifyData, 6);
                device.ga2 = Common::GetParam(notifyData, 7);
                device.ga3 = Common::GetParam(notifyData, 8);
                device.sa = Common::GetParam(notifyData, 10);
                device.sa1 = Common::GetParam(notifyData, 11);
                device.sa2 = Common::GetParam(notifyData, 12);
                device.sa3 = Common::GetParam(notifyData, 13);
            }
            else if (type == GroupAddrObject::DEV_TAGBUTTON) {
                device.type = "tagbtn";
            }
            else if (type == GroupAddrObject::DEV_TEMP) {
                device.type = "temp";
                device.sa = Common::GetParam(notifyData, 10);
            }

            if (index < 0)
                AppendDevice(m_conf, device);
            else {
                qDebug() << "Removing index: " << index;
                RemoveDevice(m_conf, index);    //remove previous device
                AppendDevice(m_conf, device);   //add new device
            }

            onMsg(Common::MSG_TYPE_INFO, tr("Device added."));
        }
    }
        break;

    case Common::NOTIFY_AUTOSEARCH: {
            if (m_gw->IsConnected() || m_ugw->IsConnected()) {
                m_autosearch = true;
                m_autosearchAddr.clear();
                m_autosearchTmr.setInterval(10000);
                m_autosearchTmr.start();
                onMsg(Common::MSG_TYPE_INFO, tr("Autosearch started."));
            }
            else {
                onMsg(Common::MSG_TYPE_ERROR, tr("Not connected to gateway!"));
            }
        }
        break;

    case Common::NOTIFY_IMPORT_CONFIG:
    case Common::NOTIFY_EXPORT_CONFIG: {
        QString server = Common::GetParam(notifyData, 1);
        QString project = Common::GetParam(notifyData, 2);
        QString user = Common::GetParam(notifyData, 3);
        QString pass = Common::GetParam(notifyData, 4);

        if ( server.isEmpty() || project.isEmpty() ||
                user.isEmpty() || pass.isEmpty() )
            onMsg(Common::MSG_TYPE_ERROR, "Please fill all the fields");
        else if (notifyType == Common::NOTIFY_IMPORT_CONFIG)
            ImportRemoteConf(server, user, pass, project);
        else if (notifyType == Common::NOTIFY_EXPORT_CONFIG)
            ExportRemoteConf(server, user, pass, project);
        }
        break;

    case Common::NOTIFY_EDIT_DEVICE:

        glb_editIndex = Common::GetParam(notifyData, 1).toInt();
        onScreenChange(Common::SCREEN_ID_BACKSTAGE, 0);
        break;

    case Common::NOTIFY_BACKSTAGE_COMPLETED:
        if (glb_editIndex >= 0) {   //on complete send device data
            //Get device from index
            QList<tp_knxDevice> devices = GetDevicesFromConf(m_conf);

            if (devices.size() < glb_editIndex) break;

            QString tags = GetDeviceTags(glb_editIndex);    //Get tags

            QString notData = devices[glb_editIndex].index + "," +
                    devices[glb_editIndex].descr + "," +
                    devices[glb_editIndex].root + "," +
                    tags + "," +
                    //devices[glb_editIndex].tags + "," +
                    devices[glb_editIndex].type + "," +
                    devices[glb_editIndex].ga + "," +
                    devices[glb_editIndex].ga1 + "," +
                    devices[glb_editIndex].ga2 + "," +
                    devices[glb_editIndex].ga3 + "," +
                    devices[glb_editIndex].ga4 + "," +
                    devices[glb_editIndex].sa + "," +
                    devices[glb_editIndex].sa1 + "," +
                    devices[glb_editIndex].sa2 + "," +
                    devices[glb_editIndex].sa3 + "," +
                    devices[glb_editIndex].sa4;
            emit Notify(Common::NOTIFY_EDIT_DEVICE, notData); //edit device with index glb_editIndex
            glb_editIndex = -1; //reset index
        }
        break;

    case Common::NOTIFY_STAGE_SYS_TAGS:
        emit Notify(Common::NOTIFY_STAGE_SYS_TAGS, GetDeviceTags(Common::GetParam(notifyData, 1).toInt()));    //Get tags
        break;

    case Common::NOTIFY_STATE_REMOVE_TAGS:
        //remove incoming tags from everywhere
        qDebug() << "NOTIFY_STATE_REMOVE_TAGS: " << notifyData;
        RemoveTags(notifyData);
        emit Notify(Common::NOTIFY_STAGE_SYS_TAGS, GetDeviceTags(Common::GetParam(notifyData, 1).toInt()));    //Get tags
        break;

    }
}

int ScreenHandler::RemoveTags(QString tags)
{

    QStringList taglist;
    QList<tp_knxDevice> devices = GetDevicesFromConf(m_conf);

    int len = tags.indexOf("/");
    tags.remove(0, len+1);                          // remove first "/"
    taglist = tags.split("/");                      // split incoming tags

restart:
    for (int k = 0; k<devices.size(); k++) {        // for each device
        QString newTags;
        for (int i=0; i<taglist.size(); i++) {      // and for each tag
            if (!taglist.at(i).isEmpty()) {         // if it's not empty
                if (devices[k].type == "tagbtn") {  // if a tag button has this as ga then remove the button
                    if (devices[k].ga.contains(taglist.at(i))) {
                        //remove button
                        devices.removeAt(k);
                        goto restart;
                    }
                }
                else if (devices[k].tags.contains(taglist.at(i))) {     // if device's tags contain a deleted tag
                    //then skip add it to the new tag list
                    QStringList devTagList = devices[k].tags.split("/");
                    devices[k].tags.clear();
                    for(int j=0; j<devTagList.size(); j++) {
                        if (devTagList.at(j) != taglist.at(i)) {
                            devices[k].tags.append("/" + devTagList.at(j));
                        }
                    }
                    if (devices[k].tags.mid(0, 1) == "/") devices[k].tags.remove(0, 1); // remove first '/' char
                }
            }
        }
    }
    //Delete tagbuttons with
    if (devices.size() > 0) ClearConf(m_conf, 1); //clear all devices
    return(SaveDevicesToConf(m_conf, devices));
}

QString ScreenHandler::GetDeviceTags(int deviceIndex)
{
    QString tags = "";
    QStringList taglist;
    int tmpint = 0;
    QString tmpstr;
    QList<tp_knxDevice> devices = GetDevicesFromConf(m_conf);

    if (devices.size() < deviceIndex) return(tags); //if index is out of range then return

    if (deviceIndex >= 0) {
        //Get device's tags
        taglist = devices[deviceIndex].tags.split("/");
        for (int i=0; i<taglist.size(); i++) {
            if (!taglist.at(i).isEmpty()) {
                tmpint++;
                tmpstr.append("/" + taglist.at(i));
            }
        }
    }

    tags = QString::number(tmpint) + tmpstr;


    foreach (tp_knxDevice device, devices) {           //for each device
        taglist = device.tags.split("/");               //split tags
        for (int i=0; i<taglist.size(); i++) {           //and for each tag
            if (!taglist.at(i).isEmpty()) {              //if it's not empty
                if (!tags.contains(taglist.at(i))) {     //and is not already in list
                    tags.append("/" + taglist.at(i));    //then add it
                }
            }
        }
    }
    return(tags);
}



void ScreenHandler::ImportRemoteConf(QString server, QString username, QString passwd, QString project)
{
    QUrl url("gidt/getconf.php");
    url.setHost(server);
    url.setScheme("http");

    QList<QPair<QString,QString> > query;
    QPair<QString,QString> pair_user("user", username);
    QPair<QString,QString> pair_pass("pass", passwd);
    QPair<QString,QString> pair_project("project", project);
    query.append(pair_user);
    query.append(pair_pass);
    query.append(pair_project);
    url.setQueryItems(query);
    qDebug() << "[Backstage::ImportRemoteConf] : " << url.toString();

    m_importReply = m_manager.get(QNetworkRequest(url.toString()));
    connect(m_importReply, SIGNAL(finished()), this, SLOT(onImportReplyFinished()));

    onMsg(Common::MSG_TYPE_INFO, tr("Importing configuration..."));
}


void ScreenHandler::ExportRemoteConf(QString server, QString username, QString passwd, QString project)
{
    QUrl url("gidt/setconf.php");
    url.setHost(server);
    url.setScheme("http");

    //Get data
    QFile file(m_conf);
    file.open(QIODevice::ReadOnly);
    QByteArray data(file.readAll());
    file.close();
    QString str_data(data);
    str_data.replace(QString("\\"), QString("\\\\"));

    //get parameters
    QUrl params;
    params.addQueryItem("user", username);
    params.addQueryItem("pass", passwd);
    params.addQueryItem("project", project);
    params.addQueryItem("data", str_data);

    qDebug() << "params: " << params.encodedQuery();

    QNetworkRequest networkRequest(url);
    networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

    m_exportReply = m_manager.post(networkRequest, params.encodedQuery());
    connect(m_exportReply, SIGNAL(finished()), this, SLOT(onExportReplyFinished()));

    onMsg(Common::MSG_TYPE_INFO, tr("Exporting configuration..."));
}


void ScreenHandler::onExportReplyFinished()
{
    if (!m_exportReply->error()) {
        QByteArray resp = m_exportReply->readAll();
        qDebug() << "[Backstage::onExportReplyFinished]" << resp.data();
        if (resp.contains("success")) {
            qDebug() << "[Backstage::onExportReplyFinished] success!";
            onMsg(Common::MSG_TYPE_INFO, tr("Export succeded"));
        }
        else {
            //some kind of error. show in msg box
            onMsg(Common::MSG_TYPE_ERROR, tr("Export failed!"));
        }
    }
    else {
        qDebug() << "[Backstage::onExportReplyFinished] Error: " << m_exportReply->errorString();
        onMsg(Common::MSG_TYPE_ERROR, tr("Export error."));
    }
    m_exportReply->deleteLater();

}


void ScreenHandler::onImportReplyFinished()
{
    if (!m_importReply->error()) {
        QByteArray resp = m_importReply->readAll();
        if (resp.size() < 10) {
            onMsg(Common::MSG_TYPE_WARNING, tr("Import returned no data. Wrong input?"));
            return;
        }
        qDebug() << "[Backstage::onImportReplyFinished]" << resp.data();
        QFile file("./new_conf.tmp");
        file.open(QIODevice::WriteOnly);
        file.write(resp);
        file.close();

        //delete devices from old file
        ClearConf(m_conf, 1);

        //Copy devices from temp file
        QSettings tmp_settings(file.fileName(), QSettings::IniFormat); //open inifile
        QSettings settings(m_conf, QSettings::IniFormat);

        int size = tmp_settings.beginReadArray("GroupAddresses");   //find the [GroupAddresses] size
        settings.beginWriteArray("GroupAddresses");

        for (int i = 0; i < size; i++) {    //fill device list with devices
            tmp_settings.setArrayIndex(i);
            settings.setArrayIndex(i);
            settings.setValue("descr", tmp_settings.value("descr").toString());
            settings.setValue("root", tmp_settings.value("root").toString());
            settings.setValue("tags", tmp_settings.value("tags").toString());
            settings.setValue("type", tmp_settings.value("type").toString());
            QString type = tmp_settings.value("type").toString();
            if (type == "switch") {
                settings.setValue("ga", tmp_settings.value("ga").toString());
                settings.setValue("sa", tmp_settings.value("sa").toString());
            }
            else if (type == "dimmer") {
                settings.setValue("ga", tmp_settings.value("ga").toString());
                settings.setValue("ga1", tmp_settings.value("ga1").toString());
                settings.setValue("sa", tmp_settings.value("sa").toString());
                settings.setValue("sa1", tmp_settings.value("sa1").toString());

            }
            else if (type == "shutter") {
                settings.setValue("ga", tmp_settings.value("ga").toString());
                settings.setValue("ga1", tmp_settings.value("ga1").toString());
                settings.setValue("sa", tmp_settings.value("sa").toString());
                settings.setValue("sa1", tmp_settings.value("sa1").toString());
            }
            else if (type == "rgb") {
                settings.setValue("ga", tmp_settings.value("ga").toString());
                settings.setValue("ga1", tmp_settings.value("ga1").toString());
                settings.setValue("ga2", tmp_settings.value("ga2").toString());
                settings.setValue("ga3", tmp_settings.value("ga3").toString());
                settings.setValue("sa", tmp_settings.value("sa").toString());
                settings.setValue("sa1", tmp_settings.value("sa1").toString());
                settings.setValue("sa2", tmp_settings.value("sa2").toString());
                settings.setValue("sa3", tmp_settings.value("sa3").toString());
            }
            else if (type == "tagbtn") {
                settings.setValue("ga", tmp_settings.value("ga").toString());
            }

        }
        settings.endArray();

        //delete temp file
        file.remove();

        onMsg(Common::MSG_TYPE_INFO, tr("Import succeded."));
    }
    else {
        qDebug() << "[Backstage::onImportReplyFinished] Error: " << m_importReply->errorString();
        onMsg(Common::MSG_TYPE_ERROR, tr("Import failed."));
    }
    m_importReply->deleteLater();
}


void ScreenHandler::onConnectTimer()
{
    m_connectTmr.stop();
    onMsg(Common::MSG_TYPE_ERROR,tr("Could not find or connect to gateway"));
    onKnxStateChange(KnxGateway::KNXIP_STATE_DISCONNECTED);
}


void ScreenHandler::onAutosearchTimer()
{
    m_autosearchTmr.stop();

    onMsg(Common::MSG_TYPE_INFO, "Autosearch ended.");

    //qsort(m_autosearchAddr);    //sort addresses
    QList<QString> addresses;
    for(int i=0; i<m_autosearchAddr.size(); i++) {  //search m_autosearchAddr for individual addresses
        if (!addresses.contains(m_autosearchAddr[i])) {
            addresses.append(m_autosearchAddr[i]);
        }
    }
    //now addresses contain only the individual addresses
    int max_ref = 0;
    int index = -1;
    for (int i=0; i<addresses.size(); i++) {
        int ref = m_autosearchAddr.count(addresses[i]);
        qDebug() << "[ScreenHandler::onAutosearchTimer] addr: " << addresses[i] << ", count: " << ref;
        if (ref > max_ref) {
            max_ref = ref;
            index = i;
        }
    }
    if (index >= 0) {
        qDebug() << "[ScreenHandler::onAutosearchTimer] the group address is " << addresses[index];
        emit Notify(Common::NOTIFY_AUTOSEARCH, addresses[index]);   //send notify to backstage qml
    }
}


// Append a new device under the [GroupAddresses] key in the conf file
//
int ScreenHandler::AppendDevice(QString conf, ScreenHandler::tp_knxDevice device)
{
    //Get device list
    QList<tp_knxDevice> devices = GetDevicesFromConf(conf);
    devices.append(device);
    if (devices.size() > 0) ClearConf(conf, 1); //clear all devices
    return( SaveDevicesToConf(conf, devices) );
}


int ScreenHandler::RemoveDevice(QString conf, int index)
{
    //Get device list
    QList<tp_knxDevice> devices = GetDevicesFromConf(conf);
    devices.removeAt(index);
    if (devices.size() > 0) ClearConf(conf, 1); //clear all devices
    return( SaveDevicesToConf(conf, devices) );
}


// Clear conf file with a mode
// mode: 0, ALL
// mode: 1, only devices
//
void ScreenHandler::ClearConf(QString conf, int mode)
{
    QSettings settings(conf, QSettings::IniFormat); //open conf file
    if (mode != 1) settings.setValue("Gateway/gwIp", "");   //clear gateway if mode=1
    settings.beginGroup("GroupAddresses");  //remove all addresses
    settings.remove("");
    settings.endGroup();
}


// Retrieve all devices under [GroupAddresses] key in conf file and return the list
//
QList<ScreenHandler::tp_knxDevice> ScreenHandler::GetDevicesFromConf(QString conf)
{
    QSettings settings(conf, QSettings::IniFormat); //open inifile
    QList<tp_knxDevice> devices;    //create a new device llist
    int size = settings.beginReadArray("GroupAddresses");   //find the [GroupAddresses] size
    for (int i = 0; i < size; i++) {    //fill device list with devices
        settings.setArrayIndex(i);
        tp_knxDevice device;
        device.index = QString::number(i);
        device.descr = settings.value("descr").toString();
        device.root = settings.value("root").toString();
        device.tags = settings.value("tags").toString();
        device.type = settings.value("type").toString();
        if (device.type == "switch") {
            device.ga = settings.value("ga").toString();
            device.sa = settings.value("sa").toString();
        }
        else if (device.type == "dimmer") {
            device.ga = settings.value("ga").toString();
            device.ga1 = settings.value("ga1").toString();
            device.sa = settings.value("sa").toString();
            device.sa1 = settings.value("sa1").toString();
        }
        else if (device.type == "shutter") {
            device.ga = settings.value("ga").toString();
            device.ga1 = settings.value("ga1").toString();
            device.sa = settings.value("sa").toString();
            device.sa1 = settings.value("sa1").toString();
        }
        else if (device.type == "rgb") {
            device.ga = settings.value("ga").toString();
            device.ga1 = settings.value("ga1").toString();
            device.ga2 = settings.value("ga2").toString();
            device.ga3 = settings.value("ga3").toString();
            device.sa = settings.value("sa").toString();
            device.sa1 = settings.value("sa1").toString();
            device.sa2 = settings.value("sa2").toString();
            device.sa3 = settings.value("sa3").toString();
        }
        else if (device.type == "tagbtn") {
            device.ga = settings.value("ga").toString();
        }
        devices.append(device);
    }
    settings.endArray();
    return(devices);    //return device list
}


// Save the device list under [GroupAddresses] key in the conf file
//
int ScreenHandler::SaveDevicesToConf(QString conf, QList<ScreenHandler::tp_knxDevice> devices)
{
    QSettings settings(conf, QSettings::IniFormat); //open inifile
    settings.beginWriteArray("GroupAddresses");   //find the [GroupAddresses] size
    for (int i = 0; i < devices.size(); i++) {    //fill device list with devices
        settings.setArrayIndex(i);
        settings.setValue("descr", devices.at(i).descr);
        settings.setValue("tags", devices.at(i).tags);
        settings.setValue("root", devices.at(i).root);
        settings.setValue("type", devices.at(i).type);
        if (devices.at(i).type == "switch") {
            settings.setValue("ga", devices.at(i).ga);
            settings.setValue("sa", devices.at(i).sa);
        }
        else if (devices.at(i).type == "dimmer") {
            settings.setValue("ga", devices.at(i).ga);
            settings.setValue("ga1", devices.at(i).ga1);
            settings.setValue("sa", devices.at(i).sa);
            settings.setValue("sa1", devices.at(i).sa1);
        }
        else if (devices.at(i).type == "shutter") {
            settings.setValue("ga", devices.at(i).ga);
            settings.setValue("ga1", devices.at(i).ga1);
            settings.setValue("sa", devices.at(i).sa);
            settings.setValue("sa1", devices.at(i).sa1);
        }
        else if (devices.at(i).type == "rgb") {
            settings.setValue("ga", devices.at(i).ga);
            settings.setValue("ga1", devices.at(i).ga1);
            settings.setValue("ga2", devices.at(i).ga2);
            settings.setValue("ga3", devices.at(i).ga3);
            settings.setValue("sa", devices.at(i).sa);
            settings.setValue("sa1", devices.at(i).sa1);
            settings.setValue("sa2", devices.at(i).sa2);
            settings.setValue("sa3", devices.at(i).sa3);
        }
        else if (devices.at(i).type == "tagbtn") {
            settings.setValue("ga", devices.at(i).ga);
        }
    }
    settings.endArray();
    return(devices.size());    //return device list
}


void ScreenHandler::ConnectSignals()
{
    // [STAGE --> SCREENHANDLER]
    QObject::connect(m_currentScreenObj, SIGNAL(quit()),
                     this, SLOT(onQuit()), Qt::DirectConnection);

    QObject::connect(m_currentScreenObj, SIGNAL(exit(int,int)),
                     this, SLOT(onScreenChange(int,int)), Qt::DirectConnection);

    QObject::connect(m_currentScreenObj, SIGNAL(Notify(int,QString)),
            this, SLOT(onNotify(int,QString)), Qt::DirectConnection);

    QObject::connect(m_currentScreenObj, SIGNAL(sendDataToKnx(int,QString,QString,cEMI::en_cemiAction)),
            this, SLOT(onDataFromScreenObj(int,QString,QString,cEMI::en_cemiAction)), Qt::DirectConnection);

    // [SCREENHANDLER --> STAGE]
    QObject::connect(this, SIGNAL(sendDataToScreenObj(QString,QString)),
            m_currentScreenObj, SLOT(onDataFromKnx(QString,QString)), Qt::DirectConnection);

    QObject::connect(this, SIGNAL(Notify(int,QString)),
            m_currentScreenObj, SLOT(onNotify(int,QString)), Qt::DirectConnection);

    QObject::connect(this, SIGNAL(SendMsg(QString,QString)),
            m_currentScreenObj, SLOT(onMsg(QString,QString)), Qt::DirectConnection);
}


void ScreenHandler::DisconnectSignals()
{
    //OBJ --> THIS
    QObject::disconnect(m_currentScreenObj, SIGNAL(quit()),
            this, SLOT(onQuit()));

    QObject::disconnect(m_currentScreenObj, SIGNAL(exit(int,int)),
            this, SLOT(onScreenChange(int,int)));

    QObject::disconnect(m_currentScreenObj, SIGNAL(Notify(int,QString)),
            this, SLOT(onNotify(int,QString)));

    QObject::disconnect(m_currentScreenObj, SIGNAL(sendDataToKnx(int,QString,QString)),
            this, SLOT(onDataFromScreenObj(int,QString,QString)));


    //THIS --> OBJ
    QObject::disconnect(this, SIGNAL(sendDataToScreenObj(QString,QString)),
            m_currentScreenObj, SLOT(onDataFromKnx(QString,QString)));

    QObject::disconnect(this, SIGNAL(Notify(int,QString)),
            m_currentScreenObj, SLOT(onNotify(int,QString)));

    QObject::disconnect(this, SIGNAL(SendMsg(QString,QString)),
            m_currentScreenObj, SLOT(onMsg(QString,QString)));
}

