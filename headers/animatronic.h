#ifndef ANIMATRONIC_H_
#define ANIMATRONIC_H_

#include "ressources.h"

struct Animatronic
{
    // Fields
    Room* currRoom;                          // Current location of the animatronic
    Anim_Timer timer;                       // Timer between movement tries, specific to each animatronic
    Anim_Difficulty difficulty;

    int (*CheckMove)(struct Animatronic*);
    void (*Move)(struct Animatronic*);

}; typedef struct Animatronic Animatronic;



#endif