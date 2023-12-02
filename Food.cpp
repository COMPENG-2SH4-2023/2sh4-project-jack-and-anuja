#include <time.h>
#include <cstdlib>
#include "MacUILib.h"
#include "Food.h"
#include "Player.h"

Food::Food(GameMechs* thisGMRef){
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1,-1,'o');
}

Food::~Food(){

}

void Food::generateFood(objPos blockOff){

    foodPos.x = 1 + rand() % mainGameMechsRef->getBoardSizeX() - 2;
    foodPos.y = 1 + rand() % mainGameMechsRef->getBoardSizeY() - 2;

    while(foodPos.x == blockOff.x && foodPos.y == blockOff.y){
        foodPos.x = 1 + rand() % mainGameMechsRef->getBoardSizeX() - 2;
        foodPos.y = 1 + rand() % mainGameMechsRef->getBoardSizeY() - 2;
    }


/*
    while(foodPos.x == blockOff.x && foodPos.y == blockOff.y){
        foodPos.x = 1 + rand() % mainGameMechsRef->getBoardSizeX() - 2;
        foodPos.y = 1 + rand() % mainGameMechsRef->getBoardSizeY() - 2;
    }
*/
}

void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}