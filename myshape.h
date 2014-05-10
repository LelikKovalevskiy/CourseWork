#ifndef MYSHAPE_H
#define MYSHAPE_H
#include <QGraphicsSvgItem>
#include <QDomDocument>
#include <QMenu>
#include <QColor>
#include <QColorDialog>
#include <QPainter>

class myShape : public QGraphicsSvgItem
{
    Q_OBJECT
public:
     myShape(QDomNode* domNode);
     QString getElementId();
     virtual void setPosAsInFile()=0;
     QDomNode* getDomNode();
private:
     QDomNode *domNode;
protected:
     virtual void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event )=0;
     void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
signals:
     void attributeChanged();
public slots:
     void setFillColor();
     void setStrokeColor();



};
#endif // MYSHAPE_H
