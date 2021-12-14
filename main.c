#include <stdio.h>
#include <stdlib.h>
#include "algos.h"

int main(int argc, char** argv){

    if(argc < 3) {
        printf("Not enough arguments.\n");
        return -1;
    }

    int choice;
   
    printf("Choice: \n");
    scanf(" %d", &choice);
    switch(choice){
        case(1):
            sortTimer(argv[1], argv[2], choice, "ins");
            break; 
        case(2):
            sortTimer(argv[1], argv[2], choice, "mrg");
            break;
        case(3):
            sortTimer(argv[1], argv[2], choice, "bub");
            break;
        case(4):
            sortTimer(argv[1], argv[2], choice, "quick");
            break;
    }
    return 0;
}