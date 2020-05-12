#ifndef MEMORY_H
#define MEMORY_H

#include "mainwindow.h"

QPushButton* Create_New_Button();
void Draw_Memory(QVector<Segments *> &segments,QVector <Holes *> &holes,QButtonGroup *BGroup,QGraphicsScene *Memory_Scene,QMainWindow *Mainn,QVector <QGraphicsProxyWidget *> PointersToButtonsDrawn,int y,int h,int index,int *global,QVector<Segments *> *segments_loop);

#endif // MEMORY_H
