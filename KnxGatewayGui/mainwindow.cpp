#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    GetNetworkInterfaces();
    Init();
    InitSignalsSlots();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::onServerData(QString groupAddr, QString data)
{
    qDebug() << "[MainWindow::onServerData] groupAddr= " << groupAddr << ", data: " << data;
    if (m_knxserver != NULL) {
       QList<QLineEdit*> obj = ui->centralWidget->findChildren<QLineEdit*>(QRegExp("txtSwGa"));
       if (obj.count() != 0) {
           for (int i=0; i<obj.count(); i++) {
               qDebug() << "ga: " << obj[i]->text();
               if (obj[i]->text() == groupAddr) {
                   QString senderId = obj[i]->text().mid(obj[i]->text().length() - 1, 1);

                   qDebug() << "QCheckBox: " << "cbxSw" << senderId;
                   QCheckBox * cbx = ui->centralWidget->findChild<QCheckBox*>("cbxSw" + senderId);
                   if (data == "80") cbx->setCheckState(Qt::Unchecked);
                   else cbx->setCheckState(Qt::Checked);
               }
           }
       }
       obj = ui->centralWidget->findChildren<QLineEdit*>(QRegExp("txtDimGa"));
       if (obj.count() != 0) {
           for (int i=0; i<obj.count(); i++) {
               qDebug() << "ga: " << obj[i]->text();
               if (obj[i]->text() == groupAddr) {
                   QString senderId = obj[i]->text().mid(obj[i]->text().length() - 1, 1);

                   qDebug() << "QCheckBox: " << "cbxSw" << senderId;
                   QSlider * cbx = ui->centralWidget->findChild<QSlider*>("hzDim" + senderId);
                   bool ok;
                   cbx->setValue(data.right(2).toInt(&ok, 16));
               }
           }
       }

    }
    qDebug() << "onServerData end";
}

void MainWindow::onServerLog(QString func, QString msg)
{
    ui->txtLog->append("\r\n" + func + " : " + msg);
}

void MainWindow::GetNetworkInterfaces()
{

    ui->cbInterfaces->clear();
    foreach(QNetworkInterface interface, QNetworkInterface::allInterfaces())
    {
        // Return only the first non-loopback MAC Address
        if (!(interface.flags() & QNetworkInterface::IsLoopBack)) {

            foreach(QNetworkAddressEntry entry, interface.addressEntries())
            {
                if (entry.ip().toString().contains("192")) ui->cbInterfaces->addItem(entry.ip().toString());
            }
        }
    }
}

void MainWindow::onSwitchStateChange(int state)
{

    QCheckBox* sender = qobject_cast<QCheckBox*>(QObject::sender());
    QString senderName = sender->objectName();
    QString senderId = sender->objectName().mid(senderName.length() - 1, 1);

    if (m_knxserver != NULL) {
       QLineEdit* obj = ui->centralWidget->findChild<QLineEdit*>("txtSwGa" + senderId);
       QString ga = obj->text();
       obj = ui->centralWidget->findChild<QLineEdit*>("txtSwPhy" + senderId);
       QString phy = obj->text();

       emit SendDataToServer(phy, ga, (state == 0) ? "80" : "81");
    }
}

void MainWindow::onDimStateChange(int value)
{
    QSlider* sender = qobject_cast<QSlider*>(QObject::sender());
    QString senderName = sender->objectName();
    QString senderId = sender->objectName().mid(senderName.length() - 1, 1);

    QLabel* lbl = ui->centralWidget->findChild<QLabel*>("lblDimVal" + senderId);
    lbl->setText(QString::number(value));
}


