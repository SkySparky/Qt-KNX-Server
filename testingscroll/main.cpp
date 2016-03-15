#include <QtGui/QApplication>
#include <QDeclarativeContext>
#include <QDebug>
#include <QGraphicsObject>

#include <QDir>

#include "qmlapplicationviewer.h"

#include "DataObject.h"
#include "guidelegate.h"
#include "btnhandler.h"
#include "devHandler.h"
#include "GroupAddrObject.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/testingscroll/main.qml"));
    viewer.showExpanded();

    //qDebug() << "Staring";


    QDeclarativeContext *ctxt = viewer.rootContext();

    QObject * rootObject = qobject_cast<QObject*>(viewer.rootObject());

//    //Create the QML/C++ delegate object
//    BtnHandler btnHandl(ctxt);

//    //QML -> C++ connection
//    QObject::connect(rootObject, SIGNAL(btnClicked(QString)),
//                        &btnHandl, SLOT(onBtnPressed(QString)), Qt::DirectConnection);

//    QObject::connect(&btnHandl, SIGNAL(quit()), qApp, SLOT(quit()));

    //Create the QML/C++ delegate object
    QDir dir("./");
    qDebug() << dir.absolutePath();
    DevHandler devHandler(ctxt, QString("./conf.ini"));

    //QML -> C++ connection
    QObject::connect(rootObject, SIGNAL(btnClicked(int,QString,QString)),
                        &devHandler, SLOT(onBtnPressed(int,QString,QString)), Qt::DirectConnection);

    devHandler.onChangeValue(QString("0/0/1"), "0");

    return app->exec();
}
