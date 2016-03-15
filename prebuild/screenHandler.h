#ifndef SCREENHANDLER_H
#define SCREENHANDLER_H

#include <QtGui/QApplication>
#include <QFile>
#include <QSettings>
#include <QObject>
#include <QDebug>
#include "common.h"
#include "stage.h"
#include "backstage.h"
#include "knxGateway.h"
#include "udpGateway.h"

class ScreenHandler : public QObject
{
    Q_OBJECT

public:
    ScreenHandler(QString iniFile);

public slots:
    void onQuit();
    void onScreenChange(int wantedScreen, int wantedSubScreen = 0);
    void onDataFromKnx(QString data);
    void onDataFromScreenObj(int type, QString groupAddr, QString value,cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);
    void onMsg(int type, QString msg);
    void onKnxStateChange(KnxGateway::en_knxGatewayState state);
    void onNotify(int notifyType, QString notifyData);
    void onKnxNotify(int notifyType, QString notifyData);
    void onAutosearchTimer();
    void onImportReplyFinished();
    void onExportReplyFinished();
    void onConnectTimer();

private:
    typedef struct {
         QString ga;
         QString ga1;
         QString ga2;
         QString ga3;
         QString ga4;
         QString sa;
         QString sa1;
         QString sa2;
         QString sa3;
         QString sa4;
         QString descr;
         QString type;
         QString tags;
         QString root;
         QString index;
     } tp_knxDevice;

    KnxGateway *m_gw;
    UdpGateway *m_ugw;
    int m_gatewayMode;
    int m_currentStage;
    QObject * m_currentScreenObj;
    QString m_conf;
    bool m_autosearch;
    QTimer m_autosearchTmr;
    QTimer m_connectTmr;
    QList<QString> m_autosearchAddr;

    //Screens & screen settings
    Stage * m_scrStage;
    Stage::tp_stageSettings m_scrStageSettings;

    Backstage * m_scrBackstage;
    Backstage::tp_backstageSettings m_scrBackstageSettings;

    QNetworkAccessManager  m_manager;
    QNetworkReply * m_importReply;
    QNetworkReply * m_exportReply;


//    bool ConnectToKnx(int mode);
//    bool DisconnectFromKnx(int mode);
    void ConnectSignals();
    void DisconnectSignals();
    void ImportRemoteConf(QString server, QString username, QString passwd, QString project);
    void ExportRemoteConf(QString server, QString username, QString passwd, QString project);
    void ClearConf(QString conf, int mode);
    QList<ScreenHandler::tp_knxDevice> GetDevicesFromConf(QString conf);
    int AppendDevice(QString conf, ScreenHandler::tp_knxDevice device);
    int RemoveDevice(QString conf, int index);
    int SaveDevicesToConf(QString conf, QList<ScreenHandler::tp_knxDevice> devices);
    int LearnBusValues();
    QString GetDeviceTags(int deviceIndex);
    int RemoveTags(QString tags);

signals:
    void SendMsg(QString title, QString msg);
    void Notify(int notifyType, QString notifyData);
    void sendDataToKnx(QString groupAddr, QString data, cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);
    void sendDataToUdp(QString groupAddr, QString data, cEMI::en_cemiAction action = cEMI::CEMI_ACTION_WRITE);
    void sendDataToScreenObj(QString groupAddr, QString data);
    void foundGateway(QString description, QString ipAddr);
    void disconnectGateway();
};

#endif // SCREENHANDLER_H
