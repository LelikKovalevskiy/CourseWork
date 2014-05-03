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
<<<<<<< HEAD
=======

>>>>>>> 044d27819c1a6542492e7bb2807ebaec2d209f6d
    QSize sizeHint()const;

signals:

public slots:

};

#endif // MYVIEW_H
