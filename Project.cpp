#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"
#include "Food.h"
#include "objPosArrayList.h"
#include <time.h>

using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;
Food* myFood;

bool exitFlag;

void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);



int main(void)
{

    Initialize();

    while(myGM->getExitFlagStatus() == false)  
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();

}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();
    srand(time(NULL));

    myGM = new GameMechs(30, 15);
    myFood = new Food(myGM);
    myPlayer = new Player(myGM, myFood);
    

    //Tester setup
    objPosArrayList* playerBody2 = myPlayer->getPlayerPos();
    myFood->generateFood(playerBody2);

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();
    if (myPlayer->checkSelfCollision()){
        myGM->setLoseFlag();
        myGM->setExitTrue();
    }

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    bool drawn;

    objPosArrayList* playerBody = myPlayer->getPlayerPos();
    objPos tempBody;

    objPos tempFood;
    myFood->getFoodPos(tempFood);

    for (int row = 0; row < myGM->getBoardSizeY(); row++){
        for (int col = 0; col < myGM->getBoardSizeX(); col++){

            drawn = false;

            for(int i = 0; i < playerBody->getSize(); i++){
                playerBody->getElement(tempBody, i);
                if(tempBody.y == row && tempBody.x == col){
                    MacUILib_printf("%c", tempBody.symbol);
                    drawn = true;
                    break;
                }
            }

            if(drawn) continue;

            if (row == 0 || row == myGM->getBoardSizeY() - 1 || col == 0 || col == myGM->getBoardSizeX() - 1){
                MacUILib_printf("#");
            }

            else if(row == tempFood.y && col == tempFood.x){
                MacUILib_printf("%c", tempFood.symbol);
            }

            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); // Move to the next row
    }

    if(myGM->getLoseFlagStatus() == true){
        MacUILib_printf("You Lose");
    }
    MacUILib_printf("Score: %d\n", myGM->getScore());
    
    for(int p = 0; p < playerBody->getSize(); p++){
        playerBody->getElement(tempBody, p);
        MacUILib_printf("Character Postions<%d>,<%d>\n",tempBody.x,tempBody.y);
    }
    MacUILib_printf("Food Positions<%d>,<%d>", tempFood.x, tempFood.y);
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();

    delete myGM;
    delete myPlayer;
    delete myFood;
}
