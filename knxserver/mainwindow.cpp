#include "mainwindow.h"
#include "ui_mainwindow.h"

// QLOG_INFO()
// QLOG_TRACE()
// QLOG_DEBUG()
// QLOG_WARN()
// QLOG_ERROR()
// QLOG_FATAL()

QsLogging::Logger& logger = QsLogging::Logger::instance();  //static logger instance
static const QString fmtDateTime("yyyy-MM-dd hh:mm:ss.zzz\t");

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    // Create tray
    createActions();
    createTrayIcon();
    trayIcon->show();

    ui->setupUi(this);

    //Do connections
    connect(ui->actionQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    // Create log
    //logger = QsLogging::Logger::instance();
    logger.setLoggingLevel(QsLogging::TraceLevel);
    const QString sLogPath(QDir(qApp->applicationDirPath()).filePath("log.txt"));
    QsLogging::DestinationPtr fileDestination(
      QsLogging::DestinationFactory::MakeFileDestination(sLogPath) );
    QsLogging::DestinationPtr debugDestination(
      QsLogging::DestinationFactory::MakeDebugOutputDestination() );
    logger.addDestination(debugDestination.get());
    logger.addDestination(fileDestination.get());

    trayIcon->showMessage("GiDT KNX Server", "Program started!");

    configLoadAll();

    //Create
    m_model = new QStandardItemModel(0,3,this);
    m_model->setHorizontalHeaderItem(0, new QStandardItem(QString("Type")));
    m_model->setHorizontalHeaderItem(1, new QStandardItem(QString("Timestamp")));
    m_model->setHorizontalHeaderItem(2, new QStandardItem(QString("Message")));

    ui->tbv_Log->setModel(m_model);
    //ui->tbv_Log->horizontalHeader()->setResizeMode(QHeaderView::Stretch);
    ui->tbv_Log->setColumnWidth(0, 80);
    ui->tbv_Log->setColumnWidth(1, 150);
    ui->tbv_Log->setColumnWidth(2, ui->tbv_Log->width()-150-85);

    onLog("Program started", Common::LOG_INFO);

    QObject::connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(onAboutToQuit()));
}


// Destructor
MainWindow::~MainWindow()
{
    delete ui;
}


// Display logs in the grid (only valid logs are info, warn & error)
void MainWindow::onLog(QString msg, Common::en_log_level log_level)
{
    int show = 0;   //by default do not type anything
    if ( (log_level == Common::LOG_INFO) && (ui->chk_LogViewInfo->isChecked())) {
        QLOG_INFO() << msg;
        show |= 1;
    }
    else if ( (log_level == Common::LOG_WARN) && (ui->chk_LogViewWarnings->isChecked())) {
        QLOG_WARN() << msg;
        show |= 1;
    }
    else if ( (log_level == Common::LOG_ERROR) && (ui->chk_LogViewErrors->isChecked())) {
        QLOG_ERROR() << msg;
        show |= 1;
    }

    if (show) { //if all creteria for showing the log are valid
        QString str_type;
        if (log_level == Common::LOG_INFO) str_type = "INFO";
        if (log_level == Common::LOG_WARN) str_type = "WARN";
        if (log_level == Common::LOG_ERROR) str_type = "ERROR";

        QStandardItem * type = new QStandardItem(str_type);
        QList<QStandardItem*> items;

        items << type << new QStandardItem(QDateTime::currentDateTime().toString(fmtDateTime)) << new QStandardItem(msg);

        m_model->appendRow(items);
        ui->tbv_Log->setModel(m_model);
    }
}

// Runs before the app quits
void MainWindow::onAboutToQuit(void)
{
    onConfigSaveAll();  //save configuration
    //QLOG_INFO() << "Program exiting...";      //hangs when quit
    qDebug() << "Program exiting";
}


// Tray icon baloon info
//
void MainWindow::onTrayMessage(QString title, QString msg, int duration)
{
    trayIcon->showMessage(title, title, QSystemTrayIcon::Information, duration);
}


// Runs while the app is closing
//
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (trayIcon->isVisible()) {
        hide();
        event->ignore();
    }
}


// Create main menu actions
//
void MainWindow::createActions()
{
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()), this, SLOT(showNormal()));

    quitAction = new QAction(tr("&Quit"), this);
    connect(quitAction, SIGNAL(triggered()), qApp, SLOT(quit()));
}


