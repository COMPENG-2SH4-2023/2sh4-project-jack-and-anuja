#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    objPos tempPos;
    tempPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

    playerPosList = new objPosArrayList();
    playerPosList->insertHead(tempPos);

}


Player::~Player()
{
    // delete any heap members here
    delete playerPosList;
}

objPosArrayList* Player::getPlayerPos(){ //Iteration 3 change
    return playerPosList;
}

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
        if (currHead.x == 1){
            currHead.x = BoardX - 1;
        }
        currHead.x--;
        break;

    case RIGHT:
        if (currHead.x == BoardX - 2){
            currHead.x = 0;
        }
        currHead.x++;
        break;

    case UP:
        if (currHead.y == 1){
            currHead.y = BoardY - 1;
        }
        currHead.y--;
        break;

    case DOWN:
        if (currHead.y == BoardY - 2){
            currHead.y = 0;
        }
        currHead.y++;
        break;
    default:
        break;
    }

    playerPosList->insertHead(currHead);

}


bool Player::checkFoodConsumption(){

    objPos newHead;
    playerPosList->getHeadElement(newHead);

    objPos foodpos;
    mainFoodRef->getFoodPos(foodpos);

    if (newHead.isPosEqual(&foodpos))
    {
        return true;
    }
    else
    {
        playerPosList->removeTail();
        return false;
    }    
    
}

void Player::increasePlayerLength(){
    mainGameMechsRef->incrementScore();
    mainFoodRef->generateFood(playerPosList);    
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
