#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include "knxServer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    KnxServer * m_knxserver;

    void Init();
    void InitSignalsSlots();
    void GetNetworkInterfaces();

signals:
    void SendDataToServer(QString phyAddr, QString groupAddr, QString data);

private slots:
    void onServerData(QString groupAddr, QString data);
    void onServerLog(QString func, QString msg);
    void on_btnStart_clicked();
    void onSwitchStateChange(int state);
    void onDimStateChange(int value);
    void onDimStateReleased();
};

#endif // MAINWINDOW_H
