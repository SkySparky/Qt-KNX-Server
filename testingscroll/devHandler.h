#ifndef DEVHANDLER_H
#define DEVHANDLER_H


#include <QDeclarativeContext>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include <QSettings>
#include "GroupAddrObject.h"

class DevHandler : public QObject
{
    Q_OBJECT

public:
    DevHandler(QDeclarativeContext *ctxt, QString conf) : m_ctxt(ctxt), m_confFile(conf)
    {
        CreateTagsScreen();

        //Create default screen
//        m_dataList.clear();
//        m_dataList.append(new GroupAddrObject(GroupAddrObject::DEV_SWITCH, "Light 1", "0/0/1", "0"));
//        m_dataList.append(new GroupAddrObject(GroupAddrObject::DEV_DIMMER, "WC","0/1/1", "45"));
//        m_dataList.append(new GroupAddrObject(GroupAddrObject::DEV_RGB, "Color R","0/2/1", "125"));
//        m_dataList.append(new GroupAddrObject(GroupAddrObject::DEV_SHUTTER, "Light 2" ,"0/3/1", "0"));

//        m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_dataList));
    }

    void CreateTagsScreen() {
        QSettings settings(m_confFile, QSettings::IniFormat);

        m_dataList.clear(); //clear list before loading the objects

        int size = settings.beginReadArray("GroupAddresses");
        for (int i=0; i<size; i++) {    //start adding objects
            settings.setArrayIndex(i);

            //Choose correct type
            int tmpType;
            QString tmpstr = settings.value("type").toString();
            if (tmpstr == "switch") tmpType = GroupAddrObject::DEV_SWITCH;
            else if (tmpstr == "dimmer") tmpType = GroupAddrObject::DEV_DIMMER;
            else if (tmpstr == "shutter") tmpType = GroupAddrObject::DEV_SHUTTER;
            else if (tmpstr == "rgb") tmpType = GroupAddrObject::DEV_RGB;

            m_dataList.append(new GroupAddrObject(tmpType,
                              settings.value("descr").toString(),
                              settings.value("ga").toString(),
                              "0",
                              settings.value("tags").toString()));
        }
        m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_dataList));
    }

    void SaveConf() {

    }

private:
    QDeclarativeContext * m_ctxt;
    QList<QObject*> m_dataList;
    QString m_confFile;


public slots:
    //Handles the incoming data from QML
    void onBtnPressed(int type, QString address, QString value) {
        qDebug() << "[GuiDelegate::onBtnPressed]: address: " << address
                 << ", type: " << type << ", value: " << value;

        //m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_dataList));
    }

    void onChangeValue(QString groupAddr, QString value) {

        foreach (QObject * obj, m_dataList) {
            GroupAddrObject * dev = qobject_cast<GroupAddrObject*>(obj);
            if (dev->groupAddr() == groupAddr) {    //Object found
                dev->setValue(value);
            }
        }
    }
};

#endif // DEVHANDLER_H
