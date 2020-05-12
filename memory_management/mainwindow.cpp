#include "mainwindow.h"
#include "memory.h"
#include "alg.h"
int proCounter=0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    //, ui(new Ui::MainWindow)
{
    //ui->setupUi(this);
    /******************** Creating Testcases ***************************/
    BGroup = new QButtonGroup();
//    for(int i = 0 ; i <5 ;i ++)
//    {
//        Segments * Segment_Temp = new Segments();
//        Segment_Temp->segmentName = "Segment"+QString::number(i);
//        segments.append(Segment_Temp);
//    }
//    segments[0]->size = 1000;
//    segments[0]->startingAddress = 1400;
//    segments[1]->size = 400;
//    segments[1]->startingAddress = 6300;
//    segments[2]->startingAddress = 4300;
//    segments[2]->size = 400;
//    segments[3]->size = 1100;
//    segments[3]->startingAddress = 3200;
//    segments[4]->size = 1000;
//    segments[4]->startingAddress = 4700;
    for(int i = 0;i <3;i++)
    {
        Holes *Hole_Temp = new Holes();
        holes.append(Hole_Temp);
    }

    holes[0]->startingAddress = 1000;
    holes[0]->size = 500;
    holes[1]->startingAddress = 2000;
    holes[1]->size = 200;


    /******************** Creating Testcase ***************************/
    //Segments* Temp_Segment= new Segments;
    //Segments* Temp_Segment1= new Segments;
    //Temp_Segment->size=700;
    //Temp_Segment1->size=300;
    //Temp_Segment1->segmentName="p1";
    //Temp_Segment->segmentName="p1";
    //segmQueue.append(Temp_Segment);
    //segmQueue.append(Temp_Segment1);
    //Holes* Temp_Hole = new Holes;
    //Temp_Hole->startingAddress = 0;
    //Temp_Hole->size = 500;
    //holeQueue.append(Temp_Hole);
    //Holes* Temp_Hole1 = new Holes;
    //Temp_Hole1->startingAddress = 2400;
    //Temp_Hole1->size = 1000;
    //holeQueue.append(Temp_Hole1);
    //Holes* Temp_Hole2 = new Holes;
    //Temp_Hole2->startingAddress = 5700;
    //Temp_Hole2->size = 1400;
    //holeQueue.append(Temp_Hole2);


    /**************GUI Design*******************/
    Horizontal_layout = new QHBoxLayout();

    sideButtonsScene = new QGraphicsScene();
    sideButtonsView = new QGraphicsView(sideButtonsScene);
    sideButtonsScene->setBackgroundBrush(QColor(3,90,166));
    sideButtonsView->setMinimumWidth(30);
    sideButtonsView->setMaximumWidth(70);
    sideButtonsView->setMinimumHeight(600);
    sideButtonsView->setAlignment(Qt::AlignTop);

    /*****************************Adding buttons to sideButtonsView******************************/

    addHoles = new QToolButton();
    addHoles->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    addHoles->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addHoles->setGeometry(0,15,75,80);
    addHoles->setIcon(QIcon("../icons/hole.png"));
    addHoles->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    addHoles->setText("Holes");
    sideButtonsScene->addWidget(addHoles);

    connect(addHoles,SIGNAL(clicked()),this,SLOT(lineEdits())) ;




    processButton = new QToolButton();
    processButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    processButton->setGeometry(0,100,75,75);
    processButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

    processIcon.addPixmap(QPixmap("../icons/planning.png"), QIcon::Normal);
    //processIcon.addPixmap(QPixmap("../icons/process-disabled.png"), QIcon::Disabled);
    processButton->setIcon(processIcon);
    processButton->setIconSize(QSize(50,50));
    processButton->setText("Process");
    processButton->setEnabled(false);
    sideButtonsScene->addWidget(processButton);
    connect(processButton,SIGNAL(clicked()),this,SLOT(addSegmentsLayout())) ;



    drawButton = new QToolButton();
    drawButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    drawButton->setGeometry(0,190,75,75);
    drawButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    drawButton->setIcon(QIcon("../icons/right.png"));
    drawButton->setIconSize(QSize(50,50));
    drawButton->setText("Draw");
    sideButtonsScene->addWidget(drawButton);
    connect(drawButton,SIGNAL(clicked()),this,SLOT(drawProcess())) ;

    tableButton = new QToolButton();
    tableButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    tableButton->setGeometry(0,275,75,75);
    tableButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    tableButton->setIcon(QIcon("../icons/edit-table.png"));
    tableButton->setIconSize(QSize(50,50));
    tableButton->setText("Table");
    sideButtonsScene->addWidget(tableButton);
    connect(tableButton,SIGNAL(clicked()),this,SLOT(get_table_name())) ;

    restartButton = new QToolButton();
    restartButton->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    restartButton->setGeometry(0,350,75,75);
    restartButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    restartButton->setIcon(QIcon("../icons/updated2.png"));
    restartButton->setIconSize(QSize(50,50));
    restartButton->setText("Restart");
    sideButtonsScene->addWidget(restartButton);

    deallocate_button = new QToolButton();
    deallocate_button ->setStyleSheet("QToolButton{ background-color :#035aa6; border:none; }");
    deallocate_button ->setGeometry(0,450,75,75);
    deallocate_button ->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    deallocate_button ->setIcon(QIcon("../icons/hole.png"));
    deallocate_button ->setIconSize(QSize(50,50));
    deallocate_button ->setText("Deallocate");
    sideButtonsScene->addWidget(deallocate_button );
    connect(deallocate_button,SIGNAL(clicked()),this,SLOT(start_deallocate())) ;



    /***********************************************************************/

    sideOptionsScene = new QGraphicsScene();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);



   /* segmentTableScene = new QGraphicsScene();
    segmentTableView = new QGraphicsView(segmentTableScene);
    segmentTableScene->setBackgroundBrush(Qt::white);
    segmentTableView->setMinimumWidth(150);*/


    memDrawingScene = new QGraphicsScene();
    memDrawingView = new QGraphicsView(memDrawingScene);
    memDrawingScene->setBackgroundBrush(Qt::white);
    memDrawingView->setMinimumWidth(250);


    Horizontal_layout->addWidget(sideButtonsView);
    Horizontal_layout->addWidget(sideOptionsView);
    //Horizontal_layout->addWidget(segmentTableView);
    Horizontal_layout->addWidget(memDrawingView);


    placeholder= new  QWidget();
    placeholder->setLayout(Horizontal_layout);
    //placeholder->setStyleSheet("QWidget{background-color : #035aa6;}");
    this->setCentralWidget(placeholder);


}




