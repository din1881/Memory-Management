#include "memory.h"

QPushButton * Create_New_Button()
{
    QPushButton *new_button = new QPushButton();
    return new_button;
}

void Draw_Memory(QVector<Segments *> &segments,QVector <Holes *> &holes,QButtonGroup *BGroup,QGraphicsScene *Memory_Scene,QMainWindow *Mainn,QVector <QGraphicsProxyWidget *> PointersToButtonsDrawn,int y,int h,int index,int *global,QVector<Segments *> *segments_loop)
{

    QLabel *add;
    QLabel *End;

    for (int i = 0; i < holes.size(); i++)
    {
        for (int j = 0; j < holes.size(); j++)
        {
            if (holes[i]->startingAddress < holes[j]->startingAddress)
        {
                Holes* temp = holes[j];
                holes[j] = holes[i];
                holes[i] = temp;
            }
        }

    }

    for (int i = 0; i < segments.size(); i++)
    {
        for (int j = 0; j < segments.size(); j++)
        {
            if (segments[i]->startingAddress < segments[j]->startingAddress)
        {
                Segments* temp = segments[j];
                segments[j] = segments[i];
                segments[i] = temp;
            }
        }

    }
    QVector <DrawingQueue> DrawingItems;
    DrawingQueue Temp;
    /* If the starting address of the first block (either hole or segment) was 0 then set it as first vector element */
    if((segments.size() != 0) && (holes[0]->startingAddress > segments[0]->startingAddress))
    {
        h = segments[0]->startingAddress;
    }else
    {
        qDebug()<<"Captured first hole";

        h = holes[0]->startingAddress;
        qDebug()<<h;
    }
    /* else add space before it and set the height to its start address */
    if( ((holes[0]->startingAddress !=0)||(segments.size()!=0 && segments[0]->startingAddress !=0))  && (h != 0) )
    {
        qDebug()<<"Passed codition";
        Temp.Name = "Reserved Space";
        Temp.startingAddress = 0;
        Temp.size = h;
        //Tasnim commented this
        //DrawingItems.append(Temp);

    }


    /*  Adding all segments to the vector */

    for(int j = 0 ; j < segments.size();j++)
    {
        Temp.Name = segments[j]->segmentName;
        Temp.startingAddress = segments[j]->startingAddress;
        Temp.size = segments[j]->size;
        h+=segments[j]->size;
        DrawingItems.append(Temp);
    }
    /*  Adding all segments to the vector */

    for(int k = 0; k < holes.size();k++)
    {

        Temp.Name = "Hole";
        Temp.startingAddress = holes[k]->startingAddress;
        Temp.size = holes[k]->size;
        h+=holes[k]->size;
        DrawingItems.append(Temp);
    }

    /* After the previous loops , we now got a vector of blocks of holes and segments that need to be arranged */


    for(int i = 0 ; i < (DrawingItems.size() - 1);i++)
    {
        for(int j = i+1;j<DrawingItems.size();j++)
        {
            if(DrawingItems[j].startingAddress < DrawingItems[i].startingAddress)
            {
                Temp = DrawingItems[j];
                DrawingItems[j]=DrawingItems[i];
                DrawingItems[i]= Temp;

            }
        }
    }
    /* Adding spaces between arranged items at the end of the vecotr */
    h = 0;
    for(int i = 0 ; i < DrawingItems.size();i++)
    {
        if(DrawingItems[i].startingAddress > h)
        {
            /* These is a space before this item as the min address is less than its starting address */
            Temp.Name = "Reserved Space";
            Temp.size = DrawingItems[i].startingAddress - h;
            Temp.startingAddress = h;
            //DrawingItems.append(Temp);
            h+=Temp.size;
            h+=DrawingItems[i].size;


        }else if (DrawingItems[i].startingAddress == h)
        {
            h+= DrawingItems[i].size;
        }
    }
    /* Arranging the vector after adding the space */
    for(int i = 0 ; i < (DrawingItems.size() - 1);i++)
    {
        for(int j = i+1;j<DrawingItems.size();j++)
        {
            if(DrawingItems[j].startingAddress < DrawingItems[i].startingAddress)
            {
                Temp = DrawingItems[j];
                DrawingItems[j]=DrawingItems[i];
                DrawingItems[i]= Temp;

            }
        }
    }
    //    for(int i = 0 ; i < DrawingItems.size();i++)
    //    {
    //        qDebug()<<"Drawing Item After ["<<i<<"] :"<<DrawingItems[i].Name << "Starting : "<<DrawingItems[i].startingAddress <<" , Size :"<<DrawingItems[i].size;
    //    }


    /* Adding items to drawing group button  */
    index = 0;
    for(int i = 0 ; i < DrawingItems.size();i++)
    {
        add = new QLabel;
        End = new QLabel;
        if(DrawingItems[i].Name.contains("Reserved"))
        {
            add->setGeometry(155,y-10,100,20);
            add->setText(QString::number(DrawingItems[i].startingAddress));
            add->setStyleSheet("background-color:white;");
            Memory_Scene->addWidget(add);
            BGroup->addButton(Create_New_Button(),index);

            BGroup->button(index)->setStyleSheet(QString("background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #000000, stop: 0.2 "
                                                         "	#232f2f,stop:0.4 #344747 , stop:0.6 #577777, stop:0.8 #8cbebe,stop:1 #AFEEEE)"));
            BGroup->button(index)->setGeometry(0,y,150,DrawingItems[i].size);
            y+=DrawingItems[i].size;
            BGroup->button(index)->setText(DrawingItems[i].Name);
            index ++;

        }else if (DrawingItems[i].Name == "Hole")
        {
            add->setGeometry(155,y-10,100,20);
            add->setText(QString::number(DrawingItems[i].startingAddress));
            add->setStyleSheet("background-color:white;");
            Memory_Scene->addWidget(add);
            BGroup->addButton(Create_New_Button(),index);
            BGroup->button(index)->setStyleSheet(" QPushButton{ background-color:#000000; color:white; font-size: 17px; font-family: Arial;border-radius: 10%;} "
                                                 "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");
            BGroup->button(index)->setGeometry(0,y,150,DrawingItems[i].size);
            y+=DrawingItems[i].size;
            BGroup->button(index)->setText(DrawingItems[i].Name);
            index ++;

        }else
        {
            add->setGeometry(155,y-10,100,20);
            add->setText(QString::number(DrawingItems[i].startingAddress));
            add->setStyleSheet("background-color:white;");
            Memory_Scene->addWidget(add);
            BGroup->addButton(Create_New_Button(),index);
            BGroup->button(index)->setStyleSheet(" QPushButton{ background-color:#00CED1; color:white; font-size: 17px; font-family: Arial;border-radius: 10%;} "
                                                 "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");
            BGroup->button(index)->setGeometry(0,y,150,DrawingItems[i].size);
            y+=DrawingItems[i].size;
            BGroup->button(index)->setText(DrawingItems[i].Name);
            index ++;

        }
        if(i == DrawingItems.size() - 1)
        {
            End->setGeometry(155,y-15,100,20);
            End->setText(QString::number(DrawingItems[i].startingAddress + DrawingItems[i].size));
            End->setStyleSheet("background-color:white;");
            Memory_Scene->addWidget(End);
        }


    }
    for(int i = 0 ; i < (BGroup->buttons().length());i++)
    {
        qDebug()<<"BGroup["<<i<<"] :"<<BGroup->button(i)->text();
    }

    for(int i = 0 ; i < (BGroup->buttons().length()) ;i++)
    {
        PointersToButtonsDrawn.append(Memory_Scene->addWidget(BGroup->button(i)));
    }
    qDebug()<<"Segments size : "<<segments_loop->size();
    QPushButton::connect(BGroup, static_cast<void(QButtonGroup::*)(QAbstractButton *)>(&QButtonGroup::buttonClicked),
                         [=](QAbstractButton *button){
      //  qDebug()<<"Segments size : "<<segments_loop->size();
        if(button->text() != "Hole")
        {

            int ret =QMessageBox::critical(Mainn,"Memory Modification Requested","Are you sure you want to de-allocate this segment ?",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
            switch (ret) {
            case QMessageBox::Yes:
                qDebug()<<"Segments size : "<<segments.size();
                /* For loop to get the index of the button pressed if it is a segment */
                if(segments_loop->size()!= 0)
                {
                    for(int i = 0 ; i < (segments_loop->size());i++)
                    {
                        if(button->text() == segments_loop->at(i)->segmentName)
                        {
                            *global = i;


                        }




                    }
                }
//                qDebug()<<"Value of global variable hereee:"<<*global;
//                for(int i = 0 ; i < (BGroup->buttons().length()) ; i++ )
//                {
//                    if(button->text() == BGroup->button(i)->text() && (BGroup->button(i)->y() == button->y()))
//                    {
//                        if(button->text()!="Hole")
//                        {

//                           // qDebug()<<"value of add in BGroup"<<BGroup->button(i)->y();
//                            //qDebug()<<"Value of add in button"<<button->y();
//                            if((i > 0) && ((BGroup->button(i-1)->text() == "Hole")) )
//                            {

//                                BGroup->button(i-1)->setGeometry(BGroup->button(i-1)->x(),BGroup->button(i-1)->y(),button->width(),BGroup->button(i-1)->height()+button->height());
//                                qDebug()<<button->text();
//                                /* I am expanding the hole above me , then replacing my place with it , then removing it*/
//                                QAbstractButton * Temp = BGroup->button(i-1);
//                                BGroup->addButton(BGroup->button(i),i-1);
//                                BGroup->addButton(Temp,i);
//                                Memory_Scene->removeItem(PointersToButtonsDrawn[i]);
//                                /* Check hena lw el ta7ty hole egm3ny 3alhaa */
//                                if((i != BGroup->buttons().size() - 1 ) &&(BGroup->button(i+1)->text() == "Hole"))
//                                {

//                                    BGroup->button(i)->setGeometry(BGroup->button(i)->x(),BGroup->button(i)->y(),button->width(),BGroup->button(i)->height()+BGroup->button(i+1)->height());
//                                    qDebug()<<button->text();
//                                    Temp = BGroup->button(i);
//                                    BGroup->addButton(BGroup->button(i+1),i);
//                                    BGroup->addButton(Temp,i+1);
//                                    Memory_Scene->removeItem(PointersToButtonsDrawn[i+1]);
//                                }
//                            }else if((i == 0) && ((BGroup->button(i+1)->text() == "Hole")))
//                            {
//                                     BGroup->button(i+1)->setGeometry(BGroup->button(i)->x(),BGroup->button(i)->y(),button->width(),BGroup->button(i)->height()+BGroup->button(i+1)->height());
//                                     qDebug()<<button->text();
//                                     Memory_Scene->removeItem(PointersToButtonsDrawn[i]);
//                            }
//                             else
//                            {
//                                     button->setStyleSheet(" QPushButton{ background-color:black; color:white; font-size: 17px; font-family: Arial;border-radius: 10%;} "
//                                                           "QPushButton:hover { background-color: white; border-radius:10%;border-width: 0.5px; border-style: solid; border-color: gray ;color:black;} ");

//                                     button->setText("Hole");
//                        }
//                        }
//                        }

//                        }
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
