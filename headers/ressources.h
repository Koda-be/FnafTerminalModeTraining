#ifndef RESSOURCES_H_
#define RESSOURCES_H_

typedef int Room_ID;

// Animatronic types

typedef float Anim_Timer;
typedef int Anim_Difficulty;



struct Room
{
    Room_ID roomID;             // ID of the room
    struct Room** adjRooms;     // Array of adjascent rooms
}; typedef struct Room Room;

#endif