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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class Segments
{
  public:
    int startingAddress, size;
    QString segmentName, segmentSize;
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
    MainWindow(QWidget *parent = nullptr);

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
    QToolButton *drawMyHoles;
    QString holes_num, memSize;
    QIcon processIcon;


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

};
#endif // MAINWINDOW_H
