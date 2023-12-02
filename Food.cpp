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

    int xRange = mainGameMechsRef->getBoardSizeX() - 2;
    int yRange = mainGameMechsRef->getBoardSizeY() - 2;

    foodPos.x = 1 + rand() % xRange;
    foodPos.y = 1 + rand() % yRange;

    while(foodPos.x == blockOff.x && foodPos.y == blockOff.y){
        foodPos.x = 1 + rand() % xRange;
        foodPos.y = 1 + rand() % yRange;
    }

}

void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}