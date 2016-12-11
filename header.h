//
// Created by Grégory GUEUX on 29/11/2016.
//

#ifndef AS7_MINI_PROJET_HEADER_H
#define AS7_MINI_PROJET_HEADER_H
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>


#define ROBOT_NUMBER 1
#define HALLWAY_NUMBER 1
#define ROOM_NUMBER 2

typedef enum type {
    WARRIOR,
    ARCHER,
    WIZARD,
    THIEF
}e_type;

typedef enum pos {
    room,
    hallway
}e_pos;

struct team;
typedef struct robot {
    int priority;
    struct team* myTeam;
    e_type type;
} s_robot;


//TODO: Pour plus tard quand on gerer le ramassage des carte et combat dans les salles.
struct hallway;
typedef struct room {
    struct hallway* hallway[1];
} s_room;

typedef struct hallway {
    pthread_mutex_t mAcces;
    s_room* room[2];
} s_hallway;

typedef struct labyrinth {
    s_hallway* hallways[HALLWAY_NUMBER]; // TODO: Pour l'instant, on laisse qu'un seul couloir, penser à augmenter le nombre.
    s_room rooms[ROOM_NUMBER];
} s_labyrinth;

typedef struct team {
    s_robot* member[ROBOT_NUMBER];
    pthread_mutex_t mTeam;

    s_labyrinth* labyrinth;
} s_team;

#endif //AS7_MINI_PROJET_HEADER_H
