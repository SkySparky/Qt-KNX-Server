#include <QtGui/QApplication>
#include <QDebug>
#include "qmlapplicationviewer.h"

#include "knxServer.h"

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;
    viewer.setOrientation(QmlApplicationViewer::ScreenOrientationAuto);
    viewer.setMainQmlFile(QLatin1String("qml/KnxServerGui/main.qml"));
    viewer.showExpanded();

    KnxServer server("./knxserver.ini");
    server.Bind();

    return app->exec();
}
