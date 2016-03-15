#include <QtGui/QApplication>
#include <QObject>
#include <QDebug>

#include "screenHandler.h"

//#define FORCE_LOAD_BACKSTAGE 1  //if you already have an ini file then comment out this to load the backstage

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    //QScopedPointer<QApplication> app(createApplication(argc, argv));
    QApplication app(argc, argv);

#if defined(Q_OS_ANDROID)
    QString iniFile = ":./qml/prebuild/conf.ini";
#else
    //QString iniFile = QDir::homePath() + "/gidt/conf.ini";
    QString iniFile = QDir::currentPath() + "/conf.ini";
#endif

    qDebug() << "inifile: " << iniFile;

//    QSettings ini(iniFile, QSettings::IniFormat);
//    qDebug() << "inifile: " << ini.fileName();
//    ini.setValue("test", "test");



#ifdef FORCE_LOAD_BACKSTAGE
    iniFile = "./dummy.ini";
#endif

    ScreenHandler screenHandler(iniFile);

    QObject::connect(qApp, SIGNAL(lastWindowClosed()), &screenHandler, SLOT(onQuit()));

    return app.exec();
}


