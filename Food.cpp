#include <time.h>
#include <cstdlib>
#include "MacUILib.h"
#include "Food.h"
#include "Player.h"

Food::Food(GameMechs* thisGMRef){
    mainGameMechsRef = thisGMRef;
    foodPos.setObjPos(-1,-1,'$');
}

Food::~Food(){

}

void Food::generateFood(objPosArrayList* blockOff) {

    
    int xRange = mainGameMechsRef->getBoardSizeX() - 2;
    int yRange = mainGameMechsRef->getBoardSizeY() - 2;

    foodPos.x = 1 + rand() % xRange;
    foodPos.y = 1 + rand() % yRange;

    // Ensure food is not generated on snake body 
     for (int i = 0; i < blockOff->getSize(); ++i) {
        objPos playerPos;
        blockOff->getElement(playerPos, i);

        while(foodPos.x == playerPos.x && foodPos.y == playerPos.y){
            foodPos.x = 1 + rand() % xRange;
            foodPos.y = 1 + rand() % yRange;
        }

    }
    
}

void Food::getFoodPos(objPos &returnPos){
    returnPos.setObjPos(foodPos.x, foodPos.y, foodPos.symbol);
}