#include "mainwindow.h"
#include <QPushButton>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    view=new myView();
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
    setCentralWidget(view);

    QAction* pactSave = new QAction("Save file", 0);
    pactSave->setText("&Save file");
    pactSave->setShortcut(QKeySequence("CTRL+N"));
    pactSave->setToolTip("Save Document");
    pactSave->setStatusTip("Save file");
    pactSave->setWhatsThis("Save file");
    connect(pactSave,SIGNAL(triggered()),this,SLOT(saveFile()));
    //not connected yet

    QAction* pactOpen = new QAction("Open File", 0);
    pactOpen->setText("&Open...");
    pactOpen->setShortcut(QKeySequence("CTRL+O"));
    pactOpen->setToolTip("Open Document");
    pactOpen->setStatusTip("Open an existing file");
    pactOpen->setWhatsThis("Open an existing file");
    connect(pactOpen,SIGNAL(triggered()),this,SLOT(openFile()));


    QMenu* pmnuFile = new QMenu("&File");
    pmnuFile->addAction(pactSave);
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
        domDocs=new QVector<QDomDocument*>;
        file.open(QIODevice::ReadOnly);
        currentDomDoc=new QDomDocument;
        domDocs->push_back(currentDomDoc);
        currentDomDoc->setContent(&file);
        QDomElement domElement=currentDomDoc->documentElement();
        int height=domElement.attribute("height").remove("px").toInt();
        int width=domElement.attribute("width").remove("px").toInt();
        int objectCounter=0;
        currentScene=new QGraphicsScene();
        currentScene->setSceneRect(0,0,width,height);
        scenes.push_back(currentScene);
        view->setScene(currentScene);

        QVector<QDomNode*>* domNodeVector=new QVector<QDomNode*>;
        traverseNode(domElement,domNodeVector,objectCounter);
        view->setMaximumSize(width+2,height+2);
        ///
        bArray=new QByteArray(currentDomDoc->toByteArray());
        bufferFile=new QBuffer(bArray);
        currentRenderer=new QSvgRenderer(*bArray);
        renderers=new QVector<QSvgRenderer*>;
        renderers->push_back(currentRenderer);

        myShape *tmp;
        for(int i=0;i<objectCounter;++i)
        {
            if(domNodeVector->at(i)->toElement().tagName()=="circle")
            {
                tmp=new myCircle(domNodeVector->at(i));
            }
            else if(domNodeVector->at(i)->toElement().tagName()=="rect")
            {
                tmp=new myRect(domNodeVector->at(i));
            }

            connect(tmp,SIGNAL(attributeChanged()),this,SLOT(updateScene()));
            tmp->setSharedRenderer(currentRenderer);
            tmp->setElementId(tmp->getElementId());
            currentScene->addItem(tmp);
            tmp->setFlag(QGraphicsSvgItem::ItemIsMovable);
            tmp->setFlag(QGraphicsSvgItem::ItemIsSelectable);
            tmp->setPosAsInFile();
        }
        qDebug()<<currentDomDoc->toString();

        //создание кнопок, нумерующих "кадры"

        frameList=new QDockWidget();
        frameList->setFeatures(QDockWidget::NoDockWidgetFeatures);
        constInfoLabel=new QLabel("Time between this frame and previous frame: ");
        timeSetter=new QSpinBox();
        timeSetter->setMinimum(0);
        constInfoLabel->setVisible(false);
        timeSetter->setVisible(false);
        connect(timeSetter,SIGNAL(valueChanged(int)),this,SLOT(setTimeBetweenFrames(int)));

        frameBox=new QComboBox();
        QPushButton* addFrameButton=new QPushButton("+add frame");
        frameBox->setMaximumWidth(80);
        addFrameButton->setMaximumWidth(65);
        frameBox->addItem("Frame №1");

        connect(addFrameButton,SIGNAL(clicked()),this,SLOT(addFrame()));
        connect(frameBox,SIGNAL(currentIndexChanged(int)),this,SLOT(setCurrentFrame(int)));

        QWidget* box1=new QWidget;
        frameListLayout=new QHBoxLayout;
        frameListLayout->addWidget(frameBox);
        frameListLayout->addWidget(addFrameButton);
        frameListLayout->addWidget(constInfoLabel);
        frameListLayout->addWidget(timeSetter);
        box1->setLayout(frameListLayout);
        frameList->setWidget(box1);
        frameListLayout->setAlignment(Qt::AlignLeft);

        frameList->setWindowModified(false);
        addDockWidget(Qt::TopDockWidgetArea,frameList);
        //
        timesBetweenFrames=new QVector<int>;


    }
}
void MainWindow::saveFile()
{
    QString fileName=QFileDialog::getSaveFileName(new QWidget(),tr("Save file"),
                                                  QString(),tr("Scalable vector graphics (*.svg)"));
    if(!fileName.isEmpty())
    {
        QFile file(fileName);
        if(file.open(QIODevice::WriteOnly | QIODevice::Text))
        {
            QTextStream write(&file);
            write<<currentDomDoc->toByteArray();
            file.close();
        }
    }
}

