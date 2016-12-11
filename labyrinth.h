//
// Created by gggue on 11/12/2016.
//

#ifndef AS7_MINI_PROJET_LABYRINTH_H
#define AS7_MINI_PROJET_LABYRINTH_H

#include "header.h"


//TODO: Pour plus tard quand on gerer le ramassage des carte et combat dans les salles.
struct hallway;
typedef struct room {
    struct hallway* hallway[1];
    pthread_mutex_t *entrer[1]; // On peut ainsi augmenter le nombre d'antrer que l'on veut.
} s_room;

typedef struct hallway {
    pthread_mutex_t accesGeneral;
    pthread_mutex_t mAcces[2];
    s_room* room[2];
} s_hallway;

typedef struct labyrinth {
    s_hallway* hallways[HALLWAY_NUMBER]; // TODO: Pour l'instant, on laisse qu'un seul couloir, penser à augmenter le nombre.
    s_room rooms[ROOM_NUMBER];
} s_labyrinth;


s_hallway* initHallway(s_room* room1, s_room* room2);
void initLabyrinth(s_labyrinth* labyrinth);
void destroyHallway(s_hallway* hallway1);
void destroyLabyrinth(s_labyrinth* labyrinth1);

#endif //AS7_MINI_PROJET_LABYRINTH_H
