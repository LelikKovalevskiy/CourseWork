#include "mygraphicsscene.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QAbstractGraphicsShapeItem>
MyGraphicsScene::MyGraphicsScene(QRectF rect):QGraphicsScene(rect)
{
    buttonIsPressed=false;
}

void MyGraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        buttonIsPressed=true;
        tmpPoint=event->scenePos();
        tmpGraphicsItem=addEllipse(QRectF(tmpPoint,QSizeF(1,1)));
    }

}
void MyGraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    buttonIsPressed=false;
}

void MyGraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if(buttonIsPressed)
    {
        removeItem(tmpGraphicsItem);
        tmpGraphicsItem=addEllipse(QRectF(tmpPoint,QSizeF(event->scenePos().x()-tmpPoint.x(),event->scenePos().y()-tmpPoint.y())));
        update();
    }
}

