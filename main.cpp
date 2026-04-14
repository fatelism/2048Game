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

void gameEnd(){
    std::cout<<"Game is end.\nYour final score: ";
    gameMainBoard.printScore();
    std::cout<<std::endl;
    system("pause");
}

int main(){
    
    init();
    
    srand(time(NULL));

    while(1){
        gameMainBoard.blockSpawn();
        gameMainBoard.printBoard();
        if(gameMainBoard.checkGameEnd()==1)break;

        Sleep(200);

        int inputStatus=gameMainBoard.blockMove();
        if(inputStatus==-1)break;
        else gameMainBoard.addScore(inputStatus);

        
    }
    gameEnd();
}