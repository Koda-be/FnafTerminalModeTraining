#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "threadFunc.h"
#include "ressources.h"
#include "room.h"
#include "animatronic.h"

pthread_mutex_t mutexMove = PTHREAD_MUTEX_INITIALIZER;

void* GameThrFunc(void* argument)
{
    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    char nightLevel = *((char*) argument);
    char* result = malloc(sizeof(char));

    RoomArray roomArray;
    roomArray.array = calloc(12, sizeof(Room*));

    printf("roomArray created\n");

    for(int i = 0; i < 12; i++)
    {
        roomArray.array[i] = createRoom((Room_ID) i);
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
    setTargetRooms(MAIN, CHICA, roomArray.array[SECURITYROOM], roomArray.array[STAGE]);

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

    pthread_create(&bonnieThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic( BONNIE, 3.3, 15, roomArray.array[STAGE]));
    pthread_create(&chicaThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(CHICA, 3.6, 15, roomArray.array[STAGE]));
    pthread_create(&freddyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FREDDY, 5, 15, roomArray.array[STAGE]));
    pthread_create(&foxyThr, NULL, AnimatronicThrFunc, (void*) createAnimatronic(FOXY, 6, 15, roomArray.array[PIRATECOVE]));

    Room *bonRes = NULL, *chiRes = NULL, *freRes = NULL, *foxRes = NULL;

    pthread_join(bonnieThr, (void*) &bonRes);
    pthread_join(chicaThr, (void*) &chiRes);
    pthread_join(freddyThr, (void*) &freRes);
    pthread_join(foxyThr, (void*) &foxRes);

    printf("Final rooms:\nbo: %s\nch: %s\nfr: %s\nfo: %s\n", bonRes->name, chiRes->name, freRes->name, foxRes->name);

    pthread_exit((void*) result);
}

void* AnimatronicThrFunc(void* argument)
{
    Animatronic* animatronic = (Animatronic*) argument;
    
    //pthread_cleanup_push(reinitialize, (void*) animatronic);

    printf("Animatronic thread successfully launched, animatronic: %s, %d\n", animatronic->id, animatronic->flag);

    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    struct timespec timer;
    timer.tv_sec = (int) animatronic->timer;
    timer.tv_nsec = (animatronic->timer - (int) animatronic->timer)*1000000000;

    while(1)
    {
        nanosleep(&timer, NULL);

        pthread_mutex_lock(&mutexMove);
        printf("%s entered move function\n", animatronic->id);
        move(animatronic);
        printf("%s exited move function\n", animatronic->id);
        pthread_mutex_unlock(&mutexMove);
    }

    //pthread_cleanup_pop(1);
    
    pthread_exit(animatronic->currRoom);
}