#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "global.h"

extern char gameState;
extern RoomArray roomArray;

void setRoomName(Room* room, char* name)
{
    realloc(room->name, strlen(name)+1);
    strcpy(room->name, name);
}

void setAdjRooms(int nbr, Target_Flag flag, Room* room, ...)
{
    Room*** adjRooms = (flag ? &(room->adjMainRooms) : &(room->adjSecRooms));

    va_list roomPtr;
    va_start(roomPtr, room);
    
    *adjRooms = malloc((nbr+1)*(sizeof(Room*)));
    for(int i = 0; i < nbr; i++)
        (*adjRooms)[i] = va_arg(roomPtr, Room*);

    (*adjRooms)[nbr] = NULL;

    va_end(roomPtr);
}

Room* searchRoom(Search_Flag flag, void* arg)
{
    if(flag)
        for(int i = 0; i < roomArray.size; i++)
            if(!(strcmp(roomArray.array[i]->name, (char*) arg)))
                return roomArray.array[i];

    for(int i = 0; i < roomArray.size; i++)
        if(roomArray.array[i]->id == *((Room_ID*) arg))
            return roomArray.array[i];

    return NULL;
}

void createRoomArray(RoomArray* roomArray, int size)
{
    Room** array = roomArray->array;
    array= malloc((size+1)*sizeof(Room*));
    for(int i = 0; i < size; i++)
    {
        array[i] = malloc(sizeof(Room));
        array[i]->id = i;
    }

    array[size] = NULL;
}