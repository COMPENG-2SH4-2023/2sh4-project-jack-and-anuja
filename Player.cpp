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
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
    playerPosList->insertHead(tempPos);
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
    playerPosList->removeTail();
}

bool checkFoodConsumption(){

}

void increasePlayerLength(){

}

bool checkSelfCollision(){

}
