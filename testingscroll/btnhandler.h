#ifndef BTNHANDLER_H
#define BTNHANDLER_H

#include <QDeclarativeContext>
#include <QObject>
#include <QDebug>
#include <QVariant>
#include "DataObject.h"

class BtnHandler : public QObject
{
    Q_OBJECT

public:
    BtnHandler(QDeclarativeContext *ctxt) : m_ctxt(ctxt)
    {
        //Create default screen
        m_dataList.append(new DataObject("Manage", "./images/Settings.png"));
        m_dataList.append(new DataObject("Settings", "./images/Settings.png"));
        m_dataList.append(new DataObject("About", "./images/Settings.png"));
        m_dataList.append(new DataObject("Back", "./images/Settings.png"));
        m_dataList.append(new DataObject("Exit", "./images/Settings.png"));

        m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_dataList));
    }

private:
    QDeclarativeContext * m_ctxt;
    QList<QObject*> m_dataList;

public slots:
    //Handles the incoming data from QML
    void onBtnPressed(QString btn) {
        qDebug() << "[GuiDelegate::onBtnPressed]: btn= " << btn;
        if (btn == "Manage") {
            m_dataList.clear();
            m_dataList.append(new DataObject("Add", "./images/Settings.png"));
            m_dataList.append(new DataObject("Reset", "./images/Settings.png"));
            m_dataList.append(new DataObject("Import", "./images/Settings.png"));
            m_dataList.append(new DataObject("Export", "./images/Settings.png"));
            m_dataList.append(new DataObject("Back", "./images/Settings.png"));
        }
        else if (btn == "Settings") {
            m_dataList.clear();
            m_dataList.append(new DataObject("Gateway IP", "./images/Settings.png"));
            m_dataList.append(new DataObject("Local Port", "./images/Settings.png"));
            m_dataList.append(new DataObject("Autosearch", "./images/Settings.png"));
            m_dataList.append(new DataObject("DDNS IP", "./images/Settings.png"));
            m_dataList.append(new DataObject("DDNS Port", "./images/Settings.png"));
            m_dataList.append(new DataObject("Save", "./images/Settings.png"));
            m_dataList.append(new DataObject("Back", "./images/Settings.png"));

        }
        else if (btn == "Back") {
            m_dataList.clear();
            m_dataList.append(new DataObject("Manage", "./images/Settings.png"));
            m_dataList.append(new DataObject("Settings", "./images/Settings.png"));
            m_dataList.append(new DataObject("About", "./images/Settings.png"));
            m_dataList.append(new DataObject("Back", "./images/Settings.png"));
            m_dataList.append(new DataObject("Exit", "./images/Settings.png"));
        }
        else if (btn == "Exit") {
            emit quit();
        }
        else {
            return;
        }

        m_ctxt->setContextProperty("screenModel", QVariant::fromValue(m_dataList));
    }

signals:
    //The signal that's emited in QML
    void quit();
//    void SendSignalToQml(QVariant id, QVariant type, QVariant data);
};

#endif // BTNHANDLER_H
