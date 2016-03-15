#include "stage.h"


Stage::Stage(Stage::tp_stageSettings & settings) : m_settings(settings) {

    m_viewer.create();
    m_viewer.setSource(QUrl(QLatin1String("qrc:/qml/prebuild/stage.qml")));
    m_viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    m_viewer.showExpanded();

    m_ctxt = m_viewer.rootContext();

    QObject * rootObject = qobject_cast<QObject*>(m_viewer.rootObject());

    //QML -> C++ connection
    QObject::connect(rootObject, SIGNAL(notify(int,QString)),
                        this, SLOT(onQmlNotify(int,QString)) ); //exit signal from stage.qml

    //C++ -> QML connection
    QObject::connect(this, SIGNAL(SendMsg(QVariant,QVariant)),
                        rootObject, SLOT(onMsg(QVariant,QVariant)));    //quit signal from stage.qml

    //Load devices from ini
    LoadDevices();

    //Display all tagbtn devices
    DisplayMainScreen();

}


void Stage::HistoryAdd(QString tag)
{
    m_menuHistory.append(tag);
}


QString Stage::HistoryRemove()
{
    QString tag;
    if (m_menuHistory.isEmpty()) tag = "./";
    else {
       m_menuHistory.removeLast();         //remove last/current entry
       if (m_menuHistory.isEmpty()) tag = "./";
       else tag = m_menuHistory.last();
    }
    return(tag);
}


void Stage::UpdateScreen(QString tag) {

    if (tag == "./") {
        qDebug() << "Displayscreen";
        DisplayMainScreen();
        return;
    }

    if (m_menuHistory.isEmpty()) HistoryAdd(tag);
    else if (tag != m_menuHistory.last()) HistoryAdd(tag);

    m_objList.clear();  //clear displayed list

    if (tag == "../") tag = ""; //display all

    foreach (GroupAddrObject * device, m_devices ) {
        //if the device has the tag then add it to the list
        if (device->tags().contains(tag)) {
            //Check if device is initialized other wise read group value

            m_objList.append(device);  //add to model
        }
        //qDebug() << "[Stage::UpdateScreen] device->tags(): " << device->tags();
    }

    //update model on stage.qml
    m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_objList));
}


void Stage::DisplayMainScreen()
{
    m_objList.clear();  // clear list

    m_menuHistory.clear(); // clear history

    //Add the all root tag button
    GroupAddrObject::tp_groupAddrObj allBtn;
    allBtn.description = "All";
    allBtn.groupAddr = "../";
    allBtn.root = 1;
    allBtn.statusAddr = "";
    allBtn.tags = "";
    allBtn.type = GroupAddrObject::DEV_TAGBUTTON;
    allBtn.value = "";
    m_objList.append(new GroupAddrObject(allBtn));  //add to model

    // search for root objects
    foreach (GroupAddrObject * device, m_devices ) {
        //if the device has the tag then add it to the list
        if ( device->root() == 1) {
            m_objList.append(device);  //add to model
        }
    }

    //update model on stage.qml
    m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_objList));
}


