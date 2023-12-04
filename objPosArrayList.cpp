#include "objPosArrayList.h"

objPosArrayList::objPosArrayList()
{
    aList = new objPos[ARRAY_MAX_CAP]; // 200 elements on hap
    sizeArray = ARRAY_MAX_CAP;
    sizeList = 0;
}

objPosArrayList::~objPosArrayList()
{
    delete[] aList;
}

int objPosArrayList::getSize()
{
    return sizeList;
}

void objPosArrayList::insertHead(objPos thisPos)
{
    // Move all parts of snake backwards 1 and insert a new head
    for(int i = sizeList; i > 0; i--){
        aList[i].setObjPos(aList[i-1]);
        if(sizeList == sizeArray){
            break;
        }    
    }

    aList[0].setObjPos(thisPos);        
    sizeList++;
}

void objPosArrayList::insertTail(objPos thisPos)
{
    // move all parts of the snake forward 1
    for(int i = 0; i < sizeList; i++){
        aList[i+1].setObjPos(aList[i]);
        if(sizeList == sizeArray){
            break;
        }    
    }

    aList[sizeList].setObjPos(thisPos);        
    sizeList++;
}

void objPosArrayList::removeHead()
{
    if (sizeList > 0) {
        for (int i = 0; i < sizeList - 1; i++) { //Sizelist -1
            aList[i].setObjPos(aList[i + 1]);
        }
        sizeList--;
    }
}

void objPosArrayList::removeTail()
{

    if(sizeList == 0){
        ;
    }

    else{
        sizeList--;
    }
    
}

void objPosArrayList::getHeadElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[0]);
}

void objPosArrayList::getTailElement(objPos &returnPos)
{
    returnPos.setObjPos(aList[sizeList-1]);
}

void objPosArrayList::getElement(objPos &returnPos, int index)
{
    returnPos.setObjPos(aList[index]);
}