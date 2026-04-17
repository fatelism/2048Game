#include <cstring>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include "color.h"





void init(){
    std::cout << "        \033[1;31m" << "Welcome to 2048 " << "\033[0m" << std::endl;
}

int printMenu(){
    std::cout<<"       菜单(按下q退出游戏)"<<std::endl;
    std::cout<<"          1.经典模式"<<std::endl;
    std::cout<<"          2.特殊模式"<<std::endl;
    std::cout<<"       3.特殊模式玩法说明"<<std::endl;

    char userInput=_getch();
    while(1){
        if(userInput=='1'){
            return 1;
        }
        else if(userInput=='2'){
            return 2;
        }
        else if(userInput=='3'){
            return 3;
        }
        else if(userInput=='q'){
            return 0;
        }

        userInput=_getch();
    }
}


void gameMode1(board gameMainBoard){

    system("cls");

    while(1){
        gameMainBoard.blockSpawn();
        gameMainBoard.printBoard(1);

        if(gameMainBoard.checkGameEnd()==1){
            
            gameMainBoard.updateMaximumClassicScore();

            if(gameMainBoard.gameEnd()==1)break;
            else{
                restart:
                gameMainBoard.gameRestart();
                continue;
            }
        }

        int inputStatus=gameMainBoard.blockMove();
        if(inputStatus==-1)break;
        else if(inputStatus==-2)goto restart;
        else gameMainBoard.addScore(inputStatus);

    }
}

void gameMode2(board gameMainBoard){
    
    system("cls");
    
    int round=0;
    while(1){
        
        if(round>0&&round%10==0){
            gameMainBoard.barrierSpawn();
        }

        gameMainBoard.blockSpawn();
        gameMainBoard.printBoard(2);

        if(gameMainBoard.checkGameEnd()==1){
            
            gameMainBoard.updateMaximumSpecialScore();

            if(gameMainBoard.gameEnd()==1)break;
            else{
                restart:
                gameMainBoard.gameRestart();
                continue;
            }
        }

        int inputStatus=gameMainBoard.blockMove();
        if(inputStatus==-1)break;
        else if(inputStatus==-2)goto restart;
        else gameMainBoard.addScore(inputStatus);

        if(round>10&&round%10==4){
            gameMainBoard.barrierEliminate();
        }

        round++;
    }
}

void gameIntroduction(){
    system("cls");

    std::cout<<"       本模式其余玩法与标准2048一致，"<<std::endl;
    std::cout<<"       不同之处在于，每10次移动会生成一个持续5回合的障碍，"<<std::endl;
    std::cout<<"       该障碍无法移动，无法被穿过。"<<std::endl;
    std::cout<<"       且保证在空余位置不大于3个时不会生成。"<<std::endl;
    std::cout<<"       （按下q键返回）"<<std::endl;

    char userInput=_getch();
    while(1){
        if(userInput=='q'){
            system("cls");
            return;
        }

        userInput=_getch();
    }
}