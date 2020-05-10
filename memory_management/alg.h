#ifndef ALG_H
#define ALG_H

#include "mainwindow.h"
void Best_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h);
void First_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h);
void Deallocate(QVector<Segments *> &s, QVector <Holes *> &h, int y_button, int w_button);
void get_segment_table (QVector<Segments *> &table,QVector<Segments *> &large_seg, QString name);
#endif // ALG_H
