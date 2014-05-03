#include "mainwindow.h"
#include <QPushButton>


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

        QVector<myCircle*>*itemVector=new QVector<myCircle*>;
        traverseNode(domElement,itemVector,objectCounter);
        qDebug()<<itemVector->size();
        //view->setMaximumSize(height+2,width+2);
        bArray=new QByteArray(domDoc->toByteArray());
        bufferFile=new QBuffer(bArray);
        renderer=new QSvgRenderer(bufferFile);

        myCircle *tmp;
        for(int i=0;i<itemVector->size();++i) //ВЫЛЕТАЕТ
        {
            tmp=itemVector->at(i);
            tmp->setSharedRenderer(renderer);
            tmp->setElementId(tmp->getElementId());
            scene->addItem(tmp);
            tmp->setFlag(QGraphicsSvgItem::ItemIsMovable);
            tmp->setFlag(QGraphicsSvgItem::ItemIsSelectable);*/
            qDebug()<<tmp->getElementId();

        }
    }
}
void MainWindow::traverseNode(const QDomNode& node,QVector<myCircle*>*itemVector,int &objectCounter)
{
    //is not ready yet

    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                    domElement.setAttribute("id",QString::number(objectCounter));
                    //qDebug()<<domElement.tagName()<<domElement.attribute("id");
                    itemVector->push_back(new myCircle(&domElement));
                    ++objectCounter;
            }
        }
        traverseNode(domNode,itemVector,objectCounter);
        domNode = domNode.nextSibling();
    }

}