MainWindow::~MainWindow()
{
   // delete ui;
}

void MainWindow::lineEdits()
{
    sideOptionsScene->clear();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);

    memorySizeLabel= new QLabel ();
    memorySizeLabel->setText("Memory Size");
    memorySizeLabel->setStyleSheet("background-color :#035aa6; color:black;font-size: 15px; font-family: Arial;");
    memorySizeLabel->setGeometry(50,10,90,30);
    sideOptionsScene->addWidget(memorySizeLabel);

    memorySize= new   QLineEdit();
    memorySize->setGeometry(30,50,120,30);
    memorySize->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(memorySize);


    noHolesLabel = new QLabel ();
    noHolesLabel->setText("Number of Holes");
    noHolesLabel->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    noHolesLabel->setGeometry(35,100, 110, 30);
    sideOptionsScene->addWidget(noHolesLabel);

    noHoles = new   QLineEdit();
    noHoles->setGeometry(30,140,120,30);
    noHoles->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(noHoles);

    bestFitBox = new QCheckBox();
    bestFitBox->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    bestFitBox->setGeometry(15,190,18,18);
    bestFitLabel = new QLabel("Best Fit");
    bestFitLabel->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    bestFitLabel->setGeometry(35,190,80,18);
    sideOptionsScene->addWidget(bestFitBox);
    sideOptionsScene->addWidget(bestFitLabel);

    firstFitBox = new QCheckBox();
    firstFitBox->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    firstFitBox->setGeometry(95,190,18,18);
    firstFitLabel= new QLabel("First Fit");
    firstFitLabel->setStyleSheet("background-color :#035aa6; color:black; font-size: 15px; font-family: Arial;");
    firstFitLabel->setGeometry(110,190,80,18);
    sideOptionsScene->addWidget(firstFitBox);
    sideOptionsScene->addWidget(firstFitLabel);

    addHolesNo = new QToolButton();
    addHolesNo->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    //addHolesNo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addHolesNo->setGeometry(50,210,75,80);
    addHolesNo->setIcon(QIcon("../icons/add.png"));
    addHolesNo->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    //addHolesNo->setText("Holes");
    sideOptionsScene->addWidget(addHolesNo);
    connect(addHolesNo,SIGNAL(clicked()),this,SLOT(memSizeAndAdd())) ;
}

