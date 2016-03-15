
#include <QtCore/QCoreApplication>
#include <QTimer>
#include "gidt_module.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

    GidtModule mod(&a, "module.ini");
    mod.Enable();
	qDebug() << "What happened?";
	return a.exec();
}
