#include "myellipse.h"

myRect::myRect(const QRectF & rect):QGraphicsRectItem(rect){}

void myRect::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QPointF pointClicked=event->pos();
    QRectF boundRect = sceneBoundingRect();
    QPointF topLeft=mapFromScene(boundRect.topLeft());
    QPointF bottomRight=mapFromScene(boundRect.bottomRight());
    if (pointClicked.x() <= topLeft.x()+3)
        resizeDir = rdLeft;
    else if (pointClicked.x() >= bottomRight.x()-3)
        resizeDir = rdRight;
    else if (pointClicked.y() <= topLeft.y()+3)
        resizeDir = rdTop;
    else if (pointClicked.y() >= bottomRight.y()-3)
        resizeDir = rdBottom;
    else
        resizeDir = rdNone;

    QGraphicsRectItem::mousePressEvent(event);
}
void myRect::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(isSelected())
    {
        QPointF pointClicked =mapToItem(this,event->pos());
        QRectF boundRect=rect();
        switch(resizeDir)
        {
        case rdLeft:
            boundRect.setLeft(pointClicked.x());
            setRect(boundRect);
            break;
        case rdRight:
            boundRect.setRight(pointClicked.x());
            setRect(boundRect);
            break;
        case rdTop:
            boundRect.setTop(pointClicked.y());
            setRect(boundRect);
            break;
        case rdBottom:
            boundRect.setBottom(pointClicked.y());
            setRect(boundRect);
        default:
            QGraphicsRectItem::mouseMoveEvent(event);
            break;
        }

        return;
    }
    QGraphicsRectItem::mouseMoveEvent(event);
}
