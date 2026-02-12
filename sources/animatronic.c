#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "animatronic.h"
#include "ressources.h"

Animatronic* createAnimatronic(Anim_ID id, Anim_Timer timer, Anim_Difficulty difficulty, int roomAmmount, Room_ID startRoom, ...)
{
    Animatronic* animatronic = malloc(sizeof(Animatronic));

    animatronic->id = id;
    animatronic->timer = timer;
    animatronic->difficulty = difficulty;
    animatronic->currRoom = searchRoom(NAME, (void*) "lobby");

    animatronic->allowedRooms = malloc((roomAmmount+1)*sizeof(Room*));

    va_list roomList;
    va_start(roomList, startRoom);

    animatronic->allowedRooms[0] = searchRoom(ID, &(startRoom));

    for(int i = 1; i <= roomAmmount; i++)
    {
        Room_ID id = va_arg(roomList, Room_ID);
        animatronic->allowedRooms[i] = searchRoom(ID, (void*) &id);
    }
    
    animatronic->allowedRooms[roomAmmount+1] = NULL;
    
    va_end(roomList);

    printf("Created animatronic: ID = %c, room = %s, timer = %f\n", animatronic->id, animatronic->currRoom->name, animatronic->timer);

    return animatronic;
}

int checkMove(Animatronic* animatronic)
{
    return((rand()%20)<animatronic->difficulty);
}

 void move(Animatronic* animatronic)
{
    Room** adjRooms = (rand()%2 ? animatronic->currRoom->adjMainRooms : animatronic->currRoom->adjSecRooms);
    int arraySize = 0;
    int arrayPos = 0;

    for(; adjRooms[arraySize] != NULL; arraySize++);
    
    Room** availableRooms = malloc((1+arraySize)*sizeof(Room*));

    for(int i = 0; animatronic->allowedRooms[i] != NULL; i++)
    {
        for(int j = 0; adjRooms[j] != NULL; j++)
            if(adjRooms[j] == animatronic->allowedRooms[i])
            {
                availableRooms[arrayPos++] = adjRooms[j];
            }
    }

    animatronic->currRoom = availableRooms[rand()%arrayPos];

    printf("%c moved to %s\n", animatronic->id, animatronic->currRoom->name);

    free(availableRooms);
}

void reinitialize(void* arg)
{
    ((AnimRoomTuple*) arg)->animatronic->currRoom = ((AnimRoomTuple*) arg)->room;
}

void destroyAnimatronic(Animatronic* animatronic)
{
    free(animatronic->allowedRooms);


}