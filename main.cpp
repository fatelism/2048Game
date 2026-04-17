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
#include "menu.h"

board gameMainBoard;

int main(){
    
    init();
    srand(time(NULL));


    while(1){
        int mode=printMenu();

        if(mode==0)return 0;
        else if(mode==1)gameMode1(gameMainBoard); 
        else if(mode==2)gameMode2(gameMainBoard);
        else if(mode==3)gameIntroduction();

        system("cls");
    }
    
}