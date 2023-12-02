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
    myPlayer = new Player(myGM, myFood);
    myFood = new Food(myGM);

    objPos position;
    myPlayer->getPlayerPos(position);

    myFood->generateFood(position);

}

void GetInput(void)
{
    myGM->getInput();
}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
    myPlayer->movePlayer();

    myGM->clearInput();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    objPos tempPos;
    myPlayer->getPlayerPos(tempPos);

    objPos tempFood;
    myFood->getFoodPos(tempFood);

    for (int row = 0; row < myGM->getBoardSizeY(); row++){
        for (int col = 0; col < myGM->getBoardSizeX(); col++){
            if (row == 0 || row == myGM->getBoardSizeY() - 1 || col == 0 || col == myGM->getBoardSizeX() - 1){
                MacUILib_printf("#");
            }
            else if (row == tempPos.y && col == tempPos.x){
                MacUILib_printf("%c", tempPos.symbol);
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
    //MacUILib_printf("Score: %d", myGM->getScore);
    MacUILib_printf("Character Postions<%d>,<%d>\n",tempPos.x,tempPos.y);
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
