#ifndef QTKNXDESIGNER_H
#define QTKNXDESIGNER_H

#include <QtGui/QMainWindow>
#include "ui_qtknxdesigner.h"
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QTimeLine>
#include <QGraphicsItemAnimation>
#include <QGraphicsScene>

class QtKnxDesigner : public QMainWindow
{
	Q_OBJECT

public:
	QtKnxDesigner(QWidget *parent = 0, Qt::WFlags flags = 0);
	~QtKnxDesigner();

private:
	Ui::QtKnxDesignerClass ui;
	QGraphicsScene m_scene;
	QGraphicsView m_view;
};

#endif // QTKNXDESIGNER_H
