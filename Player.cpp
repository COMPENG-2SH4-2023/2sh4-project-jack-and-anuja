#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    //playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');
    //No longer true

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

    //Debugging method -> insert 4 segments
    // playerPosList->insertHead(tempPos);
   //playerPosList->insertHead(tempPos);
   // playerPosList->insertHead(tempPos);
   // playerPosList->insertHead(tempPos);
}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos(){ //Iteration 3 change
    return playerPosList;
}

/*
void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
}
*/
void Player::updatePlayerDir()
{
    // PPA3 input processing logic     
    char input = mainGameMechsRef->getInput();

    switch(input){      //How do u get input. GameMechs * 
        case 'w':
            if(myDir != DOWN){
            myDir = UP;
            }
            break;

        case 'a':
            if(myDir != RIGHT){
            myDir = LEFT;
            }
            break;

        case 's':
            if(myDir != UP){
            myDir = DOWN;
            }
            break;

        case 'd':
            if(myDir != LEFT){
            myDir = RIGHT;
            }
            break;

        default:
            break;
    }
}

void Player::movePlayer()
{

    objPos currHead;    //Holding pos of current head
    playerPosList->getHeadElement(currHead);

    int BoardX = mainGameMechsRef->getBoardSizeX();
    int BoardY = mainGameMechsRef->getBoardSizeY();
    // PPA3 Finite State Machine logic
    switch (myDir){
    case LEFT:
        if (currHead.x == 0){
            currHead.x = BoardX - 1;
        }
        currHead.x--;
        break;

    case RIGHT:
        if (currHead.x == BoardX - 1){
            currHead.x = 0;
        }
        currHead.x++;
        break;

    case UP:
        if (currHead.y == 0){
            currHead.y = BoardY - 1;
        }
        currHead.y--;
        break;

    case DOWN:
        if (currHead.y == BoardY - 1){
            currHead.y = 0;
        }
        currHead.y++;
        break;
    default:
        break;
    }

    playerPosList->insertHead(currHead);

    objPos newHead;

    playerPosList->getHeadElement(newHead);

    objPos foodpos;
    mainFoodRef->getFoodPos(foodpos);
  
    // Now, you can use 'foodpos' to access the food's position.

    if (newHead.isPosEqual(&foodpos))
    {
        // Collision with food
        mainGameMechsRef->incrementScore();
        mainFoodRef->generateFood(playerPosList); // Generate new food
    }
    else
    {
        playerPosList->removeTail();
    }


}

   
    


    // Check if head position colides with food
    // if yes then increment the score in GM, generate new food, and do not move the tail
    // otherwise remove tail and move on
    

    
    
    
    



bool checkFoodConsumption(){

    
}

void increasePlayerLength(){

}

bool Player::checkSelfCollision() {
    objPos headPos;
    playerPosList->getHeadElement(headPos);

    // Iterate through the snake's body (excluding the head)
    for (int i = 1; i < playerPosList->getSize(); ++i) {
        objPos bodyPos;
        playerPosList->getElement(bodyPos, i);

        // Check for collision with body segment
        if (headPos.isPosEqual(&bodyPos)) {
            return true;  // Collision detected
        }
    }

    return false;  // No collision with self
}
