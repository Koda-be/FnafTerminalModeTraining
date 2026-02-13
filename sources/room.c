#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "room.h"
#include "ressources.h"

Room* createRoom(Room_ID id)
{
    Room* room = calloc(1, sizeof(Room));
    room->id = id;

    setRoomName(room);

    printf("Room created: %d received, room_id = %d, room_name = %s\n", id, room->id, room->name);

    return room;
}

void setRoomName(Room* room)
{
    printf("room received: %d\n", room->id);

    switch(room->id)
    {
        case STAGE:
        {
            room->name = malloc(strlen("Stage")+1);
            strcpy(room->name, "Stage");
            break;
        }

        case MAINROOM:
        {
            room->name = malloc(strlen("Main Room")+1);
            strcpy(room->name, "Main Room");
            break;
        }

        case PIRATECOVE:
        {
            room->name = malloc(strlen("Pirate Cove")+1);
            strcpy(room->name, "Pirate Cove");
            break;
        }

        case LEFTCORR1:
        {
            room->name = malloc(strlen("Left Corridor 1")+1);
            strcpy(room->name, "Left Corridor 1");
            break;
        }

        case LEFTCORR2:
        {
            room->name = malloc(strlen("Left Corridor 2")+1);
            strcpy(room->name, "Left Corridor 2");
            break;
        }

        case RIGHTCORR1:
        {
            room->name = malloc(strlen("Right Corridor 1")+1);
            strcpy(room->name, "Right Corridor 1");
            break;
        }

        case RIGHTCORR2:
        {
            room->name = malloc(strlen("Right Corridor 2")+1);
            strcpy(room->name, "Right Corridor 2");
            break;
        }

        case LEFTCLOSET:
        {
            room->name = malloc(strlen("Left Closet")+1);
            strcpy(room->name, "Left Closet");
            break;
        }

        case REPAIRROOM:
        {
            room->name = malloc(strlen("Repair Room")+1);
            strcpy(room->name, "Repair Room");
            break;
        }

        case TOILETS:
        {
            room->name = malloc(strlen("Toilets")+1);
            strcpy(room->name, "Toilets");
            break;
        }

        case KITCHEN:
        {
            room->name = malloc(strlen("Kitchen")+1);
            strcpy(room->name, "Kitchen");
            break;
        }

        case SECURITYROOM:
        {
            room->name = malloc(strlen("Security Room")+1);
            strcpy(room->name, "Security Room");
            break;
        }

        default:
        {
            room->name = malloc(strlen("/")+1);
            strcpy(room->name, "/");
            break;
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

    va_list roomPtr;
    va_start(roomPtr, room);

    (*targetRooms)[0] = va_arg(roomPtr, Room*);

    if(sec == SEC)
        (*targetRooms)[1] = va_arg(roomPtr, Room*);

    else 
        (*targetRooms)[1] = NULL;

    va_end(roomPtr);

    return;
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