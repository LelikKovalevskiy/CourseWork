#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsView>
#include <QLayout>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QMenuBar>
#include <QDomDocument>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QBuffer>
#include <QSvgRenderer>
#include <QByteArray>
#include <QGraphicsSvgItem>
#include "myview.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    QVBoxLayout *centralVLayout;
    QHBoxLayout *centralHLayout;
    myView* view;
    QGraphicsScene* scene;
    QWidget *box;
    QDomDocument *domDoc;
    QByteArray *bArray;
    QBuffer *bufferFile;
    QSvgRenderer *renderer;

    int traverseNode(const QDomNode& node);
private slots:
    void openFile();
};

#endif // MAINWINDOW_H