void MainWindow::memSizeAndAdd()
{
    if(bestFitBox->isChecked()) bestflag=1;
    else if(firstFitBox->isChecked()) firstflag=1;
    memSize= memorySize->text();
    holes_num = noHoles->text();
    //qDebug()<<"hey1: "<<holes_num;
    hSizeLabel = new QLabel("Hole Size");
    hAddressLabel = new QLabel("Starting Address");

    hSizeLabel ->setGeometry(5,280,65,30);
    hAddressLabel->setGeometry(90,280,120,30);

    hSizeLabel ->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");
    hAddressLabel->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");

    sideOptionsScene->addWidget(hSizeLabel);
    sideOptionsScene->addWidget(hAddressLabel);



    int height=290;
    qDebug()<<"hey2: "<<holes_num;
    for (int i = 0; i<holes_num.split(" ")[0].toInt(); i++)
    {
        hSize = new QLineEdit();
        hAddress = new QLineEdit();

        hSize->setGeometry(0,50+height,80,30);
        hAddress->setGeometry(100,50+height,80,30);

        sideOptionsScene->addWidget(hSize);
        sideOptionsScene->addWidget(hAddress);

        holeSizeInputs.append(hSize);
        holeStartingAddInputs.append(hAddress);

        height+=50;

    }

    drawMyHoles = new QToolButton();
    drawMyHoles->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    drawMyHoles->setGeometry(50,height+50,75,80);
    drawMyHoles->setIcon(QIcon("../icons/check.png"));
    drawMyHoles->setIconSize(QSize(50,50));
    sideOptionsScene->addWidget(drawMyHoles);
    connect(drawMyHoles,SIGNAL(clicked()),this,SLOT(drawHoles())) ;
}

void MainWindow::drawHoles()
{

    for(int i=0;i<holeSizeInputs.size();i++)
    {
        Holes *h = new Holes;

        h->startingAddress = (holeStartingAddInputs[i]->text()).split(" ")[0].toInt();
        h->size=(holeSizeInputs[i]->text()).split(" ")[0].toInt();


        holesQueue.append(h);

       qDebug()<<holesQueue[i]->size;
    }

    processButton->setEnabled(true);


}

void MainWindow::segmentsLayout()
{
    sideOptionsScene->clear();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);


    addNewProcess = new QToolButton();
    addNewProcess->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    //addHolesNo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    addNewProcess->setGeometry(50,10,75,80);
    addNewProcess->setIcon(QIcon("../icons/add.png"));
    addNewProcess->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    //addHolesNo->setText("Holes");
    sideOptionsScene->addWidget(addNewProcess);
    connect(addNewProcess,SIGNAL(clicked()),this,SLOT(addSegmentsLayout())) ;



}

void MainWindow::addSegmentsLayout()
{
    sideOptionsScene->clear();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setMaximumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);

    pLabel= new QLabel ();
    pLabel->setText("No. Of Segments");
    pLabel->setStyleSheet("background-color :#035aa6; color:black;font-size: 15px; font-family: Arial;");
    pLabel->setGeometry(30,30,150,30);
    sideOptionsScene->addWidget(pLabel);

    pLineEdit= new   QLineEdit();
    pLineEdit->setGeometry(25,70,120,30);
    pLineEdit->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(pLineEdit);


    segInput = new QToolButton();
    segInput->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    segInput->setGeometry(50,120,75,80);
    segInput->setIcon(QIcon("../icons/check.png"));
    segInput->setIconSize(QSize(50,50));
    sideOptionsScene->addWidget(segInput);
    connect(segInput,SIGNAL(clicked()),this,SLOT(drawSegInputs())) ;

}


