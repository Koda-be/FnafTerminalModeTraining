#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "threadFunc.h"

void handlerSIGUSR1(int sig)
{
     printf("SIGUSR1 gotten: %lu\n", pthread_self());
}

// void handlerSIGUSR2(int sig)
// {
//     pthread_cancel(pthread_self());
// }

int main()
{
    struct sigaction actUsr1;
    actUsr1.sa_handler = handlerSIGUSR1;
    actUsr1.sa_flags = 0;
    sigemptyset(&(actUsr1.sa_mask));

    sigaction(SIGUSR1, &actUsr1, NULL);

    // struct sigaction actUsr2;
    // actUsr2.sa_handler = handlerSIGUSR2;
    // actUsr2.sa_flags = 0;
    // sigemptyset(&(actUsr2.sa_mask));

    // sigaction(SIGUSR1, &actUsr2, NULL);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR2);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    system("clear");
    puts("Welcome to FnafTerminal!\n");

    int* night = malloc(sizeof(char));
    *night = 0;

    printf("Please choose a night (1-5): ");
    scanf("%d", night);

    while(1 > *night || *night > 5)
    {
        puts("\nValue not in valid range");
        printf("Please choose a night (1-5): ");
        scanf("%d", night);
    }

    printf("Night gotten: %p %d\n", night, *night);

    pthread_t prepThr;
    if(pthread_create(&prepThr, NULL, PrepThrFunc, (void*) night))
        puts("!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n!!! ERROR DURING MAIN GAME THREAD CREATION !!!\n!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!\n");

    pthread_t gameThr= 0;

    pthread_join(prepThr, (void**) &gameThr);

    printf("Arg received: %lu\n", gameThr);

    pthread_join(gameThr, NULL);

    exit(0);
}