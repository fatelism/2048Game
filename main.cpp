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
    std::cout<<"Game end.\nYour final score: ";
    gameMainBoard.printScore();
    std::cout<<std::endl;
    system("pause");
}

int main(){
    init();
    
    srand(time(NULL));

    // gameMainBoard.setPoint(1,1,2);
    // gameMainBoard.setPoint(1,2,4);
    // gameMainBoard.setPoint(1,3,8);
    // gameMainBoard.setPoint(1,4,16);
    // gameMainBoard.setPoint(2,1,32);
    // gameMainBoard.setPoint(2,2,64);
    // gameMainBoard.setPoint(2,3,128);
    // gameMainBoard.setPoint(2,4,256);
    // gameMainBoard.setPoint(3,1,2);
    // gameMainBoard.setPoint(3,2,4);
    // gameMainBoard.setPoint(3,3,8);
    // gameMainBoard.setPoint(3,4,16);

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