#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "animatronic.h"
#include "ressources.h"

Animatronic* createAnimatronic(Anim_Flag flag, Anim_Timer timer, Anim_Difficulty difficulty, Room* startRoom)
{
    Animatronic* animatronic = calloc(1, sizeof(Animatronic));

    switch(flag)
    {
        case BONNIE: strcpy(animatronic->id, "Bo");
        case CHICA: strcpy(animatronic->id, "Ch");
        case FREDDY: strcpy(animatronic->id, "Fr");
        case FOXY: strcpy(animatronic->id, "Fo");
    }
    
    animatronic->timer = timer;
    animatronic->difficulty = difficulty;

    animatronic->currRoom = startRoom;
    animatronic->startRoom = startRoom;

    printf("Created animatronic: ID = %s, room = %s, timer = %f\n", animatronic->id, animatronic->currRoom->name, animatronic->timer);

    return animatronic;
}

int checkMove(Animatronic* animatronic)
{
    return((rand()%20)<animatronic->difficulty);
}

 void move(Animatronic* animatronic)
{
    if(checkMove(animatronic))
    {
        Room** targetRoom = NULL;

        switch(animatronic->flag)
        {
            case BONNIE:
            {
                targetRoom = animatronic->currRoom->targetRoomsBonnie; 
                break;
            } 

            case CHICA:
            {
                targetRoom = animatronic->currRoom->targetRoomsChica; 
                break;
            } 
            case FREDDY:
            {
                targetRoom = animatronic->currRoom->targetRoomsFreddy; 
                break;
            } 
            case FOXY:
            {
                targetRoom = animatronic->currRoom->targetRoomsFoxy; 
                break;
            } 
        }

        if(targetRoom[1] != NULL && rand()%2) animatronic->currRoom = targetRoom[1];

        else animatronic->currRoom = targetRoom[0];

        printf("%s successfully moved: %s\n", animatronic->id, animatronic->currRoom->name);

        return;
    }

    printf("%s didn't move\n", animatronic->id);
}

void reinitialize(void* arg)
{
    ((Animatronic*) arg)->currRoom = ((Animatronic*) arg)->startRoom;

}

void destroyAnimatronic(Animatronic* animatronic)
{
    free(animatronic);
}