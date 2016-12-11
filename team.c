//
// Created by gggue on 11/12/2016.
//

#include "team.h"


s_robot* initRobot(s_team* team, int numero) {
    s_robot* robot = malloc(sizeof(s_robot));
    robot->nb_robot = numero;
    robot->priority = 0;
    robot->type = WARRIOR; //TODO:Pour l'instant, on ne s'emmerde pas avec le type du robot
    robot->myTeam = team;
    return robot;
}

void initTeam(s_team* team, s_labyrinth* labyrinth, int nb) {
    team->nb_team = nb;
    for (int i = 0; i < ROBOT_NUMBER; ++i) {
        team->member[i] = initRobot(team, i);
    }
    team->nb_tour = NB_TOUR;

    // j'initialiser le mutex;
    team->mTeam = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    team->labyrinth = labyrinth;
}

void destroyRobot(s_robot *robot1) {
    robot1->myTeam = NULL;
    free(robot1);
}

void destroyTeam(s_team* team) {
    if (pthread_mutex_destroy(&team->mTeam)) {
        printf ("erreur lors de la destruction du mutex");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < ROBOT_NUMBER; ++i) {
        destroyRobot(team->member[i]);
        team->member[i] = NULL;
    }
    team->labyrinth = NULL;
}