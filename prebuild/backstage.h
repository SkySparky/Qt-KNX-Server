#ifndef BACKSTAGE_H
#define BACKSTAGE_H

#include <QObject>
#include <QDebug>
#include <QGraphicsObject>
#include <QSettings>
#include <QFile>
#include <QHttp>
#include "qmlapplicationviewer.h"
#include "common.h"
#include "guidelegate.h"
#include "GroupAddrObject.h"
#include "cemi.h"

//QML file for this header: "qrc:/qml/prebuild/stage.qml"

class Backstage : public QObject
{
    Q_OBJECT


public:

    typedef enum {
        MENU_BACKSTAGE, //main menu screen
        MENU_MANAGE,
        MENU_ADD,
        MENU_ITEM_OPTIONS,
        MENU_RESET,
        MENU_IMPEXPORT,
        MENU_SETTINGS,
        MENU_ABOUT
    } en_menu_screen;

    typedef struct {
        QString conf;
    } tp_backstageSettings;

    Backstage(tp_backstageSettings & settings, int firstScreen = Backstage::MENU_BACKSTAGE);
    QmlApplicationViewer m_viewer;
    tp_backstageSettings m_settings;
    GuiDelegate * m_guidelegate;

private:
    QMap<QString,QString> m_groupAddresses;

public slots:
    /** @brief [SLOT] Retrieves incoming data from bus and forwards them to stage.qml
      @param address the group address
      @param value the group address data
     */
    void onDataFromKnx(QString groupAddr, QString data);

    /** @brief [SLOT] Retrieves notifications from screenhandler
      @param cmdType the command type
      @param data the command data
     */
    void onNotify(int notifyType, QString notifyData);

    /** @brief [SLOT] Retrieves notifications from backstage.qml
      @param notifyType the notification type (see: common.h)
      @param notifyData the notification data
     */
    void onQmlNotify(int notifyType, QString notifyData);

    /** @brief [SLOT] Display a messagebox on qml
      @param title the msgbox title
      @param msg the msgbox string message
     */
    void onMsg(QString title, QString msg);

signals:

    /** @brief [SIGNAL] Sends data to a KNX object
      @param type the group address type
      @param address the group address
      @param data the group address data
     */
    void sendDataToKnx(int type, QString groupAddr, QString data, cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);
    void Notify(int notifyType, QString notifyData);
    void exit(int screen, int subscreen);    //exits from this stage
    void quit();    //quits the program
    void qmlNotify(QVariant cmdtype, QVariant data);

    /** @brief [SIGNAL] Sends a message for messagebox to Stage.qml
     */
    void SendMsg(QVariant title, QVariant msg);

};
#endif // BACKSTAGE_H
