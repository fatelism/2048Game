#include <cstring>
#include <conio.h>
#include <iostream>
#include <cstdlib>
#include <fstream>
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

            if(occupyPoint[n][m]>0){
                std::cout<<"┌─────┐";
            }
            else if(occupyPoint[n][m]==0){
                std::cout<<"       ";
            }
            else if(occupyPoint[n][m]==-1){
                std::cout<<"*******";
            }

            std::cout<<RESETCOLOR;
        }

        void printBlockDown(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
            if(occupyPoint[n][m]>0){
                std::cout<<"└─────┘";
            }
            else if(occupyPoint[n][m]==0){
                std::cout<<"       ";
            }
            else if(occupyPoint[n][m]==-1){
                std::cout<<"*******";
            }
            
            std::cout<<RESETCOLOR;
        }

        void printBlockMid(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
            if(occupyPoint[n][m]>0){
                std::cout<<"│     │";
            }
            else if(occupyPoint[n][m]==0){
                std::cout<<"       ";
            }
            else if(occupyPoint[n][m]==-1){
                std::cout<<"*******";
            }
            
            std::cout<<RESETCOLOR;
        }

        void printBlockNumber(int n,int m){
            std::string blockColor=colorPanel[log2(occupyPoint[n][m])];
            std::cout<<blockColor;
            
            if(occupyPoint[n][m]>0){
                std::cout<<"│";
                for(int i=1;i<=(5-countDigit(occupyPoint[n][m]))/2;i++)std::cout<<" ";
                std::cout<<occupyPoint[n][m];
                for(int i=(5-countDigit(occupyPoint[n][m]))/2+countDigit(occupyPoint[n][m])+1;i<=5;i++)std::cout<<" ";
                std::cout<<"│";
            }
            else if(occupyPoint[n][m]==0){
                std::cout<<"       ";
            }
            else if(occupyPoint[n][m]==-1){
                std::cout<<"*******";
            }
            
            std::cout<<RESETCOLOR;
        }

        void printBlock(int line){
            std::cout<<"              ";
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockUp(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;

            std::cout<<"              ";
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
            
            std::cout<<"              ";
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockNumber(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
            
                                         std::cout<<"              ";
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockMid(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
                 
            std::cout<<"              ";
            std::cout<<BOLD<<"║"<<RESETCOLOR;
                        for(int column=1;column<=4;column++){
                            printBlockDown(line,column);
                        }
                                         std::cout<<BOLD<<"║"<<RESETCOLOR<<std::endl;
        }

        void printBoard(int gamemode){
            // std::cout << "\033[H\033[2J";
            std::cout << "\x1b[2J\x1b[H";
            std::cout.flush();
            std::cout<<BOLD<<"              ╔════════════════════════════╗";
            std::cout<<RESETCOLOR<<"          score: "<<totalScore;
            if(gamemode==1)std::cout<<"      maximum score: "<<getMaximumClassicScore()<<std::endl;
            else if(gamemode==2)std::cout<<"      maximum score: "<<getMaximumSpecialScore()<<std::endl;

            for(int line=1;line<=4;line++){
                printBlock(line);
            }

            std::cout<<BOLD<<"              ╚════════════════════════════╝"<<RESETCOLOR<<std::endl;
        }
        
        void blockSpawn(){

            int line=rand()%4+1,column=rand()%4+1;
            while(occupyPoint[line][column]!=0){
                line=rand()%4+1,column=rand()%4+1;
            }

            occupyPoint[line][column]=2;
        }

        void barrierSpawn(){

            int countEmpty=0;
            for(int line=1;line<=4;line++){
                for(int column=1;column<=4;column++){
                    if(occupyPoint[line][column]==0)
                        countEmpty++;
                }
            }

            if(countEmpty<=3)return;

            int line=rand()%4+1,column=rand()%4+1;
            while(occupyPoint[line][column]){
                line=rand()%4+1,column=rand()%4+1;
            }

            occupyPoint[line][column]=-1;
        }

        void barrierEliminate(){
            for(int line=1;line<=4;line++){
                for(int column=1;column<=4;column++){
                    if(occupyPoint[line][column]==-1)
                        occupyPoint[line][column]=0;
                }
            }
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
                            if(occupyPoint[line][aimcolumn]==0&&occupyPoint[line][column]>0&&withoutLineBarrier(line,aimcolumn,column)){
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
                            if(occupyPoint[line][aimcolumn]==0&&occupyPoint[line][column]>0&&withoutLineBarrier(line,aimcolumn,column)){
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
                            if(occupyPoint[line][aimcolumn]==0&&occupyPoint[line][column]>0&&withoutLineBarrier(line,column,aimcolumn)){
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
                            if(occupyPoint[line][aimcolumn]==0&&occupyPoint[line][column]>0&&withoutLineBarrier(line,column,aimcolumn)){
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
                            if(occupyPoint[aimline][column]==0&&occupyPoint[line][column]>0&&withoutColumnBarrier(column,aimline,line)){
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
                            if(occupyPoint[aimline][column]==0&&occupyPoint[line][column]>0&&withoutColumnBarrier(column,aimline,line)){
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
                            if(occupyPoint[aimline][column]==0&&occupyPoint[line][column]>0&&withoutColumnBarrier(column,line,aimline)){
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
                            if(occupyPoint[aimline][column]==0&&occupyPoint[line][column]>0&&withoutColumnBarrier(column,line,aimline)){
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

            else if(keyboardInput=='r'){
                return -2;
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
                    if(occupyPoint[i][j]!=0)
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

        void gameRestart(){
            totalScore=0;
            for(int i=0;i<6;i++)
                for(int j=0;j<6;j++)
                    occupyPoint[i][j]=0;
        }

        int gameEnd(){
            std::cout<<"Game is end.\nYour final score: ";
            printScore();
            std::cout<<std::endl;
            std::cout<<"Press 'r' to restart."<<std::endl;
            char input=_getch();
            while(1){
                if(input=='r')return 0;
                else if(input=='q')return 1; 
                input=_getch();   
            }
        }

        int getMaximumClassicScore(){
            int maximumScore=0;
            std::ifstream fin("maximumClassicScore.txt");
            if(fin.is_open()){
                fin>>maximumScore;
            }
            return maximumScore;
        }

        void updateMaximumClassicScore(){
            int maximumScore=0;
            std::ifstream fin("maximumClassicScore.txt");
            if(fin.is_open()){
                fin>>maximumScore;
            }

            if(maximumScore<totalScore){
                std::ofstream fout("maximumClassicScore.txt",std::ios::trunc);
                if(fout.is_open()){
                    fout<<totalScore;
                }
                return;
            }
            return;
        }

        int getMaximumSpecialScore(){
            int maximumScore=0;
            std::ifstream fin("maximumSpecialScore.txt");
            if(fin.is_open()){
                fin>>maximumScore;
            }
            return maximumScore;
        }

        void updateMaximumSpecialScore(){
            int maximumScore=0;
            std::ifstream fin("maximumSpecialScore.txt");
            if(fin.is_open()){
                fin>>maximumScore;
            }

            if(maximumScore<totalScore){
                std::ofstream fout("maximumSpecialScore.txt",std::ios::trunc);
                if(fout.is_open()){
                    fout<<totalScore;
                }
                return;
            }
            return;
        }
        
        bool withoutColumnBarrier(int column,int line1,int line2){
            for(int line=line1+1;line<line2;line++){
                if(occupyPoint[line][column]==-1)
                    return 0;
            }
            return 1;
        }

        bool withoutLineBarrier(int line,int column1,int column2){
            for(int column=column1+1;column<column2;column++){
                if(occupyPoint[line][column]==-1)
                    return 0;
            }
            return 1;
        }
};