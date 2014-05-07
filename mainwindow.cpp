#include "mainwindow.h"
#include <QPushButton>

QVector <QDomNode*> test;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    scene=new QGraphicsScene();
    scene->setSceneRect(0,0,700,700);
    view=new myView(scene);
    centralHLayout=new QHBoxLayout;
    centralVLayout=new QVBoxLayout;
    centralHLayout->addStretch();
    centralHLayout->addWidget(view);
    centralHLayout->addStretch();

    centralVLayout->addStretch();
    centralVLayout->addLayout(centralHLayout);
    centralVLayout->addStretch();

    box=new QWidget;
    box->setLayout(centralVLayout);
    setCentralWidget(box);

    QAction* pactNew = new QAction("New File", 0);
    pactNew->setText("&New");
    pactNew->setShortcut(QKeySequence("CTRL+N"));
    pactNew->setToolTip("New Document");
    pactNew->setStatusTip("Create a new file");
    pactNew->setWhatsThis("Create a new file");
    //not connected yet

    QAction* pactOpen = new QAction("Open File", 0);
    pactOpen->setText("&Open...");
    pactOpen->setShortcut(QKeySequence("CTRL+O"));
    pactOpen->setToolTip("Open Document");
    pactOpen->setStatusTip("Open an existing file");
    pactOpen->setWhatsThis("Open an existing file");
    connect(pactOpen,SIGNAL(triggered()),this,SLOT(openFile()));


    QMenu* pmnuFile = new QMenu("&File");
    pmnuFile->addAction(pactNew);
    pmnuFile->addAction(pactOpen);
    //not connected yet
    menuBar()->addMenu(pmnuFile);



}

MainWindow::~MainWindow()
{

}

void MainWindow::openFile()
{
    QString name=QFileDialog::getOpenFileName(new QWidget(),tr("Open file"),
                                              QString(),tr("Scalable vector graphics (*.svg)"));
    if(!name.isEmpty())
    {
        QFile file(name);
        file.open(QIODevice::ReadOnly);
        domDoc=new QDomDocument;
        domDoc->setContent(&file);
        QDomElement domElement=domDoc->documentElement();
        int height=domElement.attribute("height").remove("px").toInt();
        int width=domElement.attribute("width").remove("px").toInt();
        int objectCounter=0;
        scene->setSceneRect(0,0,height,width);

        traverseNode(domElement,objectCounter);
        view->setMaximumSize(height,width);
        bArray=new QByteArray(domDoc->toByteArray());
        bufferFile=new QBuffer(bArray);
        renderer=new QSvgRenderer(*bArray);

        myCircle *tmp;
        qDebug()<<test.size();
        for(int i=0;i<objectCounter;++i)
        {
            test.at(i)->toElement().setAttribute("test","OK");
            tmp=new myCircle(test.at(i));
            tmp->setSharedRenderer(renderer);
            tmp->setElementId(tmp->getElementId());
            scene->addItem(tmp);
            tmp->setFlag(QGraphicsSvgItem::ItemIsMovable);
            tmp->setFlag(QGraphicsSvgItem::ItemIsSelectable);
            tmp->setPosAsInFile();
        }
        qDebug()<<domDoc->toString();
    }
}
void MainWindow::traverseNode(const QDomNode& node,int &objectCounter)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                    domElement.setAttribute("id",QString::number(objectCounter));
                    ++objectCounter;
                    test.push_back(new QDomNode(domNode));

                    //and save pointer to this element somewhere

            }
        }
        traverseNode(domNode,objectCounter);
        domNode = domNode.nextSibling();
    }
}
