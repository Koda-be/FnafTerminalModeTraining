#ifndef RESSOURCES_H_
#define RESSOURCES_H_

// Game states
typedef enum
{
    notReady,
    playing,
    won,
    lost
} GameState;

// Player 
typedef char PlayerStates;
#define LEFTDOOR 0b1
#define RIGHTDOOR 0b10
#define LEFTLIGHT 0b100
#define RIGHTLIGHT 0b10000

// array specifics
#define ARRAYSIZE 12

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

// Hours
typedef int HOUR;
#define H_0 0
#define H_3 1
#define H_5 2

// Animatronic types
typedef char Anim_ID[3];
typedef float Anim_Timer;
typedef char Anim_Difficulty;
typedef char Anim_State;
typedef float Anim_StunTimer;

// Flags
typedef enum
{
    main,
    sec
} Target_Flag;

typedef enum
{
    bonnie,
    chica,
    freddy,
    foxy
} Anim_Flag;

typedef char Search_Flag;
#define ID 0
#define NAME 1

#endif