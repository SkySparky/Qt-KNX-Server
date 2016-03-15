/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun 26. Feb 14:57:31 2012
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
#include <QtGui/QComboBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QComboBox *cbInterfaces;
    QLabel *label;
    QPushButton *btnStart;
    QGroupBox *groupBox_2;
    QCheckBox *cbxSw3;
    QLineEdit *txtSwGa3;
    QLineEdit *txtSwPhy3;
    QGroupBox *groupBox_3;
    QCheckBox *cbxSw4;
    QLineEdit *txtSwGa4;
    QLineEdit *txtSwPhy4;
    QGroupBox *groupBox_4;
    QCheckBox *cbxSw5;
    QLineEdit *txtSwGa5;
    QLineEdit *txtSwPhy5;
    QGroupBox *groupBox_5;
    QCheckBox *cbxSw6;
    QLineEdit *txtSwGa6;
    QLineEdit *txtSwPhy6;
    QGroupBox *groupBox_6;
    QLineEdit *txtDimGa1;
    QLineEdit *txtDimPhy1;
    QSlider *hzDim1;
    QLabel *lblDimVal1;
    QGroupBox *groupBox_7;
    QLineEdit *txtDimGa2;
    QLineEdit *txtDimPhy2;
    QSlider *hzDim2;
    QLabel *lblDimVal2;
    QGroupBox *groupBox_8;
    QLineEdit *txtDimGa3;
    QLineEdit *txtDimPhy3;
    QSlider *hzDim3;
    QLabel *lblDimVal3;
    QGroupBox *groupBox_9;
    QLineEdit *txtDimGa4;
    QLineEdit *txtDimPhy4;
    QSlider *hzDim4;
    QLabel *lblDimVal4;
    QGroupBox *groupBox_10;
    QCheckBox *cbxSw1;
    QLineEdit *txtSwGa1;
    QLineEdit *txtSwPhy1;
    QGroupBox *groupBox_11;
    QCheckBox *cbxSw2;
    QLineEdit *txtSwGa2;
    QLineEdit *txtSwPhy2;
    QTextEdit *txtLog;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(572, 617);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 0, 271, 121));
        cbInterfaces = new QComboBox(groupBox);
        cbInterfaces->setObjectName(QString::fromUtf8("cbInterfaces"));
        cbInterfaces->setGeometry(QRect(120, 20, 131, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 20, 61, 16));
        btnStart = new QPushButton(groupBox);
        btnStart->setObjectName(QString::fromUtf8("btnStart"));
        btnStart->setGeometry(QRect(10, 60, 241, 51));
        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 120, 131, 121));
        cbxSw3 = new QCheckBox(groupBox_2);
        cbxSw3->setObjectName(QString::fromUtf8("cbxSw3"));
        cbxSw3->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa3 = new QLineEdit(groupBox_2);
        txtSwGa3->setObjectName(QString::fromUtf8("txtSwGa3"));
        txtSwGa3->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy3 = new QLineEdit(groupBox_2);
        txtSwPhy3->setObjectName(QString::fromUtf8("txtSwPhy3"));
        txtSwPhy3->setGeometry(QRect(10, 80, 113, 20));
        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(150, 120, 131, 121));
        cbxSw4 = new QCheckBox(groupBox_3);
        cbxSw4->setObjectName(QString::fromUtf8("cbxSw4"));
        cbxSw4->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa4 = new QLineEdit(groupBox_3);
        txtSwGa4->setObjectName(QString::fromUtf8("txtSwGa4"));
        txtSwGa4->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy4 = new QLineEdit(groupBox_3);
        txtSwPhy4->setObjectName(QString::fromUtf8("txtSwPhy4"));
        txtSwPhy4->setGeometry(QRect(10, 80, 113, 20));
        groupBox_4 = new QGroupBox(centralWidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(290, 120, 131, 121));
        cbxSw5 = new QCheckBox(groupBox_4);
        cbxSw5->setObjectName(QString::fromUtf8("cbxSw5"));
        cbxSw5->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa5 = new QLineEdit(groupBox_4);
        txtSwGa5->setObjectName(QString::fromUtf8("txtSwGa5"));
        txtSwGa5->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy5 = new QLineEdit(groupBox_4);
        txtSwPhy5->setObjectName(QString::fromUtf8("txtSwPhy5"));
        txtSwPhy5->setGeometry(QRect(10, 80, 113, 20));
        groupBox_5 = new QGroupBox(centralWidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(430, 120, 131, 121));
        cbxSw6 = new QCheckBox(groupBox_5);
        cbxSw6->setObjectName(QString::fromUtf8("cbxSw6"));
        cbxSw6->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa6 = new QLineEdit(groupBox_5);
        txtSwGa6->setObjectName(QString::fromUtf8("txtSwGa6"));
        txtSwGa6->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy6 = new QLineEdit(groupBox_5);
        txtSwPhy6->setObjectName(QString::fromUtf8("txtSwPhy6"));
        txtSwPhy6->setGeometry(QRect(10, 80, 113, 20));
        groupBox_6 = new QGroupBox(centralWidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(10, 240, 131, 131));
        txtDimGa1 = new QLineEdit(groupBox_6);
        txtDimGa1->setObjectName(QString::fromUtf8("txtDimGa1"));
        txtDimGa1->setGeometry(QRect(10, 70, 113, 20));
        txtDimPhy1 = new QLineEdit(groupBox_6);
        txtDimPhy1->setObjectName(QString::fromUtf8("txtDimPhy1"));
        txtDimPhy1->setGeometry(QRect(10, 100, 113, 20));
        hzDim1 = new QSlider(groupBox_6);
        hzDim1->setObjectName(QString::fromUtf8("hzDim1"));
        hzDim1->setGeometry(QRect(10, 40, 111, 19));
        hzDim1->setMaximum(255);
        hzDim1->setOrientation(Qt::Horizontal);
        lblDimVal1 = new QLabel(groupBox_6);
        lblDimVal1->setObjectName(QString::fromUtf8("lblDimVal1"));
        lblDimVal1->setGeometry(QRect(10, 20, 46, 13));
        groupBox_7 = new QGroupBox(centralWidget);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(150, 240, 131, 131));
        txtDimGa2 = new QLineEdit(groupBox_7);
        txtDimGa2->setObjectName(QString::fromUtf8("txtDimGa2"));
        txtDimGa2->setGeometry(QRect(10, 70, 113, 20));
        txtDimPhy2 = new QLineEdit(groupBox_7);
        txtDimPhy2->setObjectName(QString::fromUtf8("txtDimPhy2"));
        txtDimPhy2->setGeometry(QRect(10, 100, 113, 20));
        hzDim2 = new QSlider(groupBox_7);
        hzDim2->setObjectName(QString::fromUtf8("hzDim2"));
        hzDim2->setGeometry(QRect(10, 40, 111, 19));
        hzDim2->setMaximum(255);
        hzDim2->setOrientation(Qt::Horizontal);
        lblDimVal2 = new QLabel(groupBox_7);
        lblDimVal2->setObjectName(QString::fromUtf8("lblDimVal2"));
        lblDimVal2->setGeometry(QRect(10, 20, 46, 13));
        groupBox_8 = new QGroupBox(centralWidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(290, 240, 131, 131));
        txtDimGa3 = new QLineEdit(groupBox_8);
        txtDimGa3->setObjectName(QString::fromUtf8("txtDimGa3"));
        txtDimGa3->setGeometry(QRect(10, 70, 113, 20));
        txtDimPhy3 = new QLineEdit(groupBox_8);
        txtDimPhy3->setObjectName(QString::fromUtf8("txtDimPhy3"));
        txtDimPhy3->setGeometry(QRect(10, 100, 113, 20));
        hzDim3 = new QSlider(groupBox_8);
        hzDim3->setObjectName(QString::fromUtf8("hzDim3"));
        hzDim3->setGeometry(QRect(10, 40, 111, 19));
        hzDim3->setMaximum(255);
        hzDim3->setOrientation(Qt::Horizontal);
        lblDimVal3 = new QLabel(groupBox_8);
        lblDimVal3->setObjectName(QString::fromUtf8("lblDimVal3"));
        lblDimVal3->setGeometry(QRect(10, 20, 46, 13));
        groupBox_9 = new QGroupBox(centralWidget);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(430, 240, 131, 131));
        txtDimGa4 = new QLineEdit(groupBox_9);
        txtDimGa4->setObjectName(QString::fromUtf8("txtDimGa4"));
        txtDimGa4->setGeometry(QRect(10, 70, 113, 20));
        txtDimPhy4 = new QLineEdit(groupBox_9);
        txtDimPhy4->setObjectName(QString::fromUtf8("txtDimPhy4"));
        txtDimPhy4->setGeometry(QRect(10, 100, 113, 20));
        hzDim4 = new QSlider(groupBox_9);
        hzDim4->setObjectName(QString::fromUtf8("hzDim4"));
        hzDim4->setGeometry(QRect(10, 40, 111, 19));
        hzDim4->setMaximum(255);
        hzDim4->setOrientation(Qt::Horizontal);
        lblDimVal4 = new QLabel(groupBox_9);
        lblDimVal4->setObjectName(QString::fromUtf8("lblDimVal4"));
        lblDimVal4->setGeometry(QRect(10, 20, 46, 13));
        groupBox_10 = new QGroupBox(centralWidget);
        groupBox_10->setObjectName(QString::fromUtf8("groupBox_10"));
        groupBox_10->setGeometry(QRect(290, 0, 131, 121));
        cbxSw1 = new QCheckBox(groupBox_10);
        cbxSw1->setObjectName(QString::fromUtf8("cbxSw1"));
        cbxSw1->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa1 = new QLineEdit(groupBox_10);
        txtSwGa1->setObjectName(QString::fromUtf8("txtSwGa1"));
        txtSwGa1->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy1 = new QLineEdit(groupBox_10);
        txtSwPhy1->setObjectName(QString::fromUtf8("txtSwPhy1"));
        txtSwPhy1->setGeometry(QRect(10, 80, 113, 20));
        groupBox_11 = new QGroupBox(centralWidget);
        groupBox_11->setObjectName(QString::fromUtf8("groupBox_11"));
        groupBox_11->setGeometry(QRect(430, 0, 131, 121));
        cbxSw2 = new QCheckBox(groupBox_11);
        cbxSw2->setObjectName(QString::fromUtf8("cbxSw2"));
        cbxSw2->setGeometry(QRect(10, 20, 70, 17));
        txtSwGa2 = new QLineEdit(groupBox_11);
        txtSwGa2->setObjectName(QString::fromUtf8("txtSwGa2"));
        txtSwGa2->setGeometry(QRect(10, 50, 113, 20));
        txtSwPhy2 = new QLineEdit(groupBox_11);
        txtSwPhy2->setObjectName(QString::fromUtf8("txtSwPhy2"));
        txtSwPhy2->setGeometry(QRect(10, 80, 113, 20));
        txtLog = new QTextEdit(centralWidget);
        txtLog->setObjectName(QString::fromUtf8("txtLog"));
        txtLog->setGeometry(QRect(10, 380, 551, 181));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 572, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("MainWindow", "Gateway Server", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Interface:", 0, QApplication::UnicodeUTF8));
        btnStart->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Switch 3", 0, QApplication::UnicodeUTF8));
        cbxSw3->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa3->setText(QApplication::translate("MainWindow", "0/0/3", 0, QApplication::UnicodeUTF8));
        txtSwPhy3->setText(QApplication::translate("MainWindow", "1.1.4", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Switch 4", 0, QApplication::UnicodeUTF8));
        cbxSw4->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa4->setText(QApplication::translate("MainWindow", "0/0/4", 0, QApplication::UnicodeUTF8));
        txtSwPhy4->setText(QApplication::translate("MainWindow", "1.1.5", 0, QApplication::UnicodeUTF8));
        groupBox_4->setTitle(QApplication::translate("MainWindow", "Switch 5", 0, QApplication::UnicodeUTF8));
        cbxSw5->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa5->setText(QApplication::translate("MainWindow", "0/0/5", 0, QApplication::UnicodeUTF8));
        txtSwPhy5->setText(QApplication::translate("MainWindow", "1.1.5", 0, QApplication::UnicodeUTF8));
        groupBox_5->setTitle(QApplication::translate("MainWindow", "Switch 6", 0, QApplication::UnicodeUTF8));
        cbxSw6->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa6->setText(QApplication::translate("MainWindow", "0/0/6", 0, QApplication::UnicodeUTF8));
        txtSwPhy6->setText(QApplication::translate("MainWindow", "1.1.5", 0, QApplication::UnicodeUTF8));
        groupBox_6->setTitle(QApplication::translate("MainWindow", "Dimmer 1", 0, QApplication::UnicodeUTF8));
        txtDimGa1->setText(QApplication::translate("MainWindow", "0/1/1", 0, QApplication::UnicodeUTF8));
        txtDimPhy1->setText(QApplication::translate("MainWindow", "1.1.6", 0, QApplication::UnicodeUTF8));
        lblDimVal1->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_7->setTitle(QApplication::translate("MainWindow", "Dimmer 2", 0, QApplication::UnicodeUTF8));
        txtDimGa2->setText(QApplication::translate("MainWindow", "0/1/2", 0, QApplication::UnicodeUTF8));
        txtDimPhy2->setText(QApplication::translate("MainWindow", "1.1.6", 0, QApplication::UnicodeUTF8));
        lblDimVal2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_8->setTitle(QApplication::translate("MainWindow", "Dimmer 3", 0, QApplication::UnicodeUTF8));
        txtDimGa3->setText(QApplication::translate("MainWindow", "0/1/3", 0, QApplication::UnicodeUTF8));
        txtDimPhy3->setText(QApplication::translate("MainWindow", "1.1.6", 0, QApplication::UnicodeUTF8));
        lblDimVal3->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_9->setTitle(QApplication::translate("MainWindow", "Dimmer 4", 0, QApplication::UnicodeUTF8));
        txtDimGa4->setText(QApplication::translate("MainWindow", "0/1/4", 0, QApplication::UnicodeUTF8));
        txtDimPhy4->setText(QApplication::translate("MainWindow", "1.1.6", 0, QApplication::UnicodeUTF8));
        lblDimVal4->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        groupBox_10->setTitle(QApplication::translate("MainWindow", "Switch 1", 0, QApplication::UnicodeUTF8));
        cbxSw1->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa1->setText(QApplication::translate("MainWindow", "0/0/1", 0, QApplication::UnicodeUTF8));
        txtSwPhy1->setText(QApplication::translate("MainWindow", "1.1.4", 0, QApplication::UnicodeUTF8));
        groupBox_11->setTitle(QApplication::translate("MainWindow", "Switch 2", 0, QApplication::UnicodeUTF8));
        cbxSw2->setText(QApplication::translate("MainWindow", "Status", 0, QApplication::UnicodeUTF8));
        txtSwGa2->setText(QApplication::translate("MainWindow", "0/0/2", 0, QApplication::UnicodeUTF8));
        txtSwPhy2->setText(QApplication::translate("MainWindow", "1.1.4", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
