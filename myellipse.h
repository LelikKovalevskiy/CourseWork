#ifndef MYELLIPSE_H
#define MYELLIPSE_H
#include <QtWidgets>

enum resiseDirection
{
    rdNone,
    rdLeft,
    rdTop,
    rdRight,
    rdBottom
};
class myRect:public QGraphicsRectItem
{
private:
    resiseDirection resizeDir;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public:
    myRect(const QRectF & rect);
};

#endif // MYELLIPSE_H
