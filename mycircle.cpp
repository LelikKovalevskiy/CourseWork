#include "mycircle.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>


myCircle::myCircle(QDomNode *domNode):myShape(domNode)
{

}
void myCircle::setPosAsInFile()
{
    setPos(getDomNode()->toElement().attribute("cx").toInt()-getDomNode()->toElement().attribute("r").toInt(),
           getDomNode()->toElement().attribute("cy").toInt()-getDomNode()->toElement().attribute("r").toInt());
    qDebug()<<scenePos();
}
void myCircle::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    qDebug()<<this->scenePos();
    int r=getDomNode()->toElement().attribute("r").toInt();
    getDomNode()->toElement().setAttribute("cx",pos().x()+r);
    getDomNode()->toElement().setAttribute("cy",pos().y()+r);
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
