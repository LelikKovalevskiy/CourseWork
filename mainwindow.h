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
#include "myrect.h"
#include <QVector>
#include <QDockWidget>
#include "numberedbutton.h"
#include <QComboBox>
#include <QLabel>
#include <QSpinBox>

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
    QGraphicsScene* currentScene;
    QVector <QGraphicsScene*> scenes;
    QWidget *box;
    QVector<QDomDocument *>*domDocs;
    QDomDocument* currentDomDoc;
    QByteArray *bArray;
    QBuffer *bufferFile;
    QSvgRenderer *currentRenderer;
    QVector<QSvgRenderer*> *renderers;

    QDockWidget *frameList;
    QHBoxLayout* frameListLayout;
    QComboBox* frameBox;
    QLabel* constInfoLabel;
    QSpinBox *timeSetter;

    QVector<int> *timesBetweenFrames;


    void traverseNode(const QDomNode& node, QVector<QDomNode*>*domNodeVector, int &objectCounter);
private slots:
    void openFile();
    void saveFile();
    void updateScene();
    void addFrame();
    void setCurrentFrame(int num);
    void setTimeBetweenFrames(int time);
};

#endif // MAINWINDOW_H
