#ifndef RESSOURCES_H_
#define RESSOURCES_H_

// Room types
typedef char* Room_name;

    // Room ID's
typedef int Room_ID;
#define STAGE 0
#define MAINROOM 1
#define PIRATECOVE 2
#define LEFTCORR1 3
#define LEFTCORR2 4
#define RIGHTCORR1 5
#define RIGHTCORR2 6
#define LEFTCLOSET 7
#define REPAIRROOM 8
#define TOILETS 9
#define KITCHEN 10
#define SECURITYROOM 11

// Animatronic types
typedef char Anim_ID[3];
typedef float Anim_Timer;
typedef int Anim_Difficulty;

// Flags
typedef char Target_Flag;
#define MAIN 0
#define SEC 1

typedef char Anim_Flag;
#define BONNIE 0
#define CHICA 1
#define FREDDY 2
#define FOXY 3

typedef char Search_Flag;
#define ID 0
#define NAME 1

#endif