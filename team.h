//
// Created by gggue on 11/12/2016.
//

#ifndef AS7_MINI_PROJET_TEAM_H
#define AS7_MINI_PROJET_TEAM_H

#include "header.h"
#include "labyrinth.h"
struct team;
struct room;

typedef struct robot {
    int nb_robot;
    int priority;
    struct team* myTeam;
    e_type type;
    struct room* salleActuelle;
} s_robot;

typedef struct team {
    int nb_team;
    s_robot* member[ROBOT_NUMBER];
    pthread_mutex_t mTeam;
    pthread_cond_t cPriorite;
    size_t nb_tour;

    s_labyrinth* labyrinth;
} s_team;




s_robot* initRobot(s_team* team, int numero);
void initTeam(s_team* team, s_labyrinth* labyrinth, int nb);
void destroyRobot(s_robot *robot1);
void destroyTeam(s_team* team);
void enterHallway(s_room* room1, s_robot* robot);
int nbTourRestant(s_team* team);
#endif //AS7_MINI_PROJET_TEAM_H
