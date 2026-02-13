#ifndef ROOM_H_
#define ROOM_H_

#include "ressources.h"

struct Room
{
    char* name;
    Room_ID id;
    struct Room** targetRoomsBonnie;     
    struct Room** targetRoomsChica;
    struct Room** targetRoomsFreddy;
    struct Room** targetRoomsFoxy;
}; typedef struct Room Room;

Room* createRoom(Room_ID id);
void setRoomName(Room* room);
void setTargetRooms(Target_Flag sec, Target_Flag flag, Room* room, ...);
void destroyRoom(Room* room);

struct RoomArray
{
    Room** array;
    int size;
}; typedef struct RoomArray RoomArray;


Room* searchRoom(RoomArray* roomArray, Search_Flag flag, void* arg);
void destroyRoomArray(RoomArray* RoomArray);

#endif