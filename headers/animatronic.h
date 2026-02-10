#ifndef ANIMATRONIC_H_
#define ANIMATRONIC_H_

#include "ressources.h"

struct Animatronic
{
    Room currRoom;                          // Current location of the animatronic
    Anim_Timer timer;                       // Timer between movement tries, specific to each animatronic
}; typedef struct Animatronic Animatronic;

#endif