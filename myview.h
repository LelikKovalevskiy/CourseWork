#ifndef MYVIEW_H
#define MYVIEW_H

#include <QGraphicsView>

class myView : public QGraphicsView
{
    Q_OBJECT
public:
    myView( QGraphicsScene * scene, QWidget * parent = 0 ):QGraphicsView(scene,parent)
    {
        setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Expanding);
    }

    QSize sizeHint()const;

signals:

public slots:

};

#endif // MYVIEW_H
