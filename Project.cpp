#include <iostream>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Player.h"


using namespace std;

#define DELAY_CONST 100000

GameMechs* myGM;
Player* myPlayer;

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

    myGM = new GameMechs(20, 10);
    myPlayer = new Player(myGM);

}

void GetInput(void)
{

}

void RunLogic(void)
{
    myPlayer->updatePlayerDir();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    for (int row = 0; row < myGM.getBoardSizeY(); row++){
        for (int col = 0; col < myGM.getBoardSizeX(); col++){
            if (row == 0 || row == myGM.getBoardSizeY() - 1 || col == 0 || col == myGM.getBoardSizeY() - 1){
                MacUILib_printf("#");
            }
            else if (row == myPlayer.x && col == myPlayer.y){
                MacUILib_printf("%c", myPlayer.symbol);
            }
            else{
                MacUILib_printf(" ");
            }
        }
        MacUILib_printf("\n"); // Move to the next row
    }

    if(myGM.getLoseFlagStatus() == true){
        MacUILib_printf("You Lose");
    }

}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST); // 0.1s delay
}


void CleanUp(void)
{
    MacUILib_clearScreen();    
  
    MacUILib_uninit();
}
