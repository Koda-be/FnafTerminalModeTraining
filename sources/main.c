#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "threadFunc.h"

int main()
{
    int* night = malloc(sizeof(char));

    system("clear");
    puts("Welcome to FnafTerminal!");

    do
    {
        printf("\nPlease choose a night (1-5): ");
        scanf("%d", night);

        if(1 <= *night && *night <= 5) break;

        puts("\nValue not in valid range");
    }while(1);
    
    pthread_t gameThr;
    if(pthread_create(&gameThr, NULL, GameThrFunc, (void*) night))
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!! ERROR DURING MAIN GAME THREAD CREATION !!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    char* result = NULL;

    pthread_join(gameThr, (void**) &result);

    printf("Arg received: %d", *result);

    exit(0);
}