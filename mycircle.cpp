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
}
void myCircle::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    qDebug()<<"OK!";

    int r=domNode->toElement().attribute("r").toInt();
    domNode->toElement().setAttribute("cx",event->scenePos().x()+r);
    domNode->toElement().setAttribute("cy",event->scenePos().y()+r);
    qDebug()<<"Current scene pos: "<<event->scenePos();

    QGraphicsSvgItem::mouseReleaseEvent(event);
}
