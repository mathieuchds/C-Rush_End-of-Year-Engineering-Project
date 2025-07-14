#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "base_func.h"

int pipe_management(int tab_pipe[8], int score){    
      
    int i = 0;

    if(tab_pipe[2] > 0){
        tab_pipe[0] = 1+ rand()%3;
        tab_pipe[0] *= -1;
        i = 1;
        score++;
    }else if(tab_pipe[2] < 0){
        tab_pipe[0] = 1+ rand()%3;
        i = 1;
        score++;
    }

    while(i<8){
        if(i != 7){
            if(tab_pipe[i] != 0){
            tab_pipe[i+1] = tab_pipe[i];
            tab_pipe[i] = 0;
            i += 2;
            }else{
            i++;
            }
        }else{
            tab_pipe[i] = 0;
            i++;
        }
    }

    return score;
}