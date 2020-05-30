#include "alg.h"

void compact(QVector <Holes *> &h){
    //sorting holes according to address
    for (int i = 0; i < h.size(); i++)
    {
        for (int j = 0; j < h.size(); j++)
        {
            if (h[i]->startingAddress < h[j]->startingAddress)
        {
                Holes* temp = h[j];
                h[j] = h[i];
                h[i] = temp;
            }
        }

    }
    for(int i=0; i<h.size();i++){
        for(int j=0; j<h.size();j++){
            if(h[i]->startingAddress == (h[j]->startingAddress+h[j]->size) && (h[j]->startingAddress != h[i]->startingAddress) ){
                h[j]->size= h[i]->size+h[j]->size;
                h.erase(h.begin()+i);
                break;
            }
        }

    }
    for(int i=0; i<h.size();i++){
        qDebug()<<"after compaction new"<<h[i]->size <<"and add"<<h[i]->startingAddress;
    }
}

void sort_Holes_Size(QVector <Holes *> &h){
    for (int i = 0; i < h.size(); i++) {
            for (int j = 0; j < h.size(); j++) {
                if (h[i]->size < h[j]->size) {
                    Holes* temp = h[j];
                    h[j] = h[i];
                    h[i] = temp;
                }
            }

        }
}

void Best_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h){
qDebug()<<"best fit";
int allocated_flag=0;

    compact(h);           //for compaction

    for(int i=0; i<h.size();i++){
        qDebug()<<"after compaction"<<h[i]->size <<"and add"<<h[i]->startingAddress;
    }

    sort_Holes_Size(h);      //sorting holes according to size


    //vector to check if the allocation process will successed or not
    QVector <Segments *> test_s;

    //Best fit alg
     for (int i = 0; i < s.size(); i++) {

             for (int j = 0; j < h.size(); j++) {
                 sort_Holes_Size(h);
                 if ((s[i]->size <= h[j]->size) &&s[i]->segmentName != "Reserved") {
                     s[i]->startingAddress=h[j]->startingAddress;
                     //to fill the large vector of segments of all processes to be drawn
                     test_s.push_back(s[i]);
                     allocated_flag++;

                     //decrease the size of the hole
                         h[j]->size=h[j]->size-s[i]->size;
                         h[j]->startingAddress=h[j]->startingAddress+s[i]->size;
                         if(h[j]->size == 0) h.erase(h.begin()+j);
                         break;
                 }

             }
         }

    //check if the allocation process failed
    if(allocated_flag != s.size()  && s.size() !=0){
        for (int i=0;i<allocated_flag;i++) {
            Holes* addh= new Holes;
            addh->size=test_s[i]->size;
            addh->startingAddress=test_s[i]->startingAddress;
            h.push_back(addh);

        }

        compact(h);
        QMessageBox *invalid_name = new QMessageBox;
        invalid_name->setText("Can't allocate the process");
        invalid_name->exec();

    }
    else {
        for(int i=0; i<test_s.size();i++){
            large_Seg.push_back(test_s[i]);
        }
    }

    //delete the small seg so that it can be filled again from the user
    s.clear();
    sort_Holes_Size(h);


}

void First_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h)
{
    int allocated_flag=0;
    //sorting holes according to address
    for (int i = 0; i < h.size(); i++)
    {
        for (int j = 0; j < h.size(); j++)
        {
            if (h[i]->startingAddress < h[j]->startingAddress)
        {
                Holes* temp = h[j];
                h[j] = h[i];
                h[i] = temp;
            }
        }

    }

   compact(h); //for compaction

   //vector to check if the allocation process will successed or not
   QVector <Segments *> test_s;

    for (int i = 0; i < s.size(); i++)
    {
            for (int j = 0; j < h.size(); j++)
            {
                if ((s[i]->size <= h[j]->size) &&s[i]->segmentName != "Reserved")
                {
                    s[i]->startingAddress=h[j]->startingAddress;
                    //to fill the large vector of segments of all processes to be drawn
                    test_s.push_back(s[i]);
                    allocated_flag++;
                    //decrease the size of the hole
                    h[j]->size=h[j]->size-s[i]->size;
                    h[j]->startingAddress=h[j]->startingAddress+s[i]->size;
                    if(h[j]->size == 0) h.erase(h.begin()+j);
                    break;
                }

            }
        }

    //check if the allocation process failed
    if(allocated_flag != s.size()  && s.size() !=0){
        //large_Seg.clear();
        QMessageBox *invalid_name = new QMessageBox;
        invalid_name->setText("Can't allocate the process");
        invalid_name->exec();

    }

    //check if the allocation process failed
    if(allocated_flag != s.size()  && s.size() !=0){
        for (int i=0;i<allocated_flag;i++) {
            Holes* addh= new Holes;
            addh->size=test_s[i]->size;
            addh->startingAddress=test_s[i]->startingAddress;
            h.push_back(addh);

        }
        compact(h);
        QMessageBox *invalid_name = new QMessageBox;
        invalid_name->setText("Can't allocate the process");
        invalid_name->exec();

    }
    else {
        for(int i=0; i<test_s.size();i++){
            large_Seg.push_back(test_s[i]);
        }
    }

    //delete the small seg so that it can be filled again from the user
    s.clear();
    sort_Holes_Size(h);
}


void Deallocate(QVector<Segments *> &s, QVector <Holes *> &h, int index){
    qDebug()<<"Deallocate Triggered";

    //sorting according to address
    for (int i = 0; i < s.size(); i++)
    {
        for (int j = 0; j < s.size(); j++)
        {
            if (s[i]->startingAddress < s[j]->startingAddress)
        {
                Segments* temp = s[j];
                s[j] = s[i];
                s[i] = temp;
            }
        }

    }

    Segments *new_seg = new Segments();
    new_seg= s[index];

    for(int i=0; i<s.size();i++){
        if(s[i]->processName == new_seg->processName){
            //add hole with same size of the segment
            Holes *new_hole = new Holes();
            new_hole->startingAddress =s[i]->startingAddress;
            new_hole->size= s[i]->size;
            s.erase(s.begin()+i);
            i--;
            h.append(new_hole);
        }
    }



    //sorting holes according to address
    for (int i = 0; i < h.size(); i++)
    {
        for (int j = 0; j < h.size(); j++)
        {
            if (h[i]->startingAddress < h[j]->startingAddress)
        {
                Holes* temp = h[j];
                h[j] = h[i];
                h[i] = temp;
            }
        }

    }

    //for compaction
    for(int i=0; i<h.size();i++){
        for(int j=0; j<h.size();j++){
            if(h[i]->startingAddress == (h[j]->startingAddress+h[j]->size ) && (h[j]->startingAddress != h[i]->startingAddress) ){
                qDebug()<<"hi"<<h[j]->startingAddress<<" "<<h[j]->size;
                h[j]->size= h[i]->size+h[j]->size;
                h.erase(h.begin()+i);
                i=0;
                break;
            }
        }

    }


}



void get_segment_table (QVector<Segments *> &table,QVector<Segments *> &large_seg, QString name){
    for(int i=0; i<large_seg.size();i++){
        if(large_seg[i]->processName == name){
            table.push_back(large_seg[i]);
        }
    }
}
