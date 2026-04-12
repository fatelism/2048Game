/*
time:2026.04.12 21:45
author:fatelism
*/

#include <iostream>
#include <time.h>
#include <conio.h>
#include <cstring>
#include <Windows.h>

void init(){
    std::cout << "\033[1;31m" << "Welcome to 2048 " << "\033[0m" << std::endl;
    system("pause");
}
int countDigit(int x){
    int digit=0;
    while(x>0){
        digit++;
        x/=10;
    }
    return digit;
}

class board{
    private:
        int occupyPoint[6][6];
    
    public:
        void boardInit(){
            memset(occupyPoint,0,sizeof(occupyPoint));
        }

        void setPoint(int n,int m,int z){
            occupyPoint[n][m]=z;
        }

        void printBlockUp(int n,int m){
            if(occupyPoint[n][m]){
                std::cout<<"┌─────┐";
            }
            else{
                std::cout<<"       ";
            }
        }

        void printBlockDown(int n,int m){
            if(occupyPoint[n][m]){
                std::cout<<"└─────┘";
            }
            else{
                std::cout<<"       ";
            }
        }

        void printBlockMid(int n,int m){
            if(occupyPoint[n][m]){
                std::cout<<"│     │";
            }
            else{
                std::cout<<"       ";
            }
        }

        void printBlockNumber(int n,int m){
            if(occupyPoint[n][m]){
                std::cout<<"│";
                for(int i=1;i<=(5-countDigit(occupyPoint[n][m]))/2;i++)std::cout<<" ";
                std::cout<<occupyPoint[n][m];
                for(int i=(5-countDigit(occupyPoint[n][m]))/2+countDigit(occupyPoint[n][m])+1;i<=5;i++)std::cout<<" ";
                std::cout<<"│";
            }
            else{
                std::cout<<"       ";
            }
        }

        void printBlock(int line){
            std::cout<<"║";
                        for(int column=1;column<=4;column++){
                            printBlockUp(line,column);
                        }
                                         std::cout<<"║"<<std::endl;

            std::cout<<"║";
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<"║"<<std::endl;
            
            std::cout<<"║";
                        for(int column=1;column<=4;column++){
                            printBlockNumber(line,column);
                        }
                                         std::cout<<"║"<<std::endl;

            std::cout<<"║";
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<"║"<<std::endl;
                                         
            std::cout<<"║";
                        for(int column=1;column<=4;column++){
                            printBlockDown(line,column);
                        }
                                         std::cout<<"║"<<std::endl;
        }

        void printBoard(){
            std::cout<<"╔════════════════════════════╗"<<std::endl;

            for(int line=1;line<=4;line++){
                printBlock(line);
            }

            std::cout<<"╚════════════════════════════╝"<<std::endl;
        }
        
        void blockSpawn(){

            int line=rand()%4+1,column=rand()%4+1;
            while(occupyPoint[line][column]){
                line=rand()%4+1,column=rand()%4+1;
            }

            occupyPoint[line][column]=2;
        }

        void blockMove(){

            char keyboardInput=_getch();

            if(keyboardInput=='a'){

                for(int line=1;line<=4;line++){
                    for(int column=1;column<=4;column++){
                        for(int aimcolumn=1;aimcolumn<column;aimcolumn++){
                            if(!occupyPoint[line][aimcolumn]&&occupyPoint[line][column]){
                                occupyPoint[line][aimcolumn]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=2;column<=4;column++){
                        if(occupyPoint[line][column]==occupyPoint[line][column-1]){
                            occupyPoint[line][column-1]*=2;
                            occupyPoint[line][column]=0;
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=1;column<=4;column++){
                        for(int aimcolumn=1;aimcolumn<column;aimcolumn++){
                            if(!occupyPoint[line][aimcolumn]&&occupyPoint[line][column]){
                                occupyPoint[line][aimcolumn]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }
            }

            else if(keyboardInput=='d'){

                for(int line=1;line<=4;line++){
                    for(int column=4;column>=1;column--){
                        for(int aimcolumn=4;aimcolumn>column;aimcolumn--){
                            if(!occupyPoint[line][aimcolumn]&&occupyPoint[line][column]){
                                occupyPoint[line][aimcolumn]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=3;column>=1;column--){
                       if(occupyPoint[line][column]==occupyPoint[line][column+1]){
                            occupyPoint[line][column+1]*=2;
                            occupyPoint[line][column]=0;
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=4;column>=1;column--){
                        for(int aimcolumn=4;aimcolumn>column;aimcolumn--){
                            if(!occupyPoint[line][aimcolumn]&&occupyPoint[line][column]){
                                occupyPoint[line][aimcolumn]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }
            }
        }
}gameMainBoard;
int main(){
    // init();
    
    // gameMainBoard.setPoint(1,1,2);
    // gameMainBoard.setPoint(2,2,16);
    // gameMainBoard.setPoint(3,4,2048);
    // gameMainBoard.setPoint(4,1,256);
    // gameMainBoard.printBoard();
    // system("pause");
    srand(time(NULL));
    while(1){
        gameMainBoard.blockSpawn();
        gameMainBoard.printBoard();
        Sleep(200);
        gameMainBoard.blockMove();
    }
}