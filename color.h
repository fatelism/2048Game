#pragma once

#include <iostream>

#define RESETCOLOR "\033[0m"
#define BOLD "\033[1m"

std::string colorPanel[100]={"\033[0m","\033[38;5;15m","\033[38;5;215m","\033[38;5;208m","\033[38;5;229m",
                    "\033[38;5;226m","\033[38;5;214m","\033[38;5;120m","\033[38;5;40m","\033[38;5;28m",
                    "\033[38;5;183m","\033[38;5;129m","\033[38;5;93m"};
                
int log2(int pointNumber){
    int count=0;
    while(pointNumber>0){
        count++;
        pointNumber/=2;
    }
    if(count>=12)count=12;
    return count;
}