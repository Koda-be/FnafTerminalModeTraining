#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadFunc.h"

void* GameThrFunc(void* argument)
{
    char* arg = (char*) argument;
    char* result = malloc(sizeof(char));

    printf("main game thread successfully launched: %d\n", *arg);

    *result = *arg;

    pthread_exit((void*) result);
}