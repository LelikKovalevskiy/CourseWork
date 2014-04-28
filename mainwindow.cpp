#include "mainwindow.h"
#include "myellipse.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setMinimumSize(800,600);
    mainScene=new MyGraphicsScene(QRectF(0,0,800,600));
    view=new QGraphicsView(mainScene);
    setCentralWidget(view);
    setMouseTracking(true);
    mainScene->addItem(new myRect(QRect(100,100,100,100)));
}

MainWindow::~MainWindow()
{

}
