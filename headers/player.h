#ifndef PLAYER_H_
#define PLAYER_H_

#include <pthread.h>
#include "ressources.h"

struct Player
{
    PlayerStates states;

    pthread_t tid;
}; typedef struct Player Player;

void createPlayer();

void toggleState(PlayerStates state);
char getState(PlayerStates state);

#endif