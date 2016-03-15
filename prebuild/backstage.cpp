#include "backstage.h"

Backstage::Backstage(tp_backstageSettings & settings, int firstScreen) : m_settings(settings) {

    //firstScreen has the menuscreen that has to be displayed on init

    m_viewer.create();

    m_viewer.setSource(QUrl(QLatin1String("qrc:/qml/prebuild/backstage.qml")));

    m_viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    m_viewer.showExpanded();

    //QDeclarativeContext *ctxt = m_viewer.rootContext();

    QObject * rootObject = qobject_cast<QObject*>(m_viewer.rootObject());
    m_guidelegate = new GuiDelegate(&m_viewer);


    //QML --> C++
    QObject::connect(rootObject, SIGNAL(notify(int,QString)),
                        this, SLOT(onQmlNotify(int,QString)), Qt::DirectConnection);

    //C++ --> QML
    QObject::connect(this, SIGNAL(qmlNotify(QVariant,QVariant)),
                        rootObject, SLOT(onNotify(QVariant,QVariant)), Qt::DirectConnection);

    QObject::connect(this, SIGNAL(SendMsg(QVariant,QVariant)),
                        rootObject, SLOT(onMsg(QVariant,QVariant)));    //quit signal from stage.qml

    qDebug() << "[Backstage::Backstage]";
}


void Backstage:: onMsg(QString title, QString msg)
{
    emit SendMsg(QVariant(title), QVariant(msg));
}

//KNX data from m_gw -> screenHandler -> Here
//
void Backstage::onDataFromKnx(QString groupAddr, QString data)
{
    //Do something with knx data from parent
    m_groupAddresses[groupAddr] = data; //insert data to QMap
}

//Receive data from screenHandler
//
void Backstage::onNotify(int notifyType, QString notifyData)
{
    switch(notifyType) {
    case Common::NOTIFY_KNX_DESCR_RESULT:
    case Common::NOTIFY_KNX_SEARCH_RESULT: {
        QString knxip = Common::GetParam(notifyData, 1);
        emit qmlNotify(QVariant(notifyType), QVariant(knxip));
    }
        break;
    case Common::NOTIFY_SETTINGS_REQ:
    case Common::NOTIFY_AUTOSEARCH:
    case Common::NOTIFY_EDIT_DEVICE:
    case Common::NOTIFY_STAGE_SYS_TAGS:
        emit qmlNotify(QVariant(notifyType), QVariant(notifyData));
        break;
    }
}

// Receive data from QML
//
void Backstage::onQmlNotify(int notifyType, QString notifyData)
{
    qDebug() << "[Backstage::onQmlNotify] type: " << notifyType << ", data: " << notifyData;
    switch(notifyType) {
    case Common::NOTIFY_STAGE_EXIT:
        emit exit(Common::SCREEN_ID_STAGE, 0);  //Do all exit procedures
        break;
    case Common::NOTIFY_STAGE_USE_CONF: {
        QString ckey = Common::GetParam(notifyData, 1);
        QString cvalue= Common::GetParam(notifyData, 2);
        int action = Common::GetParam(notifyData, 3).toInt();
        QSettings settings(m_settings.conf, QSettings::IniFormat);
        if (action == 0) {  //read data from conf
            QString notData = ckey + "," + settings.value(ckey).toString();
            emit qmlNotify(Common::NOTIFY_STAGE_USE_CONF, notData); //send conf to qml
        }
        else if (action == 1) { //write data to conf
            settings.setValue(ckey, cvalue);  //save conf
        }

    }
        break;

    case Common::NOTIFY_STAGE_QUIT:
        emit quit();    //Do all quit procedures
        break;

    default:
        emit Notify(notifyType, notifyData); //if notification is not trapped here then send it to screenhandler
        break;
    }

}
