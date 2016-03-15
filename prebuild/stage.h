#ifndef STAGE_H
#define STAGE_H

#include <QObject>
#include <QDebug>
#include <QGraphicsObject>
#include <QDeclarativeContext>
#include <QSettings>
#include <QFile>
#include "qmlapplicationviewer.h"
#include "common.h"
#include "GroupAddrObject.h"
#include "cemi.h"

//QML file for this header: "qrc:/qml/prebuild/stage.qml"

/** \brief Stage screen object.

  Stage object interracts with stage.qml file and it's responsible for showing the
  group address objects and the scene that the user interracts with the bus. The
  stage.cpp retrieves bus data from it's parent and forwards them to the stage.qml.
  Also the stage.cpp retrieves signals from the stage.qml and forwards them to the
  parent object. No formating takes place during forwards.
  The stage.qml only updates device objects from it's list that correspond to the
  incoming data from the parent and all other data are discarded.

*/
class Stage : public QObject
{
    Q_OBJECT

public:
    typedef struct {
        QString conf;
    } tp_stageSettings;

    /** @brief Creates a stage object
      @param settings a settings structure for initialization
      */
    Stage(Stage::tp_stageSettings & settings);

private:
    tp_stageSettings m_settings;    // initialization settings for stage
    QmlApplicationViewer m_viewer;  // pointer to the stage QML object
    QDeclarativeContext *m_ctxt;    // pointer to QML context
    QList<QObject*> m_objList;      // displayed devices objects list
    QList<GroupAddrObject*> m_devices;  // all devices list
    QList<QString> m_menuHistory;   // history used for Back button

    /** @brief Loads devices from the config file
     */
    void UiValueChanged(int type, QString groupAddr, QString data);
    void LoadDevices();
    void HistoryAdd(QString tag);
    QString HistoryRemove();
    void UpdateScreen(QString tag);

public slots:

    /** @brief Displays the main screen that contains only tag buttons or root devices
     */
    void DisplayMainScreen();

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

    /** @brief [SLOT] Retrieves notifications from QML
      @param cmdType the command type
      @param data the command data
     */
    void onQmlNotify(int notifyType, QString notifyData);

    void onMsg(QString title, QString msg);

signals:

    /** @brief [SIGNAL] Sends data to a KNX object
      @param type the group address type
      @param address the group address
      @param data the group address data
     */
    void sendDataToKnx(int type, QString groupAddr, QString data, cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);

    void Notify(int notifyType, QString notifyData);

    /** @brief [SIGNAL] Sends an exit request to parent
      @param status the exit status
     */
    void exit(int screen, int subscreen);    //exits from this stage

    /** @brief [SIGNAL] Sends a quit request to parent
     */
    void quit();    //quits the program

    /** @brief [SIGNAL] Sends a message for messagebox to Stage.qml
     */
    void SendMsg(QVariant title, QVariant msg);

};

#endif // STAGE_H
