#include "myshape.h"

#include <QDebug>
#include <QGraphicsSceneMouseEvent>


myShape::myShape(QDomNode *domNode):QGraphicsSvgItem(),domNode(domNode)
{

}
QString myShape::getElementId()
{
    return domNode->toElement().attribute("id");
}

void myShape::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    QMenu menu;
    QAction *setFillColor = menu.addAction("Set fill color...");
    QAction *setStrokeColor = menu.addAction("Set stroke color...");
    connect(setFillColor,SIGNAL(triggered()),this,SLOT(setFillColor()));
    connect(setStrokeColor,SIGNAL(triggered()),this,SLOT(setStrokeColor()));
    QAction *selectedAction = menu.exec(event->screenPos());
    update();

}
void myShape::setFillColor()
{
    qDebug()<<"OK";
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        QDomElement element=domNode->toElement();
        element.setAttribute("fill",color.name());
        emit attributeChanged();
    }

}
void myShape::setStrokeColor()
{
    qDebug()<<"OK";
    QColor color = QColorDialog::getColor();
    if (color.isValid()) {
        QDomElement element=domNode->toElement();
        element.setAttribute("stroke",color.name());
        emit attributeChanged();
    }
}
/*void myShape::setFillOpacity()
{
    ;
}*/

QDomNode* myShape::getDomNode()
{
    return domNode;
}

