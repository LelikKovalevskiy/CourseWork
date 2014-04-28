#ifndef MYGRAPHICSSCENE_H
#define MYGRAPHICSSCENE_H
#include <QGraphicsScene>

class MyGraphicsScene: public QGraphicsScene
{
    Q_OBJECT
private:
    bool buttonIsPressed;
    QPointF tmpPoint;
    QGraphicsItem* tmpGraphicsItem;
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
public:
    MyGraphicsScene(QRectF);
};

#endif // MYGRAPHICSSCENE_H
