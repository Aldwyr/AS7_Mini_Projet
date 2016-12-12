//
// Created by Grégory GUEUX on 29/11/2016.
//

#ifndef AS7_MINI_PROJET_HEADER_H
#define AS7_MINI_PROJET_HEADER_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define ROBOT_NUMBER 5
#define HALLWAY_NUMBER 1
#define ROOM_NUMBER 2
#define NB_TEAM 2
#define NB_TOUR 200
#define NB_CASE 10

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
struct room;
struct caseHallway;
typedef struct robot {
    int nb_robot;
    int priority;
    int suivant;
    struct team* myTeam;
    e_type type;
    struct room* salleActuelle;
    struct caseHallway* caseActuelle;

    pthread_cond_t cQuiAttendQueJeBouge;
} s_robot;


typedef struct caseHallway {
    s_robot* QuiEstSurMoi;
}s_caseHallway;

//TODO: Pour plus tard quand on gerer le ramassage des carte et combat dans les salles.
struct hallway;
typedef struct room {
    struct hallway* hallway[1];
    pthread_mutex_t *entrer[1]; // On peut ainsi augmenter le nombre d'antrer que l'on veut.
} s_room;

typedef struct hallway {
    pthread_mutex_t accesGeneral;
    int cpt;
    pthread_mutex_t mAcces[2];
    s_room* room[2];
    s_caseHallway cases[NB_CASE];
} s_hallway;

typedef struct labyrinth {
    s_hallway* hallways[HALLWAY_NUMBER]; // TODO: Pour l'instant, on laisse qu'un seul couloir, penser à augmenter le nombre.
    s_room rooms[ROOM_NUMBER];
} s_labyrinth;


typedef struct team {
    int nb_team;
    s_robot* member[ROBOT_NUMBER];
    pthread_mutex_t mTeam;
    pthread_cond_t cPriorite;
    size_t nb_tour;

    s_labyrinth* labyrinth;
} s_team;


s_hallway* initHallway(s_room* room1, s_room* room2);
void initLabyrinth(s_labyrinth* labyrinth);
void destroyHallway(s_hallway* hallway1);
void destroyLabyrinth(s_labyrinth* labyrinth1);


s_robot* initRobot(s_team* team, int numero);
void initTeam(s_team* team, s_labyrinth* labyrinth, int nb);
void destroyRobot(s_robot *robot1);
void destroyTeam(s_team* team);
void enterHallway(s_room* room1, s_robot* robot);
int nbTourRestant(s_team* team);
void enterHallway(s_room* room1, s_robot* robot);
void avanceDansLeHallway(s_room* room1, s_robot* robot);
void javanceDuneCase(s_room* room1, s_robot* robot);
void sortiHallway(s_room* room1, s_robot* robot);
#endif //AS7_MINI_PROJET_HEADER_H
