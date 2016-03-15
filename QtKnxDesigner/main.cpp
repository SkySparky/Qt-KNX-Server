#include "qtknxdesigner.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QtKnxDesigner w;
	w.show();
	return a.exec();
}
