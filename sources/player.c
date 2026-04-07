#include "player.h"
#include "global.h"
#include "ressources.h"

void toggleState(PlayerStates state)
{
    player.states ^= state;
}

char getState(PlayerStates state)
{
    return player.states & state;
}