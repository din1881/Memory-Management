#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qlabel.h"
#include "qscrollbar.h"
#include <QToolBar>
#include "qmessagebox.h"
#include "QVBoxLayout"
#include "qdebug.h"
#include "qsize.h"
#include "QHBoxLayout"
#include "QGraphicsScene"
#include <QGraphicsView>
#include <QHBoxLayout>
#include <QButtonGroup>
#include <QToolButton>
#include <QLineEdit>
#include <QMessageBox>
#include <QCoreApplication>
#include <QPushButton>
#include <QGraphicsProxyWidget>
#include <QCheckBox>
#include <QProcess>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class DrawingQueue
{
public:
    int startingAddress,size;
    QString Name;
};

class Segments
{
  public:
    int startingAddress, size;
    QString segmentName, segmentSize, processName;
};

class Holes
{
public:
    int startingAddress, size;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    int global_index=-1;
    int bestflag=0;
    int firstflag=0;
    int First_Drawn = 0;
    int Deallocation_flag = 0;
    MainWindow(QWidget *parent = nullptr);
    QVector <QGraphicsProxyWidget *> PointersToButtonsDrawn;
    QVector <DrawingQueue *> DrawingItems;
    QButtonGroup *BGroup;
    QVector<Segments *> segments;
    QVector <Holes *> holes;
    QHBoxLayout *Horizontal_layout;
    QGraphicsScene *sideButtonsScene;
    QGraphicsView *sideButtonsView;
    QGraphicsScene *sideOptionsScene;
    QGraphicsView *sideOptionsView;
    QGraphicsScene *segmentTableScene;
    QGraphicsView *segmentTableView;
    QGraphicsScene *memDrawingScene;
    QGraphicsView *memDrawingView;
    QToolBar *buttonsToolbar;
    QToolButton *addHoles;
    QToolButton *addHolesNo;
    QToolButton *processButton;
    QToolButton *holesDoneB;
    QToolButton *drawButton;
    QToolButton *restartButton;
    QToolButton *tableButton;
    QToolButton *tableInputButton;
    QWidget * placeholder;
    QLabel *memorySizeLabel;
    QLineEdit *memorySize;
    QLabel *noHolesLabel;
    QLineEdit *noHoles;
    QLineEdit *no_segments;
    QVector <Holes *> holesQueue;
    //for testing
    QVector <Holes *> holeQueue;
    QVector <Segments *> segmQueue;
    QVector <Segments *> large_segments;
    QVector <Segments *> table;
    QLabel *hSizeLabel;
    QLabel *hAddressLabel;
    QLineEdit *hSize;
    QLineEdit *hAddress;
    QLabel* processTableLabel;
    QLineEdit* processTablename;
    QToolButton *drawMyHoles;
    QString holes_num, memSize;
    QIcon processIcon;
    QToolButton *addNewProcess;
    QToolButton *NewProcess;
    QLabel *pLabel;
    QLineEdit *pLineEdit;
    QToolButton *segInput;
    QLineEdit *segName;
    QLineEdit *segSize;
    QLabel *segNameLabel;
    QLabel *segSizeLabel;
    QVector <QLineEdit *> segNameInputs;
    QVector <QLineEdit *> segSizeInputs;
    QVector <QLineEdit *> holeSizeInputs;
    QVector <QLineEdit *> holeStartingAddInputs;
    QCheckBox *bestFitBox;
    QCheckBox *firstFitBox;
    QLabel *bestFitLabel;
    QLabel * firstFitLabel;
    QToolButton *deallocate_button;
    void test();




    ~MainWindow();

private:
    //Ui::MainWindow *ui;

public slots:
    void lineEdits();
    void memSizeAndAdd();
    void drawHoles();
    void segmentsLayout();
    void drawProcess();
    void show_seg_table();
    void get_table_name();
    void addSegmentsLayout();
    void drawSegInputs();
    void get_data();
    void start_deallocate();
    void restart();


};
#endif // MAINWINDOW_H