void MainWindow::drawSegInputs()
{

    segNameLabel = new QLabel("Seg Name");
    segNameLabel ->setGeometry(5,205,120,30);
    segNameLabel ->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");

    segSizeLabel = new QLabel("Seg Size");
    segSizeLabel->setGeometry(110,205,120,30);
    segSizeLabel->setStyleSheet("background-color : #035aa6; color:black; font-size: 15px; font-family: Arial;");

    sideOptionsScene->addWidget(segNameLabel);
    sideOptionsScene->addWidget(segSizeLabel);
    int height=220;

    for (int i = 0; i<(pLineEdit->text()).split(" ")[0].toInt(); i++)
    {
        segName = new QLineEdit();
        segSize = new QLineEdit();

        segName->setGeometry(5,50+height,80,30);
        segSize->setGeometry(100,50+height,80,30);

        sideOptionsScene->addWidget(segName);
        sideOptionsScene->addWidget(segSize);

        segNameInputs.append(segName);
        segSizeInputs.append(segSize);

        height+=50;

    }

    NewProcess = new QToolButton();
    NewProcess->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    //addHolesNo->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    NewProcess->setGeometry(50,height+30,75,80);
    NewProcess->setIcon(QIcon("../icons/add.png"));
    NewProcess->setIconSize(QSize(50,50));
    //addHoles->setAutoRaise(false);
    //addHolesNo->setText("Holes");
    sideOptionsScene->addWidget(NewProcess);
    connect(NewProcess,SIGNAL(clicked()),this,SLOT(get_data()));
}

void MainWindow::get_data()
{
    for(int i = 0; i < segNameInputs.size(); i++)
    {
        Segments *s = new Segments;
        s->segmentName=(segNameInputs[i]->text());
        s->size=(segSizeInputs[i]->text()).split(" ")[0].toInt();
        s->processName=("P"+QString::number(proCounter));

        segmQueue.append(s);
        qDebug()<<segmQueue[i]->size;
    }
    segNameInputs.clear();
    segSizeInputs.clear();
    proCounter++;
}

void MainWindow::drawProcess()
{

    if(bestflag) {Best_fit(segmQueue,large_segments,holesQueue); }
    else if(firstflag) {First_fit(segmQueue,large_segments,holesQueue);}

    for(int i=0; i<large_segments.size();i++){
        qDebug()<<"Large_Segments of "<<i<<", Size : "<<large_segments[i]->size<<endl;

    }

    for(int i=0; i<holesQueue.size();i++){
        qDebug()<<"holes:"<<holesQueue[i]->size<<endl;
         qDebug()<<"holes address:"<<holesQueue[i]->startingAddress<<endl;
    }

    for(int i=0; i<holesQueue.size();i++){
        qDebug()<<"holes:"<<holesQueue[i]->size<<endl;
         qDebug()<<"holes address:"<<holesQueue[i]->startingAddress<<endl;
    }
    if(First_Drawn == 1)
    {
        qDebug()<<"Condition Triggered";
        memDrawingScene->clear();
        PointersToButtonsDrawn.clear();
        memDrawingView = new QGraphicsView(memDrawingScene);
        memDrawingScene->setBackgroundBrush(Qt::white);
        memDrawingView->setMinimumWidth(250);
        memDrawingView->setMaximumWidth(250);
        memDrawingView->setAlignment(Qt::AlignTop);
        /* Need to check for scene clear */
        //qDebug()<< "Size of BGroup : "<<BGroup->buttons().size();
        //qDebug()<<"Size of pinters to buttons :"<<PointersToButtonsDrawn.size();
    }

    First_Drawn = 1;
    qDebug()<<"Flag : "<<First_Drawn;
    /*insert memory drawing here*/
    qDebug()<<"Value of global variable in function body : "<<global_index;
    Draw_Memory(large_segments,holesQueue,BGroup,memDrawingScene,this,PointersToButtonsDrawn,0,0,0,&global_index, &large_segments);
    qDebug()<<"global index is" <<global_index;


}

void MainWindow::start_deallocate(){

    if(global_index>=0){
        Deallocate(large_segments,holesQueue,global_index);
        for(int i=0; i<large_segments.size();i++){
            qDebug()<<"Large_Segments of "<<i<<", Size : "<<large_segments[i]->size<<endl;

        }

        for(int i=0; i<holesQueue.size();i++){
            qDebug()<<"holes:"<<holesQueue[i]->size<<endl;
             qDebug()<<"holes address:"<<holesQueue[i]->startingAddress<<endl;
        }

        memDrawingScene->clear();
        PointersToButtonsDrawn.clear();
        memDrawingView = new QGraphicsView(memDrawingScene);
        memDrawingScene->setBackgroundBrush(Qt::white);
        memDrawingView->setMinimumWidth(250);
        memDrawingView->setMaximumWidth(250);
        memDrawingView->setAlignment(Qt::AlignTop);


        Draw_Memory(large_segments,holesQueue,BGroup,memDrawingScene,this,PointersToButtonsDrawn,0,0,0,&global_index, &large_segments);
    }

}

