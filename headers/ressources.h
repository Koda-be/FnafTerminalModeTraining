#ifndef RESSOURCES_H_
#define RESSOURCES_H_

typedef int Room_ID;
typedef float Anim_Timer;

struct Room
{
    Room_ID roomID;             // ID of the room
    struct Room** adjRooms;     // Array of adjascent rooms
}; typedef struct Room Room;

#endif