void Stage::LoadDevices()
{
    // open config file and read all devices from in it
    QSettings settings(m_settings.conf, QSettings::IniFormat);

    m_devices.clear(); //clear list before store devices

    //scan the ini file for devices and device data
    int size = settings.beginReadArray("GroupAddresses");
    for (int i=0; i<size; i++) {    //start adding objects
        settings.setArrayIndex(i);
        GroupAddrObject::tp_groupAddrObj tmpObj; //create a new device

        //Choose correct type
        QString tmpstr = settings.value("type").toString();
        if (tmpstr == "switch") {
            tmpObj.type = GroupAddrObject::DEV_SWITCH;
            tmpObj.value = "00";
        }
        else if (tmpstr == "dimmer") {
            tmpObj.type = GroupAddrObject::DEV_DIMMER;
            tmpObj.value = "00 00";
            tmpObj.value1 = "00";
        }
        else if (tmpstr == "shutter") {
            tmpObj.type = GroupAddrObject::DEV_SHUTTER;
            tmpObj.value = "00";    //Full up/dn
            tmpObj.value1 = "00";   //Step up/dn
        }
        else if (tmpstr == "rgb") {
            tmpObj.type = GroupAddrObject::DEV_RGB;
            tmpObj.value = "00";    //on/off
            tmpObj.value1 = "00";   //R
            tmpObj.value2 = "00";   //G
            tmpObj.value3 = "00";   //B
            tmpObj.value4 = "00";   //Dim
        }
        else if (tmpstr == "tagbtn") {
            tmpObj.type = GroupAddrObject::DEV_TAGBUTTON;
        }
        else if (tmpstr == "temp") {
            tmpObj.type = GroupAddrObject::DEV_TEMP;
        }

        //read device data from the ini file
        tmpObj.index = i;
        tmpObj.root = settings.value("root", "0").toInt();
        tmpObj.description = settings.value("descr").toString();
        tmpObj.tags = settings.value("tags").toString();

        tmpObj.groupAddr = settings.value("ga").toString();
        tmpObj.groupAddr1 = settings.value("ga1").toString();
        tmpObj.groupAddr2 = settings.value("ga2").toString();
        tmpObj.groupAddr3 = settings.value("ga3").toString();
        tmpObj.groupAddr4 = settings.value("ga4").toString();

        tmpObj.statusAddr = settings.value("sa").toString();
        tmpObj.statusAddr1 = settings.value("sa1").toString();
        tmpObj.statusAddr2 = settings.value("sa2").toString();
        tmpObj.statusAddr3 = settings.value("sa3").toString();
        tmpObj.statusAddr4 = settings.value("sa4").toString();

        //emit sendDataToKnx(tmpObj.type, tmpObj.groupAddr, tmpObj.value, cEMI::CEMI_ACTION_READ);
        m_devices.append(new GroupAddrObject(tmpObj));   //store device  
    }
}


void Stage::onQmlNotify(int notifyType, QString notifyData)
{
    qDebug() << "[Stage::onQmlNotify] notifyType: " << notifyType << ", notifyData: " << notifyData;
    switch(notifyType) {
    case Common::NOTIFY_STAGE_BACK:
        UpdateScreen(HistoryRemove()); // display new last entry
        break;

    case Common::NOTIFY_EDIT_DEVICE: {
        QString devIndex = Common::GetParam(notifyData, 1);
        if (!devIndex.isEmpty())
            emit Notify(Common::NOTIFY_EDIT_DEVICE, devIndex);
    }
        break;

    case Common::NOTIFY_STAGE_EXIT:
        emit exit(Common::SCREEN_ID_BACKSTAGE, 0);  //Do all exit procedures
        break;

    case Common::NOTIFY_STAGE_RECONNECT:
        emit exit(Common::SCREEN_ID_STAGE, 5); //reconnect
        break;

    case Common::NOTIFY_STAGE_UPDATE_SCREEN: {
        QString tag = Common::GetParam(notifyData, 1);
        UpdateScreen(tag);
    }
        break;

    case Common::NOTIFY_STAGE_UPDATE_VALUE: {
        int type = Common::GetParam(notifyData, 1).toInt();
        QString ga = Common::GetParam(notifyData, 2);
        QString val = Common::GetParam(notifyData, 3);
        UiValueChanged(type, ga, val);
    }
        break;

    case Common::NOTIFY_STAGE_QUIT:
        emit quit();
        break;
    }
}


