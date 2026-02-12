#ifndef ROOM_H_
#define ROOM_H_

#include "ressources.h"

struct Room
{
    char* name;
    Room_ID id;
    struct Room** adjMainRooms;     // Array of priority adjascent rooms
    struct Room** adjSecRooms;      // Array of secondary adjascent rooms    
}; typedef struct Room Room;

void setRoomName(Room* room, char* name);
void setAdjRooms(int nbr, Target_Flag flag, Room* room, ...);
void destroyRoom(Room* room);
Room* searchRoom(Search_Flag flag, void* arg);

struct RoomArray
{
    Room** array;
    int size;
}; typedef struct RoomArray RoomArray;

void createRoomArray(RoomArray* array, int size);
void destroyRoomArray(RoomArray* array);

#endif