#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threadFunc.h"
#include "ressources.h"
#include "room.h"
#include "animatronic.h"

void* GameThrFunc(void* argument)
{
    char nightLevel = *((char*) argument);
    char* result = malloc(sizeof(char));

    RoomArray roomArray;
    roomArray.array = calloc(11, sizeof(Room*));

    for(int i = 0; i < 11; i++)
    {
        roomArray.array[i] = createRoom(i);
        setRoomName(roomArray.array[i]);
    }

    printf("main game thread successfully launched: %d\n", nightLevel);

    pthread_t bonnieThr, chicaThr, freddyThr, foxyThr;

    pthread_create(&bonnieThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic( BONNIE, 0.5, 15, 10, &roomArray, STAGE, MAINROOM, LEFTCORR1, LEFTCORR2, LEFTCLOSET, REPAIRROOM, SECURITYROOM));
    pthread_create(&chicaThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(CHICA, 0.7, 15, 9, &roomArray, STAGE, MAINROOM, RIGHTCORR1, RIGHTCORR2, TOILETS, KITCHEN, SECURITYROOM));
    pthread_create(&freddyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FREDDY, 1, 15, 9, &roomArray, STAGE, MAINROOM, RIGHTCORR1, RIGHTCORR2, TOILETS, KITCHEN, SECURITYROOM));
    pthread_create(&foxyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FOXY, 1.2, 15, 9, &roomArray, PIRATECOVE, LEFTCORR1, LEFTCORR2));

    pthread_exit((void*) result);
}

void* AnimatronicThrFunc(void* argument)
{
    Animatronic* animatronic = (Animatronic*) argument;
    
    pthread_cleanup_push(reinitialize, (void*) animatronic);

    printf("Animatronic thread successfully launched, animatronic: %s", animatronic->id);

    pthread_cleanup_pop(1);
    
    pthread_exit(NULL);
}