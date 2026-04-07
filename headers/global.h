#ifndef GLOBAL_H_
#define GLOBAL_H_

#include "ressources.h"
#include "room.h"
#include "pthread.h"
#include "player.h"
// Global variables definitions

GameState gameState = notReady;
char threadCount = 0;

RoomArray roomArray;
Player player;

pthread_mutex_t mutexIO = PTHREAD_MUTEX_INITIALIZER,
                mutexMove = PTHREAD_MUTEX_INITIALIZER, 
                mutBon = PTHREAD_MUTEX_INITIALIZER, 
                mutChi = PTHREAD_MUTEX_INITIALIZER, 
                mutFre = PTHREAD_MUTEX_INITIALIZER, 
                mutFox = PTHREAD_MUTEX_INITIALIZER,
                mutPlayer = PTHREAD_MUTEX_INITIALIZER;

pthread_key_t   keyID,
                keyAnim;

#endif