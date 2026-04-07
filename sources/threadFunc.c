#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>
#include "threadFunc.h"
#include "ressources.h"
#include "room.h"
#include "animatronic.h"
#include "global.h"

extern RoomArray roomArray;
extern pthread_mutex_t  mutexMove, 
                        mutBon, 
                        mutChi, 
                        mutFre, 
                        mutFox;

extern pthread_key_t keyAnim;

void* PrepThrFunc(void* argument)
{
    printf("Prep started\n");

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    char nightLevel = *((char*) argument);

    printf("creating key\n");

    pthread_key_create(&keyAnim, destroyAnimatronic);

    roomArray.array = calloc(ARRAYSIZE, sizeof(Room*));

    printf("roomArray created\n");

    for(int i = 0; i < ARRAYSIZE; i++)
    {
        roomArray.array[i] = createRoom((Room_ID) i);
    }

    setTargetRooms(main, bonnie, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(sec, bonnie, roomArray.array[MAINROOM], roomArray.array[LEFTCORR1], roomArray.array[REPAIRROOM]);
    setTargetRooms(sec, bonnie, roomArray.array[REPAIRROOM], roomArray.array[MAINROOM], roomArray.array[STAGE]);
    setTargetRooms(sec, bonnie, roomArray.array[LEFTCORR1], roomArray.array[LEFTCORR2], roomArray.array[LEFTCLOSET]);
    setTargetRooms(sec, bonnie, roomArray.array[LEFTCLOSET], roomArray.array[LEFTCORR1], roomArray.array[MAINROOM]);
    setTargetRooms(sec, bonnie, roomArray.array[LEFTCORR2], roomArray.array[SECURITYROOM], roomArray.array[LEFTCORR1]);
    setTargetRooms(main, bonnie, roomArray.array[SECURITYROOM], roomArray.array[STAGE]);

    setTargetRooms(main, chica, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(sec, chica, roomArray.array[MAINROOM], roomArray.array[RIGHTCORR1], roomArray.array[TOILETS]);
    setTargetRooms(sec, chica, roomArray.array[RIGHTCORR1], roomArray.array[RIGHTCORR2], roomArray.array[KITCHEN]);
    setTargetRooms(sec, chica, roomArray.array[TOILETS], roomArray.array[KITCHEN], roomArray.array[MAINROOM]);
    setTargetRooms(sec, chica, roomArray.array[KITCHEN], roomArray.array[RIGHTCORR1], roomArray.array[MAINROOM]);
    setTargetRooms(sec, chica, roomArray.array[RIGHTCORR2], roomArray.array[SECURITYROOM], roomArray.array[RIGHTCORR1]);
    setTargetRooms(main, chica, roomArray.array[SECURITYROOM], roomArray.array[STAGE]);

    setTargetRooms(main, freddy, roomArray.array[STAGE], roomArray.array[MAINROOM]);
    setTargetRooms(main, freddy, roomArray.array[MAINROOM], roomArray.array[TOILETS]);
    setTargetRooms(main, freddy, roomArray.array[TOILETS], roomArray.array[KITCHEN]);    
    setTargetRooms(main, freddy, roomArray.array[KITCHEN], roomArray.array[RIGHTCORR1]);
    setTargetRooms(main, freddy, roomArray.array[RIGHTCORR1], roomArray.array[RIGHTCORR2]);
    setTargetRooms(main, freddy, roomArray.array[RIGHTCORR2], roomArray.array[SECURITYROOM]);
    setTargetRooms(main, freddy, roomArray.array[SECURITYROOM], roomArray.array[RIGHTCORR2]);

    setTargetRooms(main, foxy, roomArray.array[PIRATECOVE], roomArray.array[LEFTCORR1]);
    setTargetRooms(main, foxy, roomArray.array[LEFTCORR1], roomArray.array[SECURITYROOM]);
    setTargetRooms(main, foxy, roomArray.array[SECURITYROOM], roomArray.array[PIRATECOVE]);

    printf("Prep finished\n");

    pthread_t gameThr;

    pthread_create(&gameThr, NULL, GameThrFunc, NULL);

    pthread_exit((void*) gameThr);
}

void* GameThrFunc(void* argument)
{
    printf("gamethread: %lu\n", pthread_self());

    sigset_t mask;
    sigemptyset(&mask);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    Animatronic     *animBonnie = createAnimatronic(bonnie, 3.3, 15, roomArray.array[STAGE]), 
                    *animChica= createAnimatronic(chica, 3.6, 15, roomArray.array[STAGE]), 
                    *animFreddy= createAnimatronic(freddy, 5, 15, roomArray.array[STAGE]),
                    *animFoxy= createAnimatronic(foxy, 6, 15, roomArray.array[PIRATECOVE]);

    Room *bonRes = NULL, *chiRes = NULL, *freRes = NULL, *foxRes = NULL;

    pthread_join(animBonnie->tid, (void*) &bonRes);
    pthread_join(animChica->tid, (void*) &chiRes);
    pthread_join(animFreddy->tid, (void*) &freRes);
    pthread_join(animFoxy->tid, (void*) &foxRes);

    printf("Final rooms:\nbo: %s\nch: %s\nfr: %s\nfo: %s\n", bonRes->name, chiRes->name, freRes->name, foxRes->name);

    pthread_key_delete(keyAnim);

    pthread_exit(NULL);
}

void* AnimatronicThrFunc(void* argument)
{
    Animatronic* animatronic = (Animatronic*) argument;

    pthread_setspecific(keyAnim, animatronic);
    
    pthread_cleanup_push(reinitialize, (void*) animatronic);

    printf("Animatronic thread successfully launched, animatronic: %s, %d\n", animatronic->id, animatronic->flag);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    pthread_sigmask(SIG_SETMASK, &mask, NULL);

    struct timespec timer;
    timer.tv_sec = (int) animatronic->timer;
    timer.tv_nsec = (animatronic->timer - (int) animatronic->timer)*1000000000;

    while(1)
    {
        nanosleep(&timer, NULL);

        pthread_mutex_lock(&mutexMove);
        printf("%s entered move function\n", animatronic->id);
        animatronic->move();
        printf("%s exited move function\n", animatronic->id);
        pthread_mutex_unlock(&mutexMove);
    }

    pthread_cleanup_pop(1);
    
    pthread_exit(animatronic->currRoom);
}

void* ClockThrFunc(void* arg)
{
    pthread_exit(NULL);
}