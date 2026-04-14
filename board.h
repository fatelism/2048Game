#include <cstring>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include "color.h"

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
        int totalScore;

    public:
        board(){
            memset(occupyPoint,0,sizeof(occupyPoint));
            totalScore=0;
        }

        void setPoint(int n,int m,int z){
            occupyPoint[n][m]=z;
        }

        void printBlockUp(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;

            if(occupyPoint[n][m]){
                std::cout<<"┌─────┐";
            }
            else{
                std::cout<<"       ";
            }

            std::cout<<RESETCOLOR;
        }

        void printBlockDown(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
            if(occupyPoint[n][m]){
                std::cout<<"└─────┘";
            }
            else{
                std::cout<<"       ";
            }
            
            std::cout<<RESETCOLOR;
        }

        void printBlockMid(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
            if(occupyPoint[n][m]){
                std::cout<<"│     │";
            }
            else{
                std::cout<<"       ";
            }
            
            std::cout<<RESETCOLOR;
        }

        void printBlockNumber(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
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
            
            std::cout<<RESETCOLOR;
        }

        void printBlock(int line){
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockUp(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;

            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
            
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockNumber(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;

            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
                                         
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockDown(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
        }

        void printBoard(){
            // std::cout << "\033[H\033[2J";
            std::cout << "\x1b[2J\x1b[H";
            std::cout.flush();
            std::cout<<BOLD<<"╔════════════════════════════╗";
            std::cout<<RESETCOLOR<<"                score: "<<totalScore<<std::endl;

            for(int line=1;line<=4;line++){
                printBlock(line);
            }

            std::cout<<BOLD<<"╚════════════════════════════╝"<<RESETCOLOR<<std::endl;
        }
        
        void blockSpawn(){

            int line=rand()%4+1,column=rand()%4+1;
            while(occupyPoint[line][column]){
                line=rand()%4+1,column=rand()%4+1;
            }

            occupyPoint[line][column]=2;
        }

        int blockMove(){
            userInput:

            char keyboardInput=_getch();
            int movementScore=0;
            bool ifVaildMovement=0;

            if(keyboardInput=='a'){

                for(int line=1;line<=4;line++){
                    for(int column=1;column<=4;column++){
                        for(int aimcolumn=1;aimcolumn<column;aimcolumn++){
                            if(!occupyPoint[line][aimcolumn]&&occupyPoint[line][column]){
                                occupyPoint[line][aimcolumn]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                                ifVaildMovement=1;
                            }
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=2;column<=4;column++){
                        if(occupyPoint[line][column]==occupyPoint[line][column-1]&&occupyPoint[line][column]>0){
                            occupyPoint[line][column-1]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line][column-1];
                            ifVaildMovement=1;
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
                                ifVaildMovement=1;
                            }
                        }
                    }
                }

                for(int line=1;line<=4;line++){
                    for(int column=3;column>=1;column--){
                       if(occupyPoint[line][column]==occupyPoint[line][column+1]&&occupyPoint[line][column]>0){
                            occupyPoint[line][column+1]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line][column+1];
                            ifVaildMovement=1;
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

            else if(keyboardInput=='w'){

                for(int column=1;column<=4;column++){
                    for(int line=1;line<=4;line++){
                        for(int aimline=1;aimline<line;aimline++){
                            if(!occupyPoint[aimline][column]&&occupyPoint[line][column]){
                                occupyPoint[aimline][column]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                                ifVaildMovement=1;
                            }
                        }
                    }
                }

                for(int column=1;column<=4;column++){
                    for(int line=2;line<=4;line++){
                        if(occupyPoint[line-1][column]==occupyPoint[line][column]&&occupyPoint[line][column]>0){
                            occupyPoint[line-1][column]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line-1][column];
                            ifVaildMovement=1;
                        }
                    }
                }

                for(int column=1;column<=4;column++){
                    for(int line=1;line<=4;line++){
                        for(int aimline=1;aimline<line;aimline++){
                            if(!occupyPoint[aimline][column]&&occupyPoint[line][column]){
                                occupyPoint[aimline][column]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }
            }

            else if(keyboardInput=='s'){

                for(int column=1;column<=4;column++){
                    for(int line=4;line>=1;line--){
                        for(int aimline=4;aimline>line;aimline--){
                            if(!occupyPoint[aimline][column]&&occupyPoint[line][column]){
                                occupyPoint[aimline][column]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                                ifVaildMovement=1;
                            }
                        }
                    }
                }

                for(int column=1;column<=4;column++){
                    for(int line=3;line>=1;line--){
                        if(occupyPoint[line+1][column]==occupyPoint[line][column]&&occupyPoint[line][column]>0){
                            occupyPoint[line+1][column]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line+1][column];
                            ifVaildMovement=1;
                        }
                    }
                }

                for(int column=1;column<=4;column++){
                    for(int line=4;line>=1;line--){
                        for(int aimline=4;aimline>line;aimline--){
                            if(!occupyPoint[aimline][column]&&occupyPoint[line][column]){
                                occupyPoint[aimline][column]=occupyPoint[line][column];
                                occupyPoint[line][column]=0;
                            }
                        }
                    }
                }
            }
            else if(keyboardInput=='q'){
                return -1;
            }

            else goto userInput;

            if(ifVaildMovement==0)goto userInput;
            else return movementScore;
        }

        void addScore(int x){
            totalScore+=x;
        }

        void printScore(){
            std::cout<<totalScore;
        }

        bool checkGameEnd(){
            int countOccupyPoint=0;
            for(int i=1;i<=4;i++){
                for(int j=1;j<=4;j++){
                    if(occupyPoint[i][j]>0)
                        countOccupyPoint++;
                }
            }
            
            if(countOccupyPoint<16)return 0;

            for(int i=1;i<=4;i++){
                for(int j=1;j<=4;j++){
                    if(occupyPoint[i][j]==occupyPoint[i-1][j]||
                       occupyPoint[i][j]==occupyPoint[i+1][j]||
                       occupyPoint[i][j]==occupyPoint[i][j-1]||
                       occupyPoint[i][j]==occupyPoint[i][j+1])
                       return 0;
                }
            }

            return 1;
        }
};