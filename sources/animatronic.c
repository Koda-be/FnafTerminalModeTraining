#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "animatronic.h"
#include "ressources.h"
#include "threadFunc.h"

extern pthread_key_t keyAnim;

Animatronic* createAnimatronic(Anim_Flag flag, Anim_Timer timer, Anim_Difficulty difficulty, Room* startRoom)
{
    Animatronic* animatronic = calloc(1, sizeof(Animatronic));

    switch(flag)
    {
        case bonnie: strcpy(animatronic->id, "Bo"); break;
        case chica: strcpy(animatronic->id, "Ch"); break;
        case freddy: strcpy(animatronic->id, "Fr"); break;
        case foxy: strcpy(animatronic->id, "Fo"); break;
    }
    
    animatronic->timer = timer;
    animatronic->difficulty = difficulty;
    animatronic->flag = flag;

    animatronic->currRoom = startRoom;
    animatronic->startRoom = startRoom;

    animatronic->move = _moveNormal;

    pthread_create(&(animatronic->tid), NULL, AnimatronicThrFunc, (void*) animatronic);

    printf("Created animatronic: ID = %s, room = %s, timer = %f\n", animatronic->id, animatronic->currRoom->name, animatronic->timer);

    return animatronic;
}

int checkMove(Animatronic* animatronic)
{
    return((rand()%20)<animatronic->difficulty);
}

 void _moveNormal(void)
{
    Animatronic* animatronic = (Animatronic*) pthread_getspecific(keyAnim);

    if(checkMove(animatronic))
    {
        Room** targetRoom = NULL;

        switch(animatronic->flag)
        {
            case bonnie:
            {
                targetRoom = animatronic->currRoom->targetRoomsBonnie; 
                break;
            } 

            case chica:
            {
                targetRoom = animatronic->currRoom->targetRoomsChica; 
                break;
            }

            default:
            {
                printf("Unavailable flag");
            }
        }

        printf("%s Next possible rooms: %s, %s\n", animatronic->id, (targetRoom[0] != NULL ? targetRoom[0]->name : "NULL"), (targetRoom[1] != NULL ? targetRoom[1]->name : "NULL"));

        if(targetRoom[1] != NULL && rand()%2) animatronic->currRoom = targetRoom[1];

        else animatronic->currRoom = targetRoom[0];

        printf("%s successfully moved: %s\n", animatronic->id, animatronic->currRoom->name);

        switch(animatronic->flag)
        {
            case bonnie:
            {
                targetRoom = animatronic->currRoom->targetRoomsBonnie; 
                break;
            } 

            case chica:
            {
                targetRoom = animatronic->currRoom->targetRoomsChica; 
                break;
            } 
            case freddy:
            {
                targetRoom = animatronic->currRoom->targetRoomsFreddy; 
                break;
            } 
            case foxy:
            {
                targetRoom = animatronic->currRoom->targetRoomsFoxy; 
                break;
            } 
        }

        printf("%s Next possible rooms: %s, %s\n", animatronic->id, (targetRoom[0] != NULL ? targetRoom[0]->name : "NULL"), (targetRoom[1] != NULL ? targetRoom[1]->name : "NULL"));
        return;
    }

    printf("%s didn't move\n", animatronic->id);
}

void reinitialize(void* arg)
{
    //((Animatronic*) arg)->currRoom = ((Animatronic*) arg)->startRoom;
}