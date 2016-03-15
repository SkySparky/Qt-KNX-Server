/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Thu 28. Jun 11:02:12 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QColumnView>
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTableView>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabGeneral;
    QGroupBox *groupBox_3;
    QCheckBox *chk_LogViewDb;
    QCheckBox *chk_LogViewKnxServer;
    QCheckBox *chk_LogViewKnxClient;
    QCheckBox *chk_LogViewKnxUdp;
    QCheckBox *chk_LogViewEmailer;
    QCheckBox *chk_LogViewGsm;
    QCheckBox *chk_LogViewPstn;
    QCheckBox *chk_LogViewAlarm;
    QCheckBox *chk_LogViewTv;
    QCheckBox *chk_LogViewGeneric;
    QCheckBox *chk_LogViewInfo;
    QCheckBox *chk_LogViewWarnings;
    QCheckBox *chk_LogViewErrors;
    QGroupBox *groupBox_8;
    QRadioButton *rbn_GeneralDb;
    QRadioButton *rbn_GeneralKnxClient;
    QRadioButton *rbn_GeneralKnxServer;
    QRadioButton *rbn_GeneralEmailer;
    QRadioButton *rbn_GeneralGsm;
    QRadioButton *rbn_GeneralPstn;
    QRadioButton *rbn_GeneralAlarm;
    QRadioButton *rbn_GeneralTv;
    QLineEdit *txt_toolsPath;
    QTableView *tbv_Log;
    QWidget *tabDatabase;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *txt_DbName;
    QLineEdit *txt_DbUsername;
    QLabel *label_3;
    QLineEdit *txt_DbPassword;
    QCheckBox *chk_DbStartUp;
    QPushButton *btn_DbConnect;
    QPushButton *btn_DbOpen;
    QLineEdit *txt_DbHost;
    QLabel *label_16;
    QLabel *label_17;
    QLineEdit *txt_DbStatus;
    QGroupBox *groupBox_5;
    QColumnView *columnView_2;
    QWidget *tabKnx;
    QGroupBox *groupBox_4;
    QLabel *label_4;
    QComboBox *cbx_KnxServerInterface;
    QPushButton *btn_KnxServerStart;
    QLabel *label_11;
    QLabel *label_12;
    QSpinBox *sbx_KnxServerControlPort;
    QSpinBox *sbx_KnxServerDataPort;
    QLineEdit *txt_KnxServerControlPortCurr;
    QLineEdit *txt_KnxServerDataPortCurr;
    QCheckBox *chk_KnxServerStartup;
    QGroupBox *groupBox_6;
    QCheckBox *chk_KnxClientStartup;
    QLabel *label_5;
    QComboBox *cbx_KnxClientGateway;
    QPushButton *btn_KnxClientSearch;
    QPushButton *btn_KnxClientConnect;
    QPushButton *btn_KnxClientDisconnect;
    QLabel *label_10;
    QLabel *label_6;
    QLabel *label_15;
    QSpinBox *sbx_KnxClientGwPort;
    QSpinBox *sbx_KnxClientLastChannel;
    QLineEdit *txt_KnxClientControlPortCurr;
    QLineEdit *txt_KnxClientDataPortCurr;
    QGroupBox *groupBox_7;
    QLabel *label_13;
    QLabel *label_14;
    QSpinBox *sbx_KnxUdpServerControlPort;
    QSpinBox *sbx_KnxUdpServerDataPort;
    QCheckBox *chk_KnxUdpServerBroadcast;
    QLineEdit *txt_KnxUdpServerControlPortCurr;
    QLineEdit *txt_KnxUdpServerDataPortCurr;
    QPushButton *btn_KnxUdpServerStart;
    QCheckBox *chk_KnxUdpServerStartup;
    QGroupBox *groupBox_2;
    QCheckBox *chk_KnxSendDateTime;
    QLabel *label_7;
    QSpinBox *sbx_KnxDateTimePeriod;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *txt_KnxDateAddr;
    QLineEdit *txt_KnxTimeAddr;
    QWidget *tabEmailer;
    QWidget *tabGsmPstn;
    QWidget *tabAlarm;
    QWidget *tabTV;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(818, 557);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 801, 491));
        QFont font;
        font.setPointSize(9);
        tabWidget->setFont(font);
        tabGeneral = new QWidget();
        tabGeneral->setObjectName(QString::fromUtf8("tabGeneral"));
        groupBox_3 = new QGroupBox(tabGeneral);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 110, 781, 81));
        chk_LogViewDb = new QCheckBox(groupBox_3);
        chk_LogViewDb->setObjectName(QString::fromUtf8("chk_LogViewDb"));
        chk_LogViewDb->setGeometry(QRect(10, 50, 81, 17));
        chk_LogViewKnxServer = new QCheckBox(groupBox_3);
        chk_LogViewKnxServer->setObjectName(QString::fromUtf8("chk_LogViewKnxServer"));
        chk_LogViewKnxServer->setGeometry(QRect(100, 50, 81, 17));
        chk_LogViewKnxClient = new QCheckBox(groupBox_3);
        chk_LogViewKnxClient->setObjectName(QString::fromUtf8("chk_LogViewKnxClient"));
        chk_LogViewKnxClient->setGeometry(QRect(190, 50, 81, 17));
        chk_LogViewKnxUdp = new QCheckBox(groupBox_3);
        chk_LogViewKnxUdp->setObjectName(QString::fromUtf8("chk_LogViewKnxUdp"));
        chk_LogViewKnxUdp->setGeometry(QRect(270, 50, 70, 17));
        chk_LogViewEmailer = new QCheckBox(groupBox_3);
        chk_LogViewEmailer->setObjectName(QString::fromUtf8("chk_LogViewEmailer"));
        chk_LogViewEmailer->setGeometry(QRect(350, 50, 70, 17));
        chk_LogViewGsm = new QCheckBox(groupBox_3);
        chk_LogViewGsm->setObjectName(QString::fromUtf8("chk_LogViewGsm"));
        chk_LogViewGsm->setGeometry(QRect(420, 50, 51, 17));
        chk_LogViewPstn = new QCheckBox(groupBox_3);
        chk_LogViewPstn->setObjectName(QString::fromUtf8("chk_LogViewPstn"));
        chk_LogViewPstn->setGeometry(QRect(480, 50, 51, 17));
        chk_LogViewAlarm = new QCheckBox(groupBox_3);
        chk_LogViewAlarm->setObjectName(QString::fromUtf8("chk_LogViewAlarm"));
        chk_LogViewAlarm->setGeometry(QRect(540, 50, 61, 17));
        chk_LogViewTv = new QCheckBox(groupBox_3);
        chk_LogViewTv->setObjectName(QString::fromUtf8("chk_LogViewTv"));
        chk_LogViewTv->setGeometry(QRect(610, 50, 41, 17));
        chk_LogViewGeneric = new QCheckBox(groupBox_3);
        chk_LogViewGeneric->setObjectName(QString::fromUtf8("chk_LogViewGeneric"));
        chk_LogViewGeneric->setGeometry(QRect(660, 50, 70, 17));
        chk_LogViewInfo = new QCheckBox(groupBox_3);
        chk_LogViewInfo->setObjectName(QString::fromUtf8("chk_LogViewInfo"));
        chk_LogViewInfo->setGeometry(QRect(10, 20, 61, 17));
        chk_LogViewWarnings = new QCheckBox(groupBox_3);
        chk_LogViewWarnings->setObjectName(QString::fromUtf8("chk_LogViewWarnings"));
        chk_LogViewWarnings->setGeometry(QRect(100, 20, 70, 17));
        chk_LogViewErrors = new QCheckBox(groupBox_3);
        chk_LogViewErrors->setObjectName(QString::fromUtf8("chk_LogViewErrors"));
        chk_LogViewErrors->setGeometry(QRect(190, 20, 70, 17));
        groupBox_8 = new QGroupBox(tabGeneral);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 10, 781, 101));
        rbn_GeneralDb = new QRadioButton(groupBox_8);
        rbn_GeneralDb->setObjectName(QString::fromUtf8("rbn_GeneralDb"));
        rbn_GeneralDb->setGeometry(QRect(20, 30, 82, 17));
        rbn_GeneralDb->setCheckable(false);
        rbn_GeneralKnxClient = new QRadioButton(groupBox_8);
        rbn_GeneralKnxClient->setObjectName(QString::fromUtf8("rbn_GeneralKnxClient"));
        rbn_GeneralKnxClient->setGeometry(QRect(20, 60, 82, 17));
        rbn_GeneralKnxClient->setCheckable(false);
        rbn_GeneralKnxServer = new QRadioButton(groupBox_8);
        rbn_GeneralKnxServer->setObjectName(QString::fromUtf8("rbn_GeneralKnxServer"));
        rbn_GeneralKnxServer->setGeometry(QRect(120, 30, 82, 17));
        rbn_GeneralKnxServer->setCheckable(false);
        rbn_GeneralEmailer = new QRadioButton(groupBox_8);
        rbn_GeneralEmailer->setObjectName(QString::fromUtf8("rbn_GeneralEmailer"));
        rbn_GeneralEmailer->setGeometry(QRect(120, 60, 82, 17));
        rbn_GeneralEmailer->setCheckable(false);
        rbn_GeneralGsm = new QRadioButton(groupBox_8);
        rbn_GeneralGsm->setObjectName(QString::fromUtf8("rbn_GeneralGsm"));
        rbn_GeneralGsm->setGeometry(QRect(220, 30, 82, 17));
        rbn_GeneralGsm->setCheckable(false);
        rbn_GeneralPstn = new QRadioButton(groupBox_8);
        rbn_GeneralPstn->setObjectName(QString::fromUtf8("rbn_GeneralPstn"));
        rbn_GeneralPstn->setGeometry(QRect(220, 60, 82, 17));
        rbn_GeneralPstn->setCheckable(false);
        rbn_GeneralAlarm = new QRadioButton(groupBox_8);
        rbn_GeneralAlarm->setObjectName(QString::fromUtf8("rbn_GeneralAlarm"));
        rbn_GeneralAlarm->setGeometry(QRect(320, 30, 82, 17));
        rbn_GeneralAlarm->setCheckable(false);
        rbn_GeneralTv = new QRadioButton(groupBox_8);
        rbn_GeneralTv->setObjectName(QString::fromUtf8("rbn_GeneralTv"));
        rbn_GeneralTv->setGeometry(QRect(320, 60, 82, 17));
        rbn_GeneralTv->setCheckable(false);
        txt_toolsPath = new QLineEdit(groupBox_8);
        txt_toolsPath->setObjectName(QString::fromUtf8("txt_toolsPath"));
        txt_toolsPath->setGeometry(QRect(450, 30, 231, 20));
        tbv_Log = new QTableView(tabGeneral);
        tbv_Log->setObjectName(QString::fromUtf8("tbv_Log"));
        tbv_Log->setGeometry(QRect(10, 200, 781, 261));
        tbv_Log->verticalHeader()->setVisible(false);
        tabWidget->addTab(tabGeneral, QString());
        tabDatabase = new QWidget();
        tabDatabase->setObjectName(QString::fromUtf8("tabDatabase"));
        groupBox = new QGroupBox(tabDatabase);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 781, 141));
        QFont font1;
        font1.setPointSize(10);
        groupBox->setFont(font1);
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 20, 61, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 50, 81, 16));
        txt_DbName = new QLineEdit(groupBox);
        txt_DbName->setObjectName(QString::fromUtf8("txt_DbName"));
        txt_DbName->setGeometry(QRect(80, 20, 113, 20));
        txt_DbUsername = new QLineEdit(groupBox);
        txt_DbUsername->setObjectName(QString::fromUtf8("txt_DbUsername"));
        txt_DbUsername->setGeometry(QRect(80, 50, 113, 20));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 80, 71, 16));
        txt_DbPassword = new QLineEdit(groupBox);
        txt_DbPassword->setObjectName(QString::fromUtf8("txt_DbPassword"));
        txt_DbPassword->setGeometry(QRect(80, 80, 113, 20));
        chk_DbStartUp = new QCheckBox(groupBox);
        chk_DbStartUp->setObjectName(QString::fromUtf8("chk_DbStartUp"));
        chk_DbStartUp->setGeometry(QRect(230, 20, 131, 17));
        btn_DbConnect = new QPushButton(groupBox);
        btn_DbConnect->setObjectName(QString::fromUtf8("btn_DbConnect"));
        btn_DbConnect->setGeometry(QRect(230, 50, 131, 23));
        btn_DbOpen = new QPushButton(groupBox);
        btn_DbOpen->setObjectName(QString::fromUtf8("btn_DbOpen"));
        btn_DbOpen->setGeometry(QRect(230, 80, 131, 23));
        txt_DbHost = new QLineEdit(groupBox);
        txt_DbHost->setObjectName(QString::fromUtf8("txt_DbHost"));
        txt_DbHost->setGeometry(QRect(80, 110, 113, 20));
        label_16 = new QLabel(groupBox);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 110, 71, 16));
        label_17 = new QLabel(groupBox);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(410, 20, 51, 16));
        label_17->setFrameShadow(QFrame::Plain);
        txt_DbStatus = new QLineEdit(groupBox);
        txt_DbStatus->setObjectName(QString::fromUtf8("txt_DbStatus"));
        txt_DbStatus->setEnabled(false);
        txt_DbStatus->setGeometry(QRect(460, 20, 113, 20));
        groupBox_5 = new QGroupBox(tabDatabase);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(10, 160, 781, 301));
        columnView_2 = new QColumnView(groupBox_5);
        columnView_2->setObjectName(QString::fromUtf8("columnView_2"));
        columnView_2->setGeometry(QRect(5, 21, 771, 271));
        tabWidget->addTab(tabDatabase, QString());
        tabKnx = new QWidget();
        tabKnx->setObjectName(QString::fromUtf8("tabKnx"));
        groupBox_4 = new QGroupBox(tabKnx);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(390, 10, 371, 191));
        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(30, 30, 61, 16));
        cbx_KnxServerInterface = new QComboBox(groupBox_4);
        cbx_KnxServerInterface->setObjectName(QString::fromUtf8("cbx_KnxServerInterface"));
        cbx_KnxServerInterface->setGeometry(QRect(110, 30, 131, 22));
        btn_KnxServerStart = new QPushButton(groupBox_4);
        btn_KnxServerStart->setObjectName(QString::fromUtf8("btn_KnxServerStart"));
        btn_KnxServerStart->setGeometry(QRect(260, 30, 101, 81));
        label_11 = new QLabel(groupBox_4);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(30, 60, 71, 16));
        label_12 = new QLabel(groupBox_4);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(30, 90, 71, 16));
        sbx_KnxServerControlPort = new QSpinBox(groupBox_4);
        sbx_KnxServerControlPort->setObjectName(QString::fromUtf8("sbx_KnxServerControlPort"));
        sbx_KnxServerControlPort->setGeometry(QRect(110, 60, 61, 22));
        sbx_KnxServerControlPort->setMaximum(65535);
        sbx_KnxServerDataPort = new QSpinBox(groupBox_4);
        sbx_KnxServerDataPort->setObjectName(QString::fromUtf8("sbx_KnxServerDataPort"));
        sbx_KnxServerDataPort->setGeometry(QRect(110, 90, 61, 22));
        sbx_KnxServerDataPort->setMaximum(65535);
        txt_KnxServerControlPortCurr = new QLineEdit(groupBox_4);
        txt_KnxServerControlPortCurr->setObjectName(QString::fromUtf8("txt_KnxServerControlPortCurr"));
        txt_KnxServerControlPortCurr->setGeometry(QRect(180, 60, 61, 20));
        txt_KnxServerControlPortCurr->setReadOnly(true);
        txt_KnxServerDataPortCurr = new QLineEdit(groupBox_4);
        txt_KnxServerDataPortCurr->setObjectName(QString::fromUtf8("txt_KnxServerDataPortCurr"));
        txt_KnxServerDataPortCurr->setGeometry(QRect(180, 90, 61, 20));
        txt_KnxServerDataPortCurr->setReadOnly(true);
        chk_KnxServerStartup = new QCheckBox(groupBox_4);
        chk_KnxServerStartup->setObjectName(QString::fromUtf8("chk_KnxServerStartup"));
        chk_KnxServerStartup->setGeometry(QRect(30, 120, 131, 17));
        groupBox_6 = new QGroupBox(tabKnx);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 10, 371, 191));
        chk_KnxClientStartup = new QCheckBox(groupBox_6);
        chk_KnxClientStartup->setObjectName(QString::fromUtf8("chk_KnxClientStartup"));
        chk_KnxClientStartup->setGeometry(QRect(10, 150, 131, 17));
        label_5 = new QLabel(groupBox_6);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 60, 61, 16));
        cbx_KnxClientGateway = new QComboBox(groupBox_6);
        cbx_KnxClientGateway->setObjectName(QString::fromUtf8("cbx_KnxClientGateway"));
        cbx_KnxClientGateway->setGeometry(QRect(100, 60, 131, 22));
        cbx_KnxClientGateway->setEditable(true);
        btn_KnxClientSearch = new QPushButton(groupBox_6);
        btn_KnxClientSearch->setObjectName(QString::fromUtf8("btn_KnxClientSearch"));
        btn_KnxClientSearch->setGeometry(QRect(250, 60, 101, 23));
        btn_KnxClientConnect = new QPushButton(groupBox_6);
        btn_KnxClientConnect->setObjectName(QString::fromUtf8("btn_KnxClientConnect"));
        btn_KnxClientConnect->setGeometry(QRect(250, 90, 101, 23));
        btn_KnxClientDisconnect = new QPushButton(groupBox_6);
        btn_KnxClientDisconnect->setObjectName(QString::fromUtf8("btn_KnxClientDisconnect"));
        btn_KnxClientDisconnect->setGeometry(QRect(250, 120, 101, 23));
        label_10 = new QLabel(groupBox_6);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 90, 81, 16));
        label_6 = new QLabel(groupBox_6);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 120, 81, 16));
        label_15 = new QLabel(groupBox_6);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 30, 46, 13));
        sbx_KnxClientGwPort = new QSpinBox(groupBox_6);
        sbx_KnxClientGwPort->setObjectName(QString::fromUtf8("sbx_KnxClientGwPort"));
        sbx_KnxClientGwPort->setGeometry(QRect(100, 90, 61, 22));
        sbx_KnxClientGwPort->setMaximum(65535);
        sbx_KnxClientLastChannel = new QSpinBox(groupBox_6);
        sbx_KnxClientLastChannel->setObjectName(QString::fromUtf8("sbx_KnxClientLastChannel"));
        sbx_KnxClientLastChannel->setGeometry(QRect(100, 120, 61, 22));
        sbx_KnxClientLastChannel->setMaximum(65535);
        txt_KnxClientControlPortCurr = new QLineEdit(groupBox_6);
        txt_KnxClientControlPortCurr->setObjectName(QString::fromUtf8("txt_KnxClientControlPortCurr"));
        txt_KnxClientControlPortCurr->setGeometry(QRect(170, 90, 61, 20));
        txt_KnxClientControlPortCurr->setReadOnly(true);
        txt_KnxClientDataPortCurr = new QLineEdit(groupBox_6);
        txt_KnxClientDataPortCurr->setObjectName(QString::fromUtf8("txt_KnxClientDataPortCurr"));
        txt_KnxClientDataPortCurr->setGeometry(QRect(170, 120, 61, 20));
        txt_KnxClientDataPortCurr->setReadOnly(true);
        groupBox_7 = new QGroupBox(tabKnx);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(390, 210, 371, 181));
        label_13 = new QLabel(groupBox_7);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(30, 30, 71, 16));
        label_14 = new QLabel(groupBox_7);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(30, 60, 71, 16));
        sbx_KnxUdpServerControlPort = new QSpinBox(groupBox_7);
        sbx_KnxUdpServerControlPort->setObjectName(QString::fromUtf8("sbx_KnxUdpServerControlPort"));
        sbx_KnxUdpServerControlPort->setGeometry(QRect(110, 30, 61, 22));
        sbx_KnxUdpServerControlPort->setMaximum(65535);
        sbx_KnxUdpServerDataPort = new QSpinBox(groupBox_7);
        sbx_KnxUdpServerDataPort->setObjectName(QString::fromUtf8("sbx_KnxUdpServerDataPort"));
        sbx_KnxUdpServerDataPort->setGeometry(QRect(110, 60, 61, 22));
        sbx_KnxUdpServerDataPort->setMaximum(65535);
        chk_KnxUdpServerBroadcast = new QCheckBox(groupBox_7);
        chk_KnxUdpServerBroadcast->setObjectName(QString::fromUtf8("chk_KnxUdpServerBroadcast"));
        chk_KnxUdpServerBroadcast->setGeometry(QRect(30, 90, 121, 17));
        txt_KnxUdpServerControlPortCurr = new QLineEdit(groupBox_7);
        txt_KnxUdpServerControlPortCurr->setObjectName(QString::fromUtf8("txt_KnxUdpServerControlPortCurr"));
        txt_KnxUdpServerControlPortCurr->setGeometry(QRect(180, 30, 61, 20));
        txt_KnxUdpServerControlPortCurr->setReadOnly(true);
        txt_KnxUdpServerDataPortCurr = new QLineEdit(groupBox_7);
        txt_KnxUdpServerDataPortCurr->setObjectName(QString::fromUtf8("txt_KnxUdpServerDataPortCurr"));
        txt_KnxUdpServerDataPortCurr->setGeometry(QRect(180, 60, 61, 20));
        txt_KnxUdpServerDataPortCurr->setReadOnly(true);
        btn_KnxUdpServerStart = new QPushButton(groupBox_7);
        btn_KnxUdpServerStart->setObjectName(QString::fromUtf8("btn_KnxUdpServerStart"));
        btn_KnxUdpServerStart->setGeometry(QRect(260, 30, 101, 81));
        chk_KnxUdpServerStartup = new QCheckBox(groupBox_7);
        chk_KnxUdpServerStartup->setObjectName(QString::fromUtf8("chk_KnxUdpServerStartup"));
        chk_KnxUdpServerStartup->setGeometry(QRect(30, 120, 131, 17));
        groupBox_2 = new QGroupBox(tabKnx);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 210, 371, 181));
        chk_KnxSendDateTime = new QCheckBox(groupBox_2);
        chk_KnxSendDateTime->setObjectName(QString::fromUtf8("chk_KnxSendDateTime"));
        chk_KnxSendDateTime->setGeometry(QRect(10, 30, 121, 17));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 30, 81, 16));
        sbx_KnxDateTimePeriod = new QSpinBox(groupBox_2);
        sbx_KnxDateTimePeriod->setObjectName(QString::fromUtf8("sbx_KnxDateTimePeriod"));
        sbx_KnxDateTimePeriod->setGeometry(QRect(230, 30, 51, 22));
        sbx_KnxDateTimePeriod->setMaximum(1200);
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 90, 121, 16));
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 60, 121, 16));
        txt_KnxDateAddr = new QLineEdit(groupBox_2);
        txt_KnxDateAddr->setObjectName(QString::fromUtf8("txt_KnxDateAddr"));
        txt_KnxDateAddr->setGeometry(QRect(130, 90, 61, 20));
        txt_KnxTimeAddr = new QLineEdit(groupBox_2);
        txt_KnxTimeAddr->setObjectName(QString::fromUtf8("txt_KnxTimeAddr"));
        txt_KnxTimeAddr->setGeometry(QRect(130, 60, 61, 20));
        tabWidget->addTab(tabKnx, QString());
        tabEmailer = new QWidget();
        tabEmailer->setObjectName(QString::fromUtf8("tabEmailer"));
        tabWidget->addTab(tabEmailer, QString());
        tabGsmPstn = new QWidget();
        tabGsmPstn->setObjectName(QString::fromUtf8("tabGsmPstn"));
        tabWidget->addTab(tabGsmPstn, QString());
        tabAlarm = new QWidget();
        tabAlarm->setObjectName(QString::fromUtf8("tabAlarm"));
        tabWidget->addTab(tabAlarm, QString());
        tabTV = new QWidget();
        tabTV->setObjectName(QString::fromUtf8("tabTV"));
        tabWidget->addTab(tabTV, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 818, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);
        QWidget::setTabOrder(tabWidget, rbn_GeneralDb);
        QWidget::setTabOrder(rbn_GeneralDb, rbn_GeneralKnxClient);
        QWidget::setTabOrder(rbn_GeneralKnxClient, rbn_GeneralKnxServer);
        QWidget::setTabOrder(rbn_GeneralKnxServer, rbn_GeneralEmailer);
        QWidget::setTabOrder(rbn_GeneralEmailer, rbn_GeneralGsm);
        QWidget::setTabOrder(rbn_GeneralGsm, rbn_GeneralPstn);
        QWidget::setTabOrder(rbn_GeneralPstn, rbn_GeneralAlarm);
        QWidget::setTabOrder(rbn_GeneralAlarm, rbn_GeneralTv);
        QWidget::setTabOrder(rbn_GeneralTv, chk_LogViewInfo);
        QWidget::setTabOrder(chk_LogViewInfo, chk_LogViewDb);
        QWidget::setTabOrder(chk_LogViewDb, chk_LogViewWarnings);
        QWidget::setTabOrder(chk_LogViewWarnings, chk_LogViewKnxServer);
        QWidget::setTabOrder(chk_LogViewKnxServer, chk_LogViewErrors);
        QWidget::setTabOrder(chk_LogViewErrors, chk_LogViewKnxClient);
        QWidget::setTabOrder(chk_LogViewKnxClient, chk_LogViewKnxUdp);
        QWidget::setTabOrder(chk_LogViewKnxUdp, chk_LogViewEmailer);
        QWidget::setTabOrder(chk_LogViewEmailer, chk_LogViewGsm);
        QWidget::setTabOrder(chk_LogViewGsm, chk_LogViewPstn);
        QWidget::setTabOrder(chk_LogViewPstn, chk_LogViewAlarm);
        QWidget::setTabOrder(chk_LogViewAlarm, chk_LogViewTv);
        QWidget::setTabOrder(chk_LogViewTv, chk_LogViewGeneric);
        QWidget::setTabOrder(chk_LogViewGeneric, txt_DbName);
        QWidget::setTabOrder(txt_DbName, txt_DbUsername);
        QWidget::setTabOrder(txt_DbUsername, txt_DbPassword);
        QWidget::setTabOrder(txt_DbPassword, txt_DbHost);
        QWidget::setTabOrder(txt_DbHost, chk_KnxUdpServerBroadcast);
        QWidget::setTabOrder(chk_KnxUdpServerBroadcast, btn_DbConnect);
        QWidget::setTabOrder(btn_DbConnect, btn_DbOpen);
        QWidget::setTabOrder(btn_DbOpen, txt_DbStatus);
        QWidget::setTabOrder(txt_DbStatus, columnView_2);
        QWidget::setTabOrder(columnView_2, cbx_KnxClientGateway);
        QWidget::setTabOrder(cbx_KnxClientGateway, btn_KnxClientSearch);
        QWidget::setTabOrder(btn_KnxClientSearch, btn_KnxClientConnect);
        QWidget::setTabOrder(btn_KnxClientConnect, btn_KnxClientDisconnect);
        QWidget::setTabOrder(btn_KnxClientDisconnect, sbx_KnxUdpServerControlPort);
        QWidget::setTabOrder(sbx_KnxUdpServerControlPort, sbx_KnxUdpServerDataPort);
        QWidget::setTabOrder(sbx_KnxUdpServerDataPort, chk_KnxUdpServerBroadcast);
        QWidget::setTabOrder(chk_KnxUdpServerBroadcast, txt_KnxUdpServerControlPortCurr);
        QWidget::setTabOrder(txt_KnxUdpServerControlPortCurr, txt_KnxUdpServerDataPortCurr);
        QWidget::setTabOrder(txt_KnxUdpServerDataPortCurr, btn_KnxUdpServerStart);
        QWidget::setTabOrder(btn_KnxUdpServerStart, chk_KnxUdpServerStartup);
        QWidget::setTabOrder(chk_KnxUdpServerStartup, chk_KnxSendDateTime);
        QWidget::setTabOrder(chk_KnxSendDateTime, sbx_KnxDateTimePeriod);
        QWidget::setTabOrder(sbx_KnxDateTimePeriod, txt_KnxDateAddr);
        QWidget::setTabOrder(txt_KnxDateAddr, txt_KnxTimeAddr);
        QWidget::setTabOrder(txt_KnxTimeAddr, chk_KnxServerStartup);
        QWidget::setTabOrder(chk_KnxServerStartup, txt_KnxServerDataPortCurr);
        QWidget::setTabOrder(txt_KnxServerDataPortCurr, txt_KnxServerControlPortCurr);
        QWidget::setTabOrder(txt_KnxServerControlPortCurr, sbx_KnxServerControlPort);
        QWidget::setTabOrder(sbx_KnxServerControlPort, chk_KnxClientStartup);
        QWidget::setTabOrder(chk_KnxClientStartup, cbx_KnxServerInterface);
        QWidget::setTabOrder(cbx_KnxServerInterface, btn_KnxServerStart);
        QWidget::setTabOrder(btn_KnxServerStart, sbx_KnxServerDataPort);

        menuBar->addAction(menuFile->menuAction());
        menuFile->addAction(actionQuit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "GiDT KNX Server", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Log view settings", 0, QApplication::UnicodeUTF8));
        chk_LogViewDb->setText(QApplication::translate("MainWindow", "Database", 0, QApplication::UnicodeUTF8));
        chk_LogViewKnxServer->setText(QApplication::translate("MainWindow", "KNX Server", 0, QApplication::UnicodeUTF8));
        chk_LogViewKnxClient->setText(QApplication::translate("MainWindow", "KNX Client", 0, QApplication::UnicodeUTF8));
        chk_LogViewKnxUdp->setText(QApplication::translate("MainWindow", "KNX UDP", 0, QApplication::UnicodeUTF8));
        chk_LogViewEmailer->setText(QApplication::translate("MainWindow", "Emailer", 0, QApplication::UnicodeUTF8));
        chk_LogViewGsm->setText(QApplication::translate("MainWindow", "GSM", 0, QApplication::UnicodeUTF8));
        chk_LogViewPstn->setText(QApplication::translate("MainWindow", "PSTN", 0, QApplication::UnicodeUTF8));
        chk_LogViewAlarm->setText(QApplication::translate("MainWindow", "Alarm", 0, QApplication::UnicodeUTF8));
        chk_LogViewTv->setText(QApplication::translate("MainWindow", "TV", 0, QApplication::UnicodeUTF8));
        chk_LogViewGeneric->setText(QApplication::translate("MainWindow", "Generic", 0, QApplication::UnicodeUTF8));
        chk_LogViewInfo->setText(QApplication::translate("MainWindow", "Info", 0, QApplication::UnicodeUTF8));
        chk_LogViewWarnings->setText(QApplication::translate("MainWindow", "Warnings", 0, QApplication::UnicodeUTF8));
        chk_LogViewErrors->setText(QApplication::translate("MainWindow", "Errors", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Overview", 0, QApplication::UnicodeUTF8));
        rbn_GeneralDb->setText(QApplication::translate("MainWindow", "Database", 0, QApplication::UnicodeUTF8));
        rbn_GeneralKnxClient->setText(QApplication::translate("MainWindow", "KNX Client", 0, QApplication::UnicodeUTF8));
        rbn_GeneralKnxServer->setText(QApplication::translate("MainWindow", "KNX Server", 0, QApplication::UnicodeUTF8));
        rbn_GeneralEmailer->setText(QApplication::translate("MainWindow", "Emailer", 0, QApplication::UnicodeUTF8));
        rbn_GeneralGsm->setText(QApplication::translate("MainWindow", "GSM", 0, QApplication::UnicodeUTF8));
        rbn_GeneralPstn->setText(QApplication::translate("MainWindow", "PSTN", 0, QApplication::UnicodeUTF8));
        rbn_GeneralAlarm->setText(QApplication::translate("MainWindow", "Alarm", 0, QApplication::UnicodeUTF8));
        rbn_GeneralTv->setText(QApplication::translate("MainWindow", "TV", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabGeneral), QApplication::translate("MainWindow", "General", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Database settings", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "DB Name:", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("MainWindow", "Username:", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Password:", 0, QApplication::UnicodeUTF8));
        chk_DbStartUp->setText(QApplication::translate("MainWindow", "Activate on startup", 0, QApplication::UnicodeUTF8));
        btn_DbConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        btn_DbOpen->setText(QApplication::translate("MainWindow", "Open DB", 0, QApplication::UnicodeUTF8));
        label_16->setText(QApplication::translate("MainWindow", "Host:", 0, QApplication::UnicodeUTF8));
        label_17->setText(QApplication::translate("MainWindow", "Status:", 0, QApplication::UnicodeUTF8));
        txt_DbStatus->setText(QApplication::translate("MainWindow", "Disconnected", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "DB Log", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabDatabase), QApplication::translate("MainWindow", "Database", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "KNX Server", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Interface:", 0, QApplication::UnicodeUTF8));
        btn_KnxServerStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        label_11->setText(QApplication::translate("MainWindow", "Control Port:", 0, QApplication::UnicodeUTF8));
        label_12->setText(QApplication::translate("MainWindow", "Data Port:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sbx_KnxServerControlPort->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sbx_KnxServerDataPort->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txt_KnxServerControlPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txt_KnxServerDataPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chk_KnxServerStartup->setText(QApplication::translate("MainWindow", "Activate on startup", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Client", 0, QApplication::UnicodeUTF8));
        chk_KnxClientStartup->setText(QApplication::translate("MainWindow", "Activate on startup", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "Gateway:", 0, QApplication::UnicodeUTF8));
        btn_KnxClientSearch->setText(QApplication::translate("MainWindow", "Search Gateways", 0, QApplication::UnicodeUTF8));
        btn_KnxClientConnect->setText(QApplication::translate("MainWindow", "Connect", 0, QApplication::UnicodeUTF8));
        btn_KnxClientDisconnect->setText(QApplication::translate("MainWindow", "Disconnect", 0, QApplication::UnicodeUTF8));
        label_10->setText(QApplication::translate("MainWindow", "Gateway port:", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Last channel:", 0, QApplication::UnicodeUTF8));
        label_15->setText(QApplication::translate("MainWindow", "Status:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sbx_KnxClientGwPort->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sbx_KnxClientLastChannel->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txt_KnxClientControlPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txt_KnxClientDataPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        groupBox_7->setTitle(QApplication::translate("MainWindow", "UDP Server", 0, QApplication::UnicodeUTF8));
        label_13->setText(QApplication::translate("MainWindow", "Control Port:", 0, QApplication::UnicodeUTF8));
        label_14->setText(QApplication::translate("MainWindow", "Data Port:", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        sbx_KnxUdpServerControlPort->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        sbx_KnxUdpServerDataPort->setToolTip(QApplication::translate("MainWindow", "Leave it 0 for automatic binding", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        chk_KnxUdpServerBroadcast->setText(QApplication::translate("MainWindow", "Broadcast events", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        txt_KnxUdpServerControlPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_TOOLTIP
        txt_KnxUdpServerDataPortCurr->setToolTip(QApplication::translate("MainWindow", "Current port binding that is used.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        btn_KnxUdpServerStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        chk_KnxUdpServerStartup->setText(QApplication::translate("MainWindow", "Activate on startup", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Time && Date settings", 0, QApplication::UnicodeUTF8));
        chk_KnxSendDateTime->setText(QApplication::translate("MainWindow", "Send date && time", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "Period (min):", 0, QApplication::UnicodeUTF8));
        label_8->setText(QApplication::translate("MainWindow", "Date group address:", 0, QApplication::UnicodeUTF8));
        label_9->setText(QApplication::translate("MainWindow", "Time group address:", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabKnx), QApplication::translate("MainWindow", "KNX Client/Server", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabEmailer), QApplication::translate("MainWindow", "Emailer", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabGsmPstn), QApplication::translate("MainWindow", "GSM/PSTN", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabAlarm), QApplication::translate("MainWindow", "Alarm", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tabTV), QApplication::translate("MainWindow", "TV", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
