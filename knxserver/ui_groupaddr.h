/********************************************************************************
** Form generated from reading UI file 'groupaddr.ui'
**
** Created: Mon 25. Jun 15:24:09 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GROUPADDR_H
#define UI_GROUPADDR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QSpinBox>
#include <QtGui/QWidget>
#include "qgroupaddr.h"

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QSpinBox *ga1;
    QSpinBox *ga2;
    QGroupAddr *ga3;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(120, 21);
        ga1 = new QSpinBox(Form);
        ga1->setObjectName(QString::fromUtf8("ga1"));
        ga1->setGeometry(QRect(0, 0, 42, 22));
        ga1->setMaximum(15);
        ga2 = new QSpinBox(Form);
        ga2->setObjectName(QString::fromUtf8("ga2"));
        ga2->setGeometry(QRect(40, 0, 42, 22));
        ga2->setMaximum(15);
        ga3 = new QGroupAddr(Form);
        ga3->setObjectName(QString::fromUtf8("ga3"));
        ga3->setGeometry(QRect(80, 0, 42, 22));
        ga3->setMaximum(255);
        ga3->setValue(0);

        retranslateUi(Form);

        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GROUPADDR_H
