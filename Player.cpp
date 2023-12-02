#include "Player.h"


Player::Player(GameMechs* thisGMRef, Food* thisFoodRef)
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP;

    // more actions to be included
    playerPos.setObjPos(mainGameMechsRef->getBoardSizeX()/2, mainGameMechsRef->getBoardSizeY()/2, '@');

}


Player::~Player()
{
    // delete any heap members here

}

void Player::getPlayerPos(objPos &returnPos)
{
    // return the reference to the playerPos arrray list
    returnPos.setObjPos(playerPos.x, playerPos.y, playerPos.symbol);
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
    int BoardX = mainGameMechsRef->getBoardSizeX();
    int BoardY = mainGameMechsRef->getBoardSizeY();
    // PPA3 Finite State Machine logic
    switch (myDir){
    case LEFT:
        if (playerPos.x == 0){
            playerPos.x = BoardX - 1;
        }
        playerPos.x--;
        break;

    case RIGHT:
        if (playerPos.x == BoardX - 1){
            playerPos.x = 0;
        }
        playerPos.x++;
        break;

    case UP:
        if (playerPos.y == 0){
            playerPos.y = BoardY - 1;
        }
        playerPos.y--;
        break;

    case DOWN:
        if (playerPos.y == BoardY - 1){
            playerPos.y = 0;
        }
        playerPos.y++;
        break;

    default:
        break;
    }
}

bool checkFoodConsumption(){

}

void increasePlayerLength(){

}

bool checkSelfCollision(){

}
