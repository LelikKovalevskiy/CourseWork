#include "myrect.h"

myRect::myRect(QDomNode *domNode):myShape(domNode)
{

}
void myRect::setPosAsInFile()
{
    setPos(getDomNode()->toElement().attribute("x").toInt(),
           getDomNode()->toElement().attribute("y").toInt());
    qDebug()<<scenePos();
}
void myRect::mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )
{
    qDebug()<<this->scenePos();
    getDomNode()->toElement().setAttribute("x",pos().x());
    getDomNode()->toElement().setAttribute("y",pos().y());
    QGraphicsSvgItem::mouseReleaseEvent(event);
}
