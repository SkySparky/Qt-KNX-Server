#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "QsLog.h"
#include "QsLogDest.h"
#include "common.h"

#include <QSystemTrayIcon>
#include <QMainWindow>
#include <QMessageBox>
#include <QObject>
#include <QCloseEvent>
#include <QProcess>
#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QStandardItemModel>
#include <QtCore/QCoreApplication>


#define SERVER_VERSION "0.1"

#define CONF_FILE "./config.ini"
#define LOG_FILE "./log.txt"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event);
    
private:

    Ui::MainWindow *ui;
    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;
    QSettings m_config;
    QProcess m_dbEdit;
    QStandardItemModel *m_model;

    void createActions();
    void createTrayIcon();
    QString configLoad(QString key);
    void configLoadAll();

public slots:
    void onTrayActivation(QSystemTrayIcon::ActivationReason reason);
    void onTrayMessage(QString title, QString msg, int duration = 5000);
    void onConfigSave(QString key, QString param);
    void onConfigSaveAll(void);
    void onAboutToQuit(void);
    void on_btn_DbConnect_clicked();
    void on_btn_DbOpen_clicked();
    void onLog(QString msg, Common::en_log_level log_level);
};

#endif // MAINWINDOW_H
