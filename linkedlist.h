#ifndef LINKEDLIST_H_INCLUDED
#define LINKEDLIST_H_INCLUDED

#include"object.h"

object *pfirst=NULL, *pthis, *pnew;

namespace linkedlist{
    void getnode(shape s,int x1,int y1,int x2, int y2){
        pnew = new object(s);
        pnew->setInital(x1,y1);
        pnew->setFinal(x2,y2);
        pnew->setNext(NULL);
    }
    void insertfrombeginning(shape s,int x1,int y1,int x2, int y2)
    {
        getnode(s,x1,y1,x2,y2);
        pnew->setNext(pfirst);
        pfirst= pnew;
    }
    void insertfromend(shape s,int x1,int y1,int x2, int y2)
    {
        if(pfirst==NULL){
            insertfrombeginning(s,x1,y1,x2,y2);
        }else{
            pthis = pfirst;
            while(pthis->getNext()!=NULL){
                pthis = pthis->getNext();
            }
            getnode(s,x1,y1,x2,y2);
            pthis->setNext(pnew);
        }
    }
    void display(){
        pthis = pfirst;
        while(pthis!=NULL){
            pthis->drawObject();
            pthis=pthis->getNext();
        }
    }
}


#endif // LINKEDLIST_H_INCLUDED
