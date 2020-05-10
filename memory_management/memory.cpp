#include "memory.h"

QPushButton * Create_New_Button()
{
    QPushButton *new_button = new QPushButton();
    return new_button;
}

void Draw_Memory(QVector<Segments *> &segments,QVector <Holes *> &holes,QButtonGroup *BGroup,QGraphicsScene *Memory_Scene,QMainWindow *Mainn,int y)
{
    int h = y;
    int index = y;
    int sum = holes.size() + segments.size();
    for(int i = 0 ; i < sum;i++)
    {

        for(int j = 0 ; j < segments.size();j++)
        {
            if(segments[j]->startingAddress == h)
            {
                BGroup->addButton(Create_New_Button(),index);
                BGroup->button(index)->setStyleSheet(" QPushButton{ background-color:#AFEEEE; color:black; font-size: 17px; font-family: Arial;border-radius: 10%;} "
                                                     "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");
                BGroup->button(index)->setGeometry(0,y,150,50);
                BGroup->button(index)->setText("Segment "+ QString::number(j));
                h+=segments[j]->size;
                y+=50;
                index ++;
//                qDebug()<<"added segment " +  QString::number(j) + ", Starting : "<< segments[j]->startingAddress<<"Size: "<< segments[j]->size <<" height :" <<h<< "The value of i :"<<index;
                break;
            }
        }
        for(int k = 0; k < holes.size();k++)
        {
            if(holes[k]->startingAddress == h)
            {
                BGroup->addButton(Create_New_Button(),index);
                BGroup->button(index)->setStyleSheet(" QPushButton{ background-color:black; color:white; font-size: 17px; font-family: Arial;border-radius: 10%;} "
                                                     "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");
                BGroup->button(index)->setGeometry(0,y,150,50);
                y+=50;
                BGroup->button(index)->setText("Hole");
                h+=holes[k]->size;
                index ++;
//                qDebug()<<"added hole" +  QString::number(k) + " , Starting : "<< holes[k]->startingAddress<<"Size: "<< holes[k]->size<<" height :" <<h << "The value of i :"<<index;
                break;
            }
        }
    }
    for(int i = 0 ; i < (BGroup->buttons().length()) ;i++)
    {
        Memory_Scene->addWidget(BGroup->button(i));

    }

    QPushButton::connect(BGroup, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
            [=](QAbstractButton *button){
        if(button->text() != "Hole")
        {

            int ret =QMessageBox::critical(Mainn,"Memory Modification Requested","Are you sure you want to de-allocate this segment ?",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
            switch (ret) {
            case QMessageBox::Yes:
                for(int i = 1;i<(BGroup->buttons().length());i++)
                {
                    if(BGroup->button(i)->text() == button->text())
                    {
                        button->setStyleSheet(" QPushButton{ background-color:black; color:white; font-size: 17px; font-family: Arial;border-radius: 10%;} "
                                              "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");

                        button->setText("Hole");


                    }
                }

                break;

            case QMessageBox::No:
                break;
            default:
                qDebug()<<"Error Happened";
                break;
            }
        }

    });
}
