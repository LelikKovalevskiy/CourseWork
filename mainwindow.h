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

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QVBoxLayout *centralVLayout;
    QHBoxLayout *centralHLayout;
    QGraphicsView* view;
    QGraphicsScene* scene;
    QWidget *box;
    QDomDocument *domDoc;
private:
    int traverseNode(const QDomNode& node);
private slots:
    void openFile();
};

#endif // MAINWINDOW_H
