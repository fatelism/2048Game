/*
time:2026.04.12 21:45
author:fatelism
*/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <cstring>
#include <Windows.h>
#include "board.h"

void init(){
    std::cout << "     \033[1;31m" << "Welcome to 2048 " << "\033[0m" << std::endl;
    system("pause");
}


board gameMainBoard;


int main(){
    
    init();
    
    srand(time(NULL));

    // gameMainBoard.setPoint(1,1,8192);
    // gameMainBoard.setPoint(1,2,8192);
    // gameMainBoard.setPoint(1,3,8192);
    // gameMainBoard.setPoint(1,4,8192);
    // gameMainBoard.setPoint(2,1,2048);
    // gameMainBoard.setPoint(2,2,1000);
    // gameMainBoard.setPoint(2,3,2000);
    // gameMainBoard.setPoint(2,4,3000);
    while(1){
        gameMainBoard.blockSpawn();
        gameMainBoard.printBoard();

        if(gameMainBoard.checkGameEnd()==1){
            
            gameMainBoard.updateMaximumScore();

            if(gameMainBoard.gameEnd()==1)break;
            else{
                gameMainBoard.gameRestart();
                continue;
            }
        }

        // Sleep(200);

        int inputStatus=gameMainBoard.blockMove();
        if(inputStatus==-1)break;
        else gameMainBoard.addScore(inputStatus);

        
    }
    
}