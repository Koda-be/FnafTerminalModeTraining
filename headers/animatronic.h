#ifndef ANIMATRONIC_H_
#define ANIMATRONIC_H_

#include <pthread.h>
#include "ressources.h"
#include "room.h"

struct Animatronic
{
    // ID fields
    Anim_ID id;
    Anim_Flag flag;
    Anim_Timer  timer,
                stunTimer;                       // Timer between movement tries, specific to each animatronic
    Anim_Difficulty difficulty;             // Difficulty 
    Anim_State state;

    // Position fields
    Room* currRoom;                         // Current location of the animatronic
    Room* startRoom;

    // Thread fields
    pthread_t tid;

    void (*move)(void);
}; typedef struct Animatronic Animatronic;

// struct AnimRoomTuple
// {
//     Animatronic* animatronic;
//     Room* room;
// }; typedef struct AnimRoomTuple AnimRoomTuple;

Animatronic* createAnimatronic(Anim_Flag flag, Anim_Timer timer, Anim_Difficulty difficulty, Room* startRoom);
int checkMove(Animatronic*);
void _moveNormal(void);
void _moveStunable(void);
void reinitialize(void*);
void destroyAnimatronic(void*);

#endif