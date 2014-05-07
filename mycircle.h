#ifndef MYCIRCLE_H
#define MYCIRCLE_H

#include <QGraphicsSvgItem>
#include <QDomDocument>

class myCircle : public QGraphicsSvgItem
{
    Q_OBJECT
public:
     myCircle(QDomNode* domNode);
     QString getElementId();
     void setPosAsInFile();
private:
     QDomNode *domNode;
protected:
     void mouseReleaseEvent ( QGraphicsSceneMouseEvent * event );





signals:

public slots:

};

#endif // MYCIRCLE_H
