#include "mycircle.h"
#include <QDebug>

myCircle::myCircle(QDomElement *domElement):QGraphicsSvgItem(),domElement(domElement)
{
    qDebug()<<domElement->attribute("id");
}
QString myCircle::getElementId()
{
    return domElement->attribute("id");
}