void MainWindow::createTrayIcon()
{
    // Create Menu
    //
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    // Create system tray
    //
    trayIcon = new QSystemTrayIcon(this);
    connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(onTrayActivation(QSystemTrayIcon::ActivationReason)));
    trayIcon->setContextMenu(trayIconMenu);
    QString tooltip = "GiDT Knx Server v.";
    tooltip.append(SERVER_VERSION);
    trayIcon->setToolTip(tooltip);
    QIcon icon("./images/icon.png");
    trayIcon->setIcon(icon);
}


void MainWindow::onTrayActivation(QSystemTrayIcon::ActivationReason reason)
{
    if (reason == QSystemTrayIcon::DoubleClick) {
        restoreAction->trigger();
    }
}


void MainWindow::on_btn_DbConnect_clicked()
{


}


// Load the DB connection window
//
void MainWindow::on_btn_DbOpen_clicked()
{
    if (m_dbEdit.state() == QProcess::Running) {
        QMessageBox msgbox;
        msgbox.setText("SQL Browser is already running.");
        msgbox.exec();
        return;
    }

    //url example: QODBC://user:pass@localhost:3036/gidt
    QString appExec = ui->txt_toolsPath->text() + "/sqlbrowser.exe";
    QString appArgs = "QODBC://";
    appArgs.append(ui->txt_DbUsername->text());
    appArgs.append(":");
    appArgs.append(ui->txt_DbPassword->text());
    appArgs.append("@");
    appArgs.append(ui->txt_DbHost->text());
    appArgs.append("/");
    appArgs.append(ui->txt_DbName->text());

    m_dbEdit.start(appExec, QStringList() << appArgs);
}


//Load configuration parameter from the conf file
//
QString MainWindow::configLoad(QString key)
{
    QSettings settings(CONF_FILE, QSettings::IniFormat);
    return(settings.value(key).toString());
}


//Load all configuration
//
void MainWindow::configLoadAll()

{
    QSettings settings(CONF_FILE, QSettings::IniFormat);
    QString tmpStr;

    // Tools path
    ui->txt_toolsPath->setText(settings.value("tools_path").toString());


    //Log settings
    ui->chk_LogViewInfo->setChecked(settings.value("LOG/log_info").toBool());
    ui->chk_LogViewWarnings->setChecked(settings.value("LOG/log_warn").toBool());
    ui->chk_LogViewErrors->setChecked(settings.value("LOG/log_errors").toBool());
    ui->chk_LogViewAlarm->setChecked(settings.value("LOG/log_alarm").toBool());
    ui->chk_LogViewDb->setChecked(settings.value("LOG/log_db").toBool());
    ui->chk_LogViewEmailer->setChecked(settings.value("LOG/log_emailer").toBool());
    ui->chk_LogViewGeneric->setChecked(settings.value("LOG/log_generic").toBool());
    ui->chk_LogViewGsm->setChecked(settings.value("LOG/log_gsm").toBool());
    ui->chk_LogViewKnxClient->setChecked(settings.value("LOG/log_knx_client").toBool());
    ui->chk_LogViewKnxServer->setChecked(settings.value("LOG/log_knx_server").toBool());
    ui->chk_LogViewKnxUdp->setChecked(settings.value("LOG/log_knx_udp").toBool());
    ui->chk_LogViewPstn->setChecked(settings.value("LOG/log_pstn").toBool());
    ui->chk_LogViewTv->setChecked(settings.value("LOG/log_tv").toBool());

    // Database
    ui->txt_DbName->setText(settings.value("db_name").toString());
    ui->txt_DbPassword->setText(settings.value("db_passwd").toString());
    ui->txt_DbUsername->setText(settings.value("db_user").toString());
    ui->txt_DbHost->setText(settings.value("db_host").toString());
    ui->chk_DbStartUp->setChecked(settings.value("db_startup").toBool());

    // KNX Client
    tmpStr = settings.value("knxclient_gateway").toString();
    if (!tmpStr.isEmpty()) {
        ui->cbx_KnxClientGateway->addItem(tmpStr);
    }
    ui->sbx_KnxClientGwPort->setValue(settings.value("knxclient_gwport").toInt());
    ui->sbx_KnxClientLastChannel->setValue(settings.value("knxclient_lastchannel").toInt());
    ui->chk_KnxClientStartup->setChecked(settings.value("knxclient_startup").toBool());

    // KNX Server
    ui->sbx_KnxServerControlPort->setValue(settings.value("knxserver_controlport").toInt());
    ui->sbx_KnxServerDataPort->setValue(settings.value("knxserver_dataport").toInt());
    ui->chk_KnxServerStartup->setChecked(settings.value("knxserver_startup").toBool());

    // KNX Date/Time
    ui->chk_KnxSendDateTime->setChecked(settings.value("knx_dateTimeSend").toBool());
    ui->sbx_KnxDateTimePeriod->setValue(settings.value("knx_dateTimePeriod").toInt());
    ui->txt_KnxTimeAddr->setText(settings.value("knxtime_addr").toString());
    ui->txt_KnxDateAddr->setText(settings.value("knxdate_addr").toString());

    // UDP Server
    ui->sbx_KnxUdpServerControlPort->setValue(settings.value("knxudp_controlport").toInt());
    ui->sbx_KnxUdpServerDataPort->setValue(settings.value("knxudp_dataport").toInt());
    ui->chk_KnxUdpServerBroadcast->setChecked(settings.value("knxudp_broadcast").toBool());
    ui->chk_KnxUdpServerStartup->setChecked(settings.value("knxudp_startup").toBool());

}


