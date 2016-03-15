#include "qtknxdesigner.h"

QtKnxDesigner::QtKnxDesigner(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	ui.setupUi(this);

	QGraphicsItem *item=m_scene.addEllipse(0, 0, 100, 100, QPen(), QBrush(Qt::SolidPattern));
	
	QTimeLine *timeline=new QTimeLine(3000);
	timeline->setFrameRange(0, 100);
	QGraphicsItemAnimation *animation=new QGraphicsItemAnimation;
	animation->setItem(item);
	animation->setTimeLine(timeline);
	for (int i=0; i<100; i++) {
		animation->setScaleAt(i/100.0, i/100.0, i/100.0);
	}
	connect(timeline, SIGNAL(valueChanged(qreal)), animation, SLOT(setStep(qreal)));
	timeline->start();
	

	ui.sceneView->setScene(&m_scene);
	ui.sceneView->show();

}

QtKnxDesigner::~QtKnxDesigner()
{

}
