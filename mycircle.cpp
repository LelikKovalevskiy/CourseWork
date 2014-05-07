#include "mycircle.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

myCircle::myCircle(QDomNode *domNode):QGraphicsSvgItem(),domNode(domNode)
{

}
QString myCircle::getElementId()
{
    return domNode->toElement().attribute("id");
}
void myCircle::setPosAsInFile()
{
    setPos(domNode->toElement().attribute("cx").toInt()-domNode->toElement().attribute("r").toInt(),
           domNode->toElement().attribute("cy").toInt()-domNode->toElement().attribute("r").toInt());
    qDebug()<<scenePos();
}
void myCircle::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    qDebug()<<this->scenePos();
    int r=domNode->toElement().attribute("r").toInt();
    domNode->toElement().setAttribute("cx",pos().x()+r);
    domNode->toElement().setAttribute("cy",pos().y()+r);
    qDebug()<<"Current scene pos: "<<event->scenePos();
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
