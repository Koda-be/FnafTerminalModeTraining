#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadFunc.h"
#include "room.h"
#include "animatronic.h"
#include "global.h"

extern 

void* GameThrFunc(void* argument)
{
    char nightLevel = *((char*) argument);
    char* result = malloc(sizeof(char));


    printf("main game thread successfully launched: %d\n", nightLevel);

    createRoomArray(&roomArray, 11);

    setAdjRooms(1, MAIN, roomArray.array[0], roomArray.array[1]);
    setRoomName(roomArray.array[0], "lobby");

    setAdjRooms(1, MAIN, roomArray.array[1], roomArray.array[2]);
    setAdjRooms(1, SEC, roomArray.array[1], roomArray.array[0]);
    
    for(int i = 0; i < 5; i++)
    {
        setAdjRooms(1, MAIN, roomArray.array[i], roomArray.array[i+1]);
        setAdjRooms(2, SEC, roomArray.array[i], roomArray.array[i-1], roomArray.array[i-2]);
    }

    setAdjRooms(2, MAIN, roomArray.array[5], roomArray.array[6], roomArray.array[9]);
    setAdjRooms(2, SEC, roomArray.array[5], roomArray.array[4], roomArray.array[3]);

    for(int i = 6; i < 8; i++)
    {
        setAdjRooms(1, MAIN, roomArray.array[i], roomArray.array[i+1]);
        setAdjRooms(2, SEC, roomArray.array[i], roomArray.array[i-1], roomArray.array[i-2]);
    }

    setAdjRooms(1, MAIN, roomArray.array[8], roomArray.array[11]);
    setAdjRooms(2, SEC, roomArray.array[8], roomArray.array[7], roomArray.array[6]);

    setAdjRooms(1, MAIN, roomArray.array[9], roomArray.array[10]);
    setAdjRooms(2, SEC, roomArray.array[9], roomArray.array[5], roomArray.array[4]);

    setAdjRooms(1, MAIN, roomArray.array[10], roomArray.array[11]);
    setAdjRooms(2, SEC, roomArray.array[10], roomArray.array[9], roomArray.array[5]);

    setAdjRooms(1, MAIN, roomArray.array[roomArray.size-1], roomArray.array[0]);
    setAdjRooms(0, SEC, roomArray.array[roomArray.size-1]);

    pthread_t bonnieThr, chicaThr;

    pthread_create(&bonnieThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic( 'B', 0.5, 10, 0, 1, 2, 3, 4, 5, 6, 7, 8, 11));
    pthread_create(&chicaThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic('C', 0.7, 9, 0, 1, 2, 3, 4, 5, 9, 10, 11));

    pthread_exit((void*) result);
}

void* AnimatronicThrFunc(void* argument)
{
    Animatronic* animatronic = (Animatronic*) argument;
    AnimRoomTuple* reinitTuple = malloc(sizeof(AnimRoomTuple));
    reinitTuple->animatronic = animatronic;
    reinitTuple->room = roomArray.array[0];

    pthread_cleanup_push(free, (void*) reinitTuple);
    pthread_cleanup_push(reinitialize, (void*) reinitTuple);

    printf("Animatronic thread successfully launched, animatronic: %c", animatronic->id);

    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
    
    pthread_exit(NULL);
}