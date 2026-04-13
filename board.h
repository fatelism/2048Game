#include <cstring>
#include <conio.h>
#include <iostream>
#include <cstdlib>

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
            std::cout<<"╔════════════════════════════╗"<<"                score: "<<totalScore<<std::endl;

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

        int blockMove(){
            userInput:

            char keyboardInput=_getch();
            int movementScore=0;

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
                            movementScore+=occupyPoint[line][column-1];
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

                return movementScore;
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
                            movementScore+=occupyPoint[line][column+1];
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

                return movementScore;
            }

            else if(keyboardInput=='w'){

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

                for(int column=1;column<=4;column++){
                    for(int line=2;line<=4;line++){
                        if(occupyPoint[line-1][column]==occupyPoint[line][column]){
                            occupyPoint[line-1][column]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line-1][column];
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

                return movementScore;
            }

            else if(keyboardInput=='s'){

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

                for(int column=1;column<=4;column++){
                    for(int line=3;line>=1;line--){
                        if(occupyPoint[line+1][column]==occupyPoint[line][column]){
                            occupyPoint[line+1][column]*=2;
                            occupyPoint[line][column]=0;
                            movementScore+=occupyPoint[line+1][column];
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

                return movementScore;
            }
            else if(keyboardInput=='q'){
                return -1;
            }

            else goto userInput;
        }

        void addScore(int x){
            totalScore+=x;
        }
};