void MainWindow::onDimStateReleased()
{
    QSlider* sender = qobject_cast<QSlider*>(QObject::sender());
    QString senderName = sender->objectName();
    QString senderId = sender->objectName().mid(senderName.length() - 1, 1);

    if (m_knxserver != NULL) {
       QLineEdit* obj = ui->centralWidget->findChild<QLineEdit*>("txtDimGa" + senderId);
       QString ga = obj->text();
       obj = ui->centralWidget->findChild<QLineEdit*>("txtDimPhy" + senderId);
       QString phy = obj->text();

       QString val = "80 " + QString("0" + QString::number(sender->value(), 16)).right(2).toUpper();

       emit SendDataToServer(phy, ga, val);
    }
}


void MainWindow::Init()
{
    ui->cbxSw1->setChecked(false);
    ui->cbxSw2->setChecked(false);
    ui->cbxSw3->setChecked(false);
    ui->cbxSw4->setChecked(false);
    ui->cbxSw5->setChecked(false);
    ui->cbxSw6->setChecked(false);

    ui->hzDim1->setValue(0);
    ui->hzDim2->setValue(0);
    ui->hzDim3->setValue(0);
    ui->hzDim4->setValue(0);

    ui->lblDimVal1->setText("0");
    ui->lblDimVal2->setText("0");
    ui->lblDimVal3->setText("0");
    ui->lblDimVal4->setText("0");
}


void MainWindow::InitSignalsSlots()
{

    connect(ui->cbxSw1, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));
    connect(ui->cbxSw2, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));
    connect(ui->cbxSw3, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));
    connect(ui->cbxSw4, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));
    connect(ui->cbxSw5, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));
    connect(ui->cbxSw6, SIGNAL(stateChanged(int)), this, SLOT(onSwitchStateChange(int)));

    connect(ui->hzDim1, SIGNAL(sliderReleased()), this, SLOT(onDimStateReleased()));
    connect(ui->hzDim2, SIGNAL(sliderReleased()), this, SLOT(onDimStateReleased()));
    connect(ui->hzDim3, SIGNAL(sliderReleased()), this, SLOT(onDimStateReleased()));
    connect(ui->hzDim4, SIGNAL(sliderReleased()), this, SLOT(onDimStateReleased()));

    connect(ui->hzDim1, SIGNAL(valueChanged(int)), this, SLOT(onDimStateChange(int)));
    connect(ui->hzDim2, SIGNAL(valueChanged(int)), this, SLOT(onDimStateChange(int)));
    connect(ui->hzDim3, SIGNAL(valueChanged(int)), this, SLOT(onDimStateChange(int)));
    connect(ui->hzDim4, SIGNAL(valueChanged(int)), this, SLOT(onDimStateChange(int)));

}

void MainWindow::on_btnStart_clicked()
{
    if (ui->btnStart->text() == "Start") {
        ui->btnStart->setText("Stop");
        //Clear log
        ui->txtLog->clear();

        //Create server
        m_knxserver = new KnxServer(ui->cbInterfaces->currentText(), 1);
        onServerLog("GiDT Server", "Created.");
        connect(m_knxserver, SIGNAL(Log(QString,QString)), this, SLOT(onServerLog(QString,QString)));
        connect(m_knxserver, SIGNAL(GatewayData(QString,QString)), this, SLOT(onServerData(QString,QString)));
        connect(this, SIGNAL(SendDataToServer(QString,QString,QString)), m_knxserver, SLOT(onSendDataToClients(QString,QString,QString)));
        m_knxserver->Bind();
    }
    else {
        ui->btnStart->setText("Start");

        m_knxserver->Close();
        //delete server
        disconnect(m_knxserver, SIGNAL(Log(QString,QString)), this, SLOT(onServerLog(QString,QString)));
        disconnect(m_knxserver, SIGNAL(GatewayData(QString,QString)), this, SLOT(onServerData(QString,QString)));
        disconnect(this, SIGNAL(SendDataToServer(QString,QString,QString)), m_knxserver, SLOT(onSendDataToClients(QString,QString,QString)));
        m_knxserver->deleteLater();
        m_knxserver = NULL;
        onServerLog("GiDT Server", "Stopped.");
    }
}
