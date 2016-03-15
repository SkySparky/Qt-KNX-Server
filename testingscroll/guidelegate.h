#ifndef GUIDELEGATE_H
#define GUIDELEGATE_H

/**
  Delegate for QML UI and C++ code.
  When you want to send data to QML then call SendDataToQml(objId,objType,objStrData)
  When QML sends data then the data are handled in onDataFromQml(obj slot
*/

#include <QObject>
#include <QDebug>
#include <QVariant>
#include "qmlapplicationviewer.h"

class GuiDelegate : public QObject
{
    Q_OBJECT

public:
    GuiDelegate(QmlApplicationViewer * viewer) : m_viewer(viewer) {}
    QmlApplicationViewer * m_viewer;

    //Sends data to QML by emiting a signal
    void SendDataToQml(int objId, int objType, QString objStrData) {
        emit SendSignalToQml(QVariant(objId), QVariant(objType), QVariant(objStrData));
    }

public slots:
    //Handles the incoming data from QML
    void onDataFromQml(int objId, QString objData) {
        qDebug() << "[GuiDelegate::OnDataFromKnx]: " << objId << " : " << objData;
        //emit SendDataToQml(QVariant(1), QVariant(1), QVariant("text string"));
    }

signals:
    //The signal that's emited in QML
    void SendSignalToQml(QVariant id, QVariant type, QVariant data);
};

#endif // GUIDELEGATE_H
