#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QCheckBox>
#include <QToolBar>
#include <QVBoxLayout>
#include <QVector>
#include <QObject>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVector>
#include <QString>

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

    QToolBar *Vtoolbar;
    QToolBar *Htoolbar;
    QPushButton *addHoles;
    QPushButton *addProcess;
    QPushButton *addHolesDone;
    QPushButton *addProDone;
    QCheckBox *firstFit_checkbox;
    QCheckBox *bestFit_checkbox;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
