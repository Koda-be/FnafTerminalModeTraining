#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "animatronic.h"
#include "ressources.h"

Animatronic* createAnimatronic(Anim_Flag flag, Anim_Timer timer, Anim_Difficulty difficulty, int roomAmmount, RoomArray* roomArray, Room_ID startRoom, ...)
{
    Animatronic* animatronic = malloc(sizeof(Animatronic));

    switch(flag)
    {
        case BONNIE: strcpy(animatronic->id, "Bo");
        case CHICA: strcpy(animatronic->id, "Ch");
        case FREDDY: strcpy(animatronic->id, "Fr");
        case FOXY: strcpy(animatronic->id, "Fo");
    }
    
    animatronic->timer = timer;
    animatronic->difficulty = difficulty;

    Room_ID* roomPtr = malloc(sizeof(Room_ID));
    *roomPtr = STAGE;
    animatronic->currRoom = searchRoom(roomArray, ID, (void*) roomPtr);
    free(roomPtr);

    animatronic->path = malloc((roomAmmount+1)*sizeof(Room*));

    va_list roomList;
    va_start(roomList, startRoom);

    animatronic->path[0] = searchRoom(roomArray, ID, &(startRoom));

    for(int i = 1; i <= roomAmmount; i++)
    {
        Room_ID id = va_arg(roomList, Room_ID);
        animatronic->path[i] = searchRoom(roomArray, ID, (void*) &id);
    }
    
    animatronic->path[roomAmmount+1] = NULL;
    
    va_end(roomList);

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
    ((Animatronic*) arg)->currRoom = ((Animatronic*) arg)->path[0];

}

void destroyAnimatronic(Animatronic* animatronic)
{
    free(animatronic->path);
    free(animatronic);
}