// Save configuration parameter
void MainWindow::onConfigSave(QString key, QString param)
{
    QSettings settings(CONF_FILE, QSettings::IniFormat);
    settings.setValue(key, param);
}


// Save all configuration data
//
void MainWindow::onConfigSaveAll(void)
{
    QSettings settings(CONF_FILE, QSettings::IniFormat);

    // Tools path
    settings.setValue("tools_path", ui->txt_toolsPath->text());

    //Log settings
    settings.setValue("LOG/log_info", ui->chk_LogViewInfo->isChecked());
    settings.setValue("LOG/log_warn", ui->chk_LogViewWarnings->isChecked());
    settings.setValue("LOG/log_errors", ui->chk_LogViewErrors->isChecked());
    settings.setValue("LOG/log_alarm", ui->chk_LogViewAlarm->isChecked());
    settings.setValue("LOG/log_db", ui->chk_LogViewDb->isChecked());
    settings.setValue("LOG/log_emailer", ui->chk_LogViewEmailer->isChecked());
    settings.setValue("LOG/log_generic", ui->chk_LogViewGeneric->isChecked());
    settings.setValue("LOG/log_gsm", ui->chk_LogViewGsm->isChecked());
    settings.setValue("LOG/log_knx_client", ui->chk_LogViewKnxClient->isChecked());
    settings.setValue("LOG/log_knx_server", ui->chk_LogViewKnxServer->isChecked());
    settings.setValue("LOG/log_knx_udp", ui->chk_LogViewKnxUdp->isChecked());
    settings.setValue("LOG/log_pstn", ui->chk_LogViewPstn->isChecked());
    settings.setValue("LOG/log_tv", ui->chk_LogViewTv->isChecked());

    // Database
    settings.setValue("db_name", ui->txt_DbName->text());
    settings.setValue("db_passwd", ui->txt_DbPassword->text());
    settings.setValue("db_user", ui->txt_DbUsername->text());
    settings.setValue("db_host", ui->txt_DbHost->text());
    settings.setValue("db_startup", ui->chk_DbStartUp->isChecked());

    // KNX Client
    settings.setValue("knxclient_gateway", ui->cbx_KnxClientGateway->currentText());
    settings.setValue("knxclient_gwport", ui->sbx_KnxClientGwPort->value());
    settings.setValue("knxclient_lastchannel", ui->sbx_KnxClientLastChannel->value());
    settings.setValue("knxclient_startup", ui->chk_KnxClientStartup->isChecked());

    // KNX Server
    settings.setValue("knxserver_controlport", ui->sbx_KnxServerControlPort->value());
    settings.setValue("knxserver_dataport", ui->sbx_KnxServerDataPort->value());
    settings.setValue("knxserver_startup", ui->chk_KnxServerStartup->isChecked());


    // KNX Date/Time
    settings.setValue("knx_dateTimeSend", ui->chk_KnxSendDateTime->isChecked());
    settings.setValue("knx_dateTimePeriod", ui->sbx_KnxDateTimePeriod->value());
    settings.setValue("knxtime_addr", ui->txt_KnxTimeAddr->text());
    settings.setValue("knxdate_addr", ui->txt_KnxDateAddr->text());

    // UDP Server
    settings.setValue("knxudp_controlport", ui->sbx_KnxUdpServerControlPort->value());
    settings.setValue("knxudp_dataport", ui->sbx_KnxUdpServerDataPort->value());
    settings.setValue("knxudp_broadcast", ui->chk_KnxUdpServerBroadcast->isChecked());
    settings.setValue("knxudp_startup", ui->chk_KnxUdpServerStartup->isChecked());



}
