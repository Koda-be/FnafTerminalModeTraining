#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "ressources.h"

void setRoomName(Room* room)
{
    switch(room->id)
    {
        case STAGE:
        {
            room->name = malloc(strlen("Stage")+1);
            strcpy(room->name, "Stage");
        }

        case MAINROOM:
        {
            room->name = malloc(strlen("Main Room")+1);
            strcpy(room->name, "Main Room");
        }

        case PIRATECOVE:
        {
            room->name = malloc(strlen("Pirate Cove")+1);
            strcpy(room->name, "Pirate Cove");
        }

        case LEFTCORR1:
        {
            room->name = malloc(strlen("Left Corridor 1")+1);
            strcpy(room->name, "Left Corridor 1");
        }

        case LEFTCORR2:
        {
            room->name = malloc(strlen("Left Corridor 2")+1);
            strcpy(room->name, "Left Corridor 2");
        }

        case RIGHTCORR1:
        {
            room->name = malloc(strlen("Right Corridor 1")+1);
            strcpy(room->name, "Right Corridor 1");
        }

        case RIGHTCORR2:
        {
            room->name = malloc(strlen("Right Corridor 2")+1);
            strcpy(room->name, "Right Corridor 2");
        }

        case LEFTCLOSET:
        {
            room->name = malloc(strlen("Left Closet")+1);
            strcpy(room->name, "Left Closet");
        }

        case REPAIRROOM:
        {
            room->name = malloc(strlen("Repair Room")+1);
            strcpy(room->name, "Repair Room");
        }

        case TOILETS:
        {
            room->name = malloc(strlen("Toilets")+1);
            strcpy(room->name, "Toilets");
        }

        case KITCHEN:
        {
            room->name = malloc(strlen("Kitchen")+1);
            strcpy(room->name, "Kitchen");
        }

        case SECURITYROOM:
        {
            room->name = malloc(strlen("Security Room")+1);
            strcpy(room->name, "Security Room");
        }

        default:
        {
            room->name = malloc(strlen("/")+1);
            strcpy(room->name, "/");
        }
    }
}

void setTargetRooms(Target_Flag sec, Anim_Flag flag, Room* room, ...)
{
    Room*** targetRooms = NULL;

    switch(flag)
    {
        case BONNIE:
            targetRooms = &(room->targetRoomsBonnie);
            break;

        case CHICA:
            targetRooms = &(room->targetRoomsChica);
            break;
        
        case FREDDY:
            targetRooms = &(room->targetRoomsFreddy);
            break;
        
        case FOXY:
            targetRooms = &(room->targetRoomsFoxy);
            break;

        default:
            printf("Invalid flag in setTargetRooms(): %d", flag);
    }
    
    *targetRooms = malloc(2*(sizeof(Room*)));
    (*targetRooms)[0] = room;

    if(sec == SEC)
    {
        va_list roomPtr;
        va_start(roomPtr, room);

        (*targetRooms)[1] = va_arg(roomPtr, Room*);

        va_end(roomPtr);

        return;
    }
    
    (*targetRooms)[1] = NULL;
}

Room* searchRoom(RoomArray* roomArray, Search_Flag flag, void* arg)
{
    if(flag)
        for(int i = 0; i < roomArray->size; i++)
            if(!(strcmp(roomArray->array[i]->name, (char*) arg)))
                return roomArray->array[i];

    for(int i = 0; i < roomArray->size; i++)
        if(roomArray->array[i]->id == *((Room_ID*) arg))
            return roomArray->array[i];

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