void Stage::onNotify(int notifyType, QString notifyData)
{
    switch(notifyType) {
    case Common::NOTIFY_KNX_CONNECTED: {    //learn all group addresses
        foreach (GroupAddrObject * dev, m_devices) {
            //qDebug() << "[Stage::onNotify] ";
            //GroupAddrObject * dev = qobject_cast<GroupAddrObject*>(obj);
            if (dev->type() == GroupAddrObject::DEV_SWITCH) {
                emit sendDataToKnx(dev->type(), dev->groupAddr(), dev->value(), cEMI::CEMI_ACTION_READ);
            }
            else if (dev->type() == GroupAddrObject::DEV_DIMMER) {
                emit sendDataToKnx(dev->type(), dev->groupAddr(), dev->value(), cEMI::CEMI_ACTION_READ);
                emit sendDataToKnx(dev->type(), dev->groupAddr1(), dev->value1(), cEMI::CEMI_ACTION_READ);
            }
            else if (dev->type() == GroupAddrObject::DEV_RGB) {
                emit sendDataToKnx(dev->type(), dev->groupAddr(), dev->value(), cEMI::CEMI_ACTION_READ);
                emit sendDataToKnx(dev->type(), dev->groupAddr1(), dev->value1(), cEMI::CEMI_ACTION_READ);
                emit sendDataToKnx(dev->type(), dev->groupAddr2(), dev->value2(), cEMI::CEMI_ACTION_READ);
                emit sendDataToKnx(dev->type(), dev->groupAddr3(), dev->value3(), cEMI::CEMI_ACTION_READ);
            }
            else if (dev->type() == GroupAddrObject::DEV_TEMP) {
                emit sendDataToKnx(dev->type(), dev->groupAddr(), dev->value(), cEMI::CEMI_ACTION_READ);
                emit sendDataToKnx(dev->type(), dev->statusAddr(), dev->value(), cEMI::CEMI_ACTION_READ);
            }
        }
        }
        break;
    }
}


void Stage::UiValueChanged(int type, QString groupAddr, QString data) {
    //update value
    foreach (QObject * obj, m_objList) {
        GroupAddrObject * dev = qobject_cast<GroupAddrObject*>(obj);
        if ((dev->groupAddr() == groupAddr) || (dev->statusAddr() == groupAddr)) {    //Object found
            dev->setValue(data);
            qDebug() << "[Stage::onUiValueChange]: address: " << groupAddr << ", type: " << type << ", value: " << data;
            break;
        }
        else if ((dev->groupAddr1() == groupAddr) || (dev->statusAddr1() == groupAddr)) {    //Object found
            dev->setValue1(data);
            break;
        }
        else if ((dev->groupAddr2() == groupAddr) || (dev->statusAddr2() == groupAddr)) {    //Object found
            dev->setValue2(data);
            break;
        }
        else if ((dev->groupAddr3() == groupAddr) || (dev->statusAddr3() == groupAddr)) {    //Object found
            dev->setValue3(data);
            break;
        }
        else if ((dev->groupAddr4() == groupAddr) || (dev->statusAddr4() == groupAddr)) {    //Object found
            dev->setValue4(data);
            break;
        }
    }
    emit sendDataToKnx(type, groupAddr, data);
}


void Stage:: onMsg(QString title, QString msg)
{
    emit SendMsg(QVariant(title), QVariant(msg));
}


void Stage::onDataFromKnx(QString groupAddr, QString data) {
    //Do something with data from parent

    foreach (QObject * obj, m_objList) {
        GroupAddrObject * dev = qobject_cast<GroupAddrObject*>(obj);
        if ((dev->groupAddr() == groupAddr) || (dev->statusAddr() == groupAddr)) {    //Object found
            dev->setValue(data);
            qDebug() << "[Stage::onDataFromKnx]: address: " << groupAddr << ", value: " << data;
            return;
        }
        else if ((dev->groupAddr1() == groupAddr) || (dev->statusAddr1() == groupAddr)) {    //Object found
            dev->setValue1(data);
            return;
        }
        else if ((dev->groupAddr2() == groupAddr) || (dev->statusAddr2() == groupAddr)) {    //Object found
            dev->setValue2(data);
            return;
        }
        else if ((dev->groupAddr3() == groupAddr) || (dev->statusAddr3() == groupAddr)) {    //Object found
            dev->setValue3(data);
            return;
        }
        else if ((dev->groupAddr4() == groupAddr) || (dev->statusAddr4() == groupAddr)) {    //Object found
            dev->setValue4(data);
            return;
        }
    }
}
