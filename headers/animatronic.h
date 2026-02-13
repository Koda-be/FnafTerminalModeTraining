#ifndef ANIMATRONIC_H_
#define ANIMATRONIC_H_

#include "ressources.h"
#include "room.h"

struct Animatronic
{
    // ID fields
    Anim_ID id;
    Anim_Flag flag;
    Anim_Timer timer;                       // Timer between movement tries, specific to each animatronic
    Anim_Difficulty difficulty;             // Difficulty 

    // Position fields
    Room* currRoom;                         // Current location of the animatronic
    Room** path;                            // Array of rooms the animatronic will go through
}; typedef struct Animatronic Animatronic;

struct AnimRoomTuple
{
    Animatronic* animatronic;
    Room* room;
}; typedef struct AnimRoomTuple AnimRoomTuple;

Animatronic* createAnimatronic(Anim_Flag flag, Anim_Timer timer, Anim_Difficulty difficulty, int roomAmmount, RoomArray* roomArray, Room_ID room, ...);
int checkMove(Animatronic*);
void move(Animatronic*);
void reinitialize(void*);
void destroyAnimatronic(Animatronic*);

#endif