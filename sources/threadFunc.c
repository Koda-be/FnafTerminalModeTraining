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
        roomArray.array[i] = createRoom((Room_ID) i);
        setRoomName(roomArray.array[i]);
    }

    setTargetRooms(MAIN, BONNIE, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(SEC, BONNIE, roomArray.array[MAINROOM], roomArray.array[LEFTCORR1], roomArray.array[REPAIRROOM]);
    setTargetRooms(SEC, BONNIE, roomArray.array[REPAIRROOM], roomArray.array[MAINROOM], roomArray.array[STAGE]);
    setTargetRooms(SEC, BONNIE, roomArray.array[LEFTCORR1], roomArray.array[LEFTCORR2], roomArray.array[LEFTCLOSET]);
    setTargetRooms(SEC, BONNIE, roomArray.array[LEFTCLOSET], roomArray.array[LEFTCORR1], roomArray.array[MAINROOM]);
    setTargetRooms(SEC, BONNIE, roomArray.array[LEFTCORR2], roomArray.array[SECURITYROOM], roomArray.array[LEFTCORR1]);
    setTargetRooms(MAIN, BONNIE, roomArray.array[SECURITYROOM], roomArray.array[STAGE]);

    setTargetRooms(MAIN, CHICA, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(SEC, CHICA, roomArray.array[MAINROOM], roomArray.array[RIGHTCORR1], roomArray.array[TOILETS]);
    setTargetRooms(SEC, CHICA, roomArray.array[RIGHTCORR1], roomArray.array[RIGHTCORR2], roomArray.array[KITCHEN]);
    setTargetRooms(SEC, CHICA, roomArray.array[TOILETS], roomArray.array[KITCHEN], roomArray.array[MAINROOM]);
    setTargetRooms(SEC, CHICA, roomArray.array[KITCHEN], roomArray.array[RIGHTCORR1], roomArray.array[MAINROOM]);
    setTargetRooms(SEC, CHICA, roomArray.array[RIGHTCORR2], roomArray.array[SECURITYROOM], roomArray.array[RIGHTCORR1]);
    setTargetRooms(MAIN, MAIN, roomArray.array[SECURITYROOM], roomArray.array[STAGE]);


    setTargetRooms(MAIN, FREDDY, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(MAIN, FREDDY, roomArray.array[MAINROOM], roomArray.array[TOILETS]);
    setTargetRooms(MAIN, FREDDY, roomArray.array[TOILETS], roomArray.array[KITCHEN]);    
    setTargetRooms(MAIN, FREDDY, roomArray.array[KITCHEN], roomArray.array[RIGHTCORR1]);
    setTargetRooms(MAIN, FREDDY, roomArray.array[RIGHTCORR1], roomArray.array[RIGHTCORR2]);
    setTargetRooms(MAIN, FREDDY, roomArray.array[RIGHTCORR2], roomArray.array[SECURITYROOM]);
    setTargetRooms(MAIN, FREDDY, roomArray.array[SECURITYROOM], roomArray.array[RIGHTCORR2]);

    setTargetRooms(MAIN, FOXY, roomArray.array[PIRATECOVE], roomArray.array[LEFTCORR1]);
    setTargetRooms(MAIN, FOXY, roomArray.array[LEFTCORR1], roomArray.array[SECURITYROOM]);
    setTargetRooms(MAIN, FOXY, roomArray.array[SECURITYROOM], roomArray.array[PIRATECOVE]);

    printf("main game thread successfully launched: %d\n", nightLevel);

    pthread_t bonnieThr, chicaThr, freddyThr, foxyThr;

    pthread_create(&bonnieThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic( BONNIE, 0.5, 15, roomArray.array[STAGE]));
    pthread_create(&chicaThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(CHICA, 0.7, 15, roomArray.array[STAGE]));
    pthread_create(&freddyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FREDDY, 1, 15, roomArray.array[STAGE]));
    pthread_create(&foxyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FOXY, 1.2, 15, roomArray.array[PIRATECOVE]));

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