#ifndef MYCIRCLE_H
#define MYCIRCLE_H

#include <QGraphicsSvgItem>
#include <QDomDocument>
#include <QMenu>
#include <QColor>
#include <QColorDialog>
#include <QPainter>
#include "myshape.h"

class myCircle : public myShape
{
    Q_OBJECT
public:
     myCircle(QDomNode* domNode);
     void setPosAsInFile();
protected:
     void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );
};

#endif // MYCIRCLE_H
