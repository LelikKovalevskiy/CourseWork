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
#include "mycircle.h"

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

    void traverseNode(const QDomNode& node, QVector<myCircle*>*itemVector, int &objectCounter);
private slots:
    void openFile();
};

#endif // MAINWINDOW_H