void MainWindow::traverseNode(const QDomNode& node, QVector<QDomNode *> * domNodeVector, int &objectCounter)
{
    QDomNode domNode = node.firstChild();
    while(!domNode.isNull()) {
        if(domNode.isElement()) {
            QDomElement domElement = domNode.toElement();
            if(!domElement.isNull()) {
                domElement.setAttribute("id",QString::number(objectCounter));
                ++objectCounter;
                domNodeVector->push_back(new QDomNode(domNode));

                //and save pointer to this element somewhere

            }
        }
        traverseNode(domNode,domNodeVector,objectCounter);
        domNode = domNode.nextSibling();
    }
}
void MainWindow::updateScene()
{
    currentRenderer->load(currentDomDoc->toByteArray());
    view->update();
}
void MainWindow::addFrame()
{

    QByteArray tmpBArray=currentDomDoc->toByteArray();
    currentDomDoc=new QDomDocument();
    domDocs->push_back(currentDomDoc);
    currentDomDoc->setContent(tmpBArray);

    currentScene=new QGraphicsScene();
    currentScene->setSceneRect(0,0,currentDomDoc->documentElement().attribute("width").toInt(),
                               currentDomDoc->documentElement().attribute("height").toInt());
    scenes.push_back(currentScene);
    bArray=new QByteArray(currentDomDoc->toByteArray());
    currentRenderer=new QSvgRenderer(*bArray);
    renderers->push_back(currentRenderer);
    frameBox->addItem("Frame №"+QString::number(scenes.size()));
    qDebug("OK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");


    timesBetweenFrames->push_back(0);
    frameBox->setCurrentIndex(scenes.size()-1);
    timeSetter->setValue(0);

    //fucking error


    constInfoLabel->setVisible(true);
    timeSetter->setVisible(true);

    QVector<QDomNode*>domNodeVector;
    int objectCounter=0;
    traverseNode(currentDomDoc->documentElement(),&domNodeVector, objectCounter);
    myShape *tmp;
    for(int i=0;i<objectCounter;++i)
    {
        if(domNodeVector.at(i)->toElement().tagName()=="circle")
        {
            tmp=new myCircle(domNodeVector.at(i));
        }
        else if(domNodeVector.at(i)->toElement().tagName()=="rect")
        {
            tmp=new myRect(domNodeVector.at(i));
        }

        connect(tmp,SIGNAL(attributeChanged()),this,SLOT(updateScene()));
        tmp->setSharedRenderer(currentRenderer);
        tmp->setElementId(tmp->getElementId());
        currentScene->addItem(tmp);
        tmp->setFlag(QGraphicsSvgItem::ItemIsMovable);
        tmp->setFlag(QGraphicsSvgItem::ItemIsSelectable);
        tmp->setPosAsInFile();
    }
    view->setScene(currentScene);
    view->update();

}
void MainWindow::setCurrentFrame(int num)
{
    currentDomDoc=domDocs->at(num);
    currentRenderer=renderers->at(num);
    currentScene=scenes.at(num);
    view->setScene(currentScene);
    view->update();

    if(num==0)
    {
        constInfoLabel->setVisible(false);
        timeSetter->setVisible(false);
    }
    else
    {
        constInfoLabel->setVisible(true);
        timeSetter->setVisible(true);
    }
    if(num>0)
        timeSetter->setValue(timesBetweenFrames->at(num-1));

}
void MainWindow::setTimeBetweenFrames(int time)
{
    if(frameBox->currentIndex()>0)
        timesBetweenFrames->replace(frameBox->currentIndex()-1,time);
    qDebug()<<*timesBetweenFrames;
}
