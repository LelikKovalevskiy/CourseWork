#ifndef MYRECT_H
#define MYRECT_H
#include "myshape.h"
#include <QDebug>
#include <QGraphicsSceneMouseEvent>

class myRect:public myShape
{
    Q_OBJECT
public:
     myRect(QDomNode* domNode);
     void setPosAsInFile();
protected:
     void mouseReleaseEvent( QGraphicsSceneMouseEvent * event );

};

#endif // MYRECT_H