void MainWindow::test(){
    for(int i=0; i<holesQueue.size();i++){
        qDebug()<<"holes:"<<holesQueue[i]->size<<endl;
         qDebug()<<"holes address:"<<holesQueue[i]->startingAddress<<endl;
    }
    if(First_Drawn == 1)
    {
        qDebug()<<"Condition Triggered";
        Horizontal_layout->removeWidget(memDrawingView);
        memDrawingScene->clear();
        PointersToButtonsDrawn.clear();
        memDrawingScene = new QGraphicsScene();

        memDrawingView = new QGraphicsView(memDrawingScene);
        memDrawingScene->setBackgroundBrush(Qt::white);
        memDrawingView->setMinimumWidth(250);
        Horizontal_layout->addWidget(memDrawingView);
        /* Need to check for scene clear */
        //qDebug()<< "Size of BGroup : "<<BGroup->buttons().size();
        //qDebug()<<"Size of pinters to buttons :"<<PointersToButtonsDrawn.size();
    }

    First_Drawn = 1;
    qDebug()<<"Flag : "<<First_Drawn;
    /*insert memory drawing here*/
    qDebug()<<"Value of global variable in function body : "<<global_index;
    Draw_Memory(large_segments,holesQueue,BGroup,memDrawingScene,this,PointersToButtonsDrawn,0,0,0,&global_index, &large_segments);
    qDebug()<<"global index is" <<global_index;

     qDebug()<<"last";
}
void MainWindow::get_table_name(){
    sideOptionsScene->clear();
    sideOptionsView = new QGraphicsView(sideOptionsScene);
    sideOptionsScene->setBackgroundBrush(QColor(3,90,166));
    sideOptionsView->setMinimumWidth(250);
    sideOptionsView->setAlignment(Qt::AlignTop);

    processTableLabel= new QLabel ();
    processTableLabel->setText("Process Name");
    processTableLabel->setStyleSheet("background-color :#035aa6; color:black;font-size: 15px; font-family: Arial;");
    processTableLabel->setGeometry(40,10,100,30);
    sideOptionsScene->addWidget(processTableLabel);

    processTablename= new QLineEdit();
    processTablename->setGeometry(30,50,120,30);
    processTablename->setStyleSheet("background-color:white;");
    sideOptionsScene->addWidget(processTablename);

    QString path = QCoreApplication::applicationDirPath() + "/../../../Memory-Management/icons/";
    tableInputButton = new QToolButton();
    tableInputButton->setStyleSheet("QToolButton{ background-color : #035aa6; border:none;}");
    tableInputButton->setGeometry(50,80,75,80);
    tableInputButton->setIcon(QIcon(path +"check.png"));
    tableInputButton->setIconSize(QSize(50,50));
    sideOptionsScene->addWidget(tableInputButton);
    connect(tableInputButton,SIGNAL(clicked()),this,SLOT(show_seg_table())) ;
}

void MainWindow::show_seg_table(){

    QString get_process_name = processTablename->text();
    qDebug()<<get_process_name;

    get_segment_table(table,large_segments,get_process_name);

    //check if the user entered invalid process name
    if(table.size()==0){
        QMessageBox *invalid_name = new QMessageBox;
        invalid_name->setText("No process found with this name");
        invalid_name->exec();
    }

    int height=0;
    for(int i=0;i<table.size();i++){
        QLabel *address1 = new QLabel;
        QLabel *size1 = new QLabel;
        QLabel *seg_no = new QLabel;
        address1->setText(tr(" %1").arg(table[i]->startingAddress));
        size1->setText(tr(" %1").arg(table[i]->size));
        seg_no->setText(tr("%1").arg(i));
        seg_no->setStyleSheet("background-color :#035aa6; color:black;");
        seg_no->setGeometry(5,160+height,20,25);
        address1->setGeometry(30,160+height,50,25);
        size1->setGeometry(110,160+height,50,25);
        sideOptionsScene->addWidget(seg_no);
        sideOptionsScene->addWidget(address1);
        sideOptionsScene->addWidget(size1);
        height+=40;
    }
    table.clear();


}

