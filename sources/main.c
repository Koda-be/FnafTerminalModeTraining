#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "threadFunc.h"
#include "global.h"

void handlerSIGUSR1(int sig)
{
    gameState = 0;
}

int main()
{
    int* night = malloc(sizeof(char));

    system("clear");
    puts("Welcome to FnafTerminal!\n");

    do
    {
        printf("Please choose a night (1-5): ");
        scanf("%d", night);

        if(1 <= *night && *night <= 5) break;

        puts("\nValue not in valid range");
    }while(1);
    
    struct sigaction action;
    action.sa_handler = handlerSIGUSR1;
    action.sa_flags = 0;
    sigemptyset(&(action.sa_mask));

    sigaction(SIGUSR1, &action, NULL);

    pthread_t gameThr;
    if(pthread_create(&gameThr, NULL, GameThrFunc, (void*) night))
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!! ERROR DURING MAIN GAME THREAD CREATION !!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    char* result = NULL;

    pthread_join(gameThr, (void**) &result);

    printf("Arg received: %d", *result);

    free(result);

    exit(0);
}