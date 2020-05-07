#include "mainwindow.h"
//#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
  //ui(new Ui::MainWindow)
{
    /******************* Adding Vertical ToolBar ***********************/

    Vtoolbar = new QToolBar(this);
    Vtoolbar->setStyleSheet("QToolBar{ background-color:#035aa6;  color:white; }");
    Vtoolbar->setGeometry(0,0,150,500);


    /**************** Adding holes Button inside toolbar **************/

    addHoles = new QPushButton("Add Holes",this);
    addHoles->setStyleSheet(" QPushButton{ background-color:#1f4068; color:white; font-size: 17px; font-family: Arial;border-radius: 4px;} "
                      "QPushButton:hover { background-color: white; color:rgb(0,0,0); border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;} ");
    addHoles->setGeometry(25,150,100,40);


    /************ Adding Algorithm CheckBox inside toolbar *************/

    bestFit_checkbox = new QCheckBox("Best Fit", this);
    bestFit_checkbox->setStyleSheet("background-color:#035aa6; color:rgb(0,0,0); font-size: 15px; font-family: Arial;");
    bestFit_checkbox->setGeometry(30,210,18,18);

    firstFit_checkbox = new QCheckBox("First Fit", this);
    firstFit_checkbox->setStyleSheet("background-color:#035aa6; color:rgb(0,0,0); font-size: 15px; font-family: Arial;");
    firstFit_checkbox->setGeometry(70,210,18,18);


    /**************** Adding Hdone Button inside toolbar **************/

    addHolesDone = new QPushButton("Done",this);
    addHolesDone->setStyleSheet(" QPushButton{ background-color:#1f4068; color:white; font-size: 17px; font-family: Arial;border-radius: 4px;} "
                      "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:1f4068;} ");
    addHolesDone->setGeometry(25,250,100,40);



    /******************* Adding Horizontal ToolBar ***********************/

    Htoolbar = new QToolBar(this);
    Htoolbar->setStyleSheet("QToolBar{ background-color:#035aa6;  color:white; }");
    Htoolbar->setGeometry(0,500,1000,75);



    /**************** Adding addProcess Button inside toolbar **************/

    addProcess = new QPushButton("+",this);
    addProcess->setStyleSheet(" QPushButton{ background-color:#1f4068; color:white; font-size: 17px; font-family: Arial;border-radius: 4px;} "
                      "QPushButton:hover { background-color: white;color:rgb(0,0,0); border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:1f4068;} ");
    addProcess->setGeometry(475,515,50,50);



    /**************** Adding Hdone Button inside toolbar **************/

    addProDone = new QPushButton("✓",this);
    addProDone->setStyleSheet(" QPushButton{ background-color:#1f4068; color:white; font-size: 17px; font-family: Arial;border-radius: 4px;} "
                      "QPushButton:hover { background-color: white;color:rgb(0,0,0); border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:1f4068;} ");
    addProDone->setGeometry(550,515,50,50);




    // Initializing the scene , and making it parent to the view (Qt requirments :] )
    QGraphicsScene *Scene = new QGraphicsScene();
    QGraphicsView *view = new QGraphicsView();
    Scene->setBackgroundBrush(Qt::white);
    view = new  QGraphicsView(Scene);

    // Creating a horizontal  layout (column) to add the things in the same column to it
    QHBoxLayout * Hlayout = new QHBoxLayout();
    Hlayout->addWidget(Vtoolbar);
    Hlayout->addWidget(addHoles);
    Hlayout->addWidget(addHolesDone);
    Hlayout->addWidget(bestFit_checkbox);
    Hlayout->addWidget(firstFit_checkbox);
    Hlayout->addWidget(view);


    // Creating a vertical row that can take widgets in it , we will make a row of column element , and a push button
    QVBoxLayout *vlayout = new QVBoxLayout();
    vlayout->addLayout(Hlayout);
    vlayout->addWidget(Htoolbar);
    vlayout->addWidget(addProcess);
    vlayout->addWidget(addProcess);
    vlayout->addWidget(addProDone);
    this->setLayout(vlayout);

}

MainWindow::~MainWindow()
{
    //delete ui;
}

