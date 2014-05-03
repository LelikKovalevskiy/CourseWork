#ifndef MYCIRCLE_H
#define MYCIRCLE_H

#include <QGraphicsSvgItem>
#include <QDomDocument>

class myCircle : public QGraphicsSvgItem
{
    Q_OBJECT
public:
     myCircle(QDomElement *domElement);
     QString getElementId();
private:
     QDomElement *domElement;




signals:

public slots:

};

#endif // MYCIRCLE_H
