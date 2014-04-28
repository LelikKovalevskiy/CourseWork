#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include "mygraphicsscene.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    MyGraphicsScene* mainScene;
    QGraphicsView * view;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
};

#endif // MAINWINDOW_H
