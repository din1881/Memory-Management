#include "alg.h"

void Best_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h){
qDebug()<<"best fit";
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
            if(h[i]->startingAddress == (h[j]->startingAddress+h[j]->size) && (h[j]->startingAddress != h[i]->startingAddress) ){
                h[j]->size= h[i]->size+h[j]->size;
                h.erase(h.begin()+i);
                break;
            }
        }

    }

    for(int i=0; i<h.size();i++){
        qDebug()<<"after compaction"<<h[i]->size <<"and add"<<h[i]->startingAddress;
    }
    //sorting holes according to size
    for (int i = 0; i < h.size(); i++) {
            for (int j = 0; j < h.size(); j++) {
                if (h[i]->size < h[j]->size) {
                    Holes* temp = h[j];
                    h[j] = h[i];
                    h[i] = temp;
                }
            }

        }

    for (int i = 0; i < s.size(); i++) {
            for (int j = 0; j < h.size(); j++) {
                if ((s[i]->size <= h[j]->size) &&s[i]->segmentName != "Reserved") {
                    s[i]->startingAddress=h[j]->startingAddress;
                    //to fill the large vector of segments of all processes to be drawn
                    large_Seg.push_back(s[i]);
                    //decrease the size of the hole
                        h[j]->size=h[j]->size-s[i]->size;
                        h[j]->startingAddress=h[j]->startingAddress+s[i]->size;
                        if(h[j]->size == 0) h.erase(h.begin()+j);
                        break;



                }

            }
        }

    //delete the small seg so that it can be filled again from the user
    s.clear();
    for (int i = 0; i < h.size(); i++) {
            for (int j = 0; j < h.size(); j++) {
                if (h[i]->startingAddress < h[j]->startingAddress) {
                    Holes* temp = h[j];
                    h[j] = h[i];
                    h[i] = temp;
                }
            }

        }

}

void First_fit(QVector<Segments *> &s, QVector<Segments *> &large_Seg,QVector <Holes *> &h)
{
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
            if(h[i]->startingAddress == (h[j]->startingAddress+h[j]->size) && (h[j]->startingAddress != h[i]->startingAddress) ){
                h[j]->size= h[i]->size+h[j]->size;
                h.erase(h.begin()+i);
                break;
            }
        }

    }

    for (int i = 0; i < s.size(); i++)
    {
            for (int j = 0; j < h.size(); j++)
            {
                if ((s[i]->size <= h[j]->size) &&s[i]->segmentName != "Reserved")
                {
                    s[i]->startingAddress=h[j]->startingAddress;
                    //to fill the large vector of segments of all processes to be drawn
                    large_Seg.push_back(s[i]);
                    //decrease the size of the hole
                    h[j]->size=h[j]->size-s[i]->size;
                    h[j]->startingAddress=h[j]->startingAddress+s[i]->size;
                    if(h[j]->size == 0) h.erase(h.begin()+j);
                    break;
                }

            }
        }

    //delete the small seg so that it can be filled again from the user
    s.clear();
    for (int i = 0; i < h.size(); i++) {
            for (int j = 0; j < h.size(); j++) {
                if (h[i]->startingAddress < h[j]->startingAddress) {
                    Holes* temp = h[j];
                    h[j] = h[i];
                    h[i] = temp;
                }
            }

        }
}


void Deallocate(QVector<Segments *> &s, QVector <Holes *> &h, int index){
    qDebug()<<"Deallocate Triggered";
    int found_flag =0;

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
            qDebug()<<" is it>"<<s[index]->segmentName<<index;
            s.erase(s.begin()+i);
            h.append(new_hole);
            qDebug()<<"holes size after appending"<<h.size();
        }
    }



//    //add hole with same size of the segment
//    Holes *new_hole = new Holes();
//    new_hole->startingAddress =s[index]->startingAddress;
//    new_hole->size= s[index]->size;
//    qDebug()<<" is it>"<<s[index]->segmentName<<index;
//    s.erase(s.begin()+index);
//    h.append(new_hole);
//    qDebug()<<"holes size after appending"<<h.size();

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
    qDebug()<<"holes size afterrrrrr appending"<<h.size();
    //for compaction
//    for(int i=0; i<h.size();i++){
//        if((new_hole->startingAddress == (h[i]->startingAddress+h[i]->size -1)) || ( h[i]->startingAddress ==(new_hole->startingAddress+new_hole->size-1))){
//            h[i]->size= h[i]->size+new_hole->size;
//            found_flag=1;
//            break;
//        }
//    }

//    if(found_flag == 0){
//        h.append(new_hole);
//    }
}

//void Deallocate(QVector<Segments *> &s, QVector <Holes *> &h, int y_button, int w_button){

    //add a new hole
  //  Holes* new_hole = new Holes();
    //new_hole->size=w_button;
    //new_hole->startingAddress=y_button;
    //h.append(new_hole);

    //delete the segment from the vector
    //for(int i=0; i<s.size();i++){
      //  if(s[i]->startingAddress==y_button){
        //    s.erase(s.begin()+i);
          //  break;
       // }
   // }

//}

void get_segment_table (QVector<Segments *> &table,QVector<Segments *> &large_seg, QString name){
    for(int i=0; i<large_seg.size();i++){
        if(large_seg[i]->processName == name){
            table.push_back(large_seg[i]);
        }
    }
}
