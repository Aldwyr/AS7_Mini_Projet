//
// Created by gggue on 11/12/2016.
//

#include "team.h"


int nbTourRestant(s_team* team) {
    if (team->nb_tour > 0) {
        team->nb_tour--;
        return 1;
    }
    else
        return -1;
}

void enterHallway(s_room* room1, s_robot* robot) {
    pthread_mutex_lock(&room1->hallway[0]->accesGeneral);
    pthread_mutex_lock(room1->entrer[0]);
    if (room1->hallway[0]->cptteam[robot->myTeam->nb_team - 1] == 0) {
        // je bloque tout les autres acces au couloir.
        printf("Je suis le robot numero : %d de l'equipe %d et mon equipe entre dans le couloir.\n", robot->nb_robot, robot->myTeam->nb_team);
        for (int i = 0; i < 2; ++i) {
            if (room1->entrer[0] != &room1->hallway[0]->mAcces[i]) {
                pthread_mutex_lock(&room1->hallway[0]->mAcces[i]);
            }
        }
    } else
        printf("Je suis.\n Robot n %d de l'equipe %d.\n", robot->nb_robot, robot->myTeam->nb_team);
    // J'incrément le compteur d'équipe pour les autres robot.
    room1->hallway[0]->cptteam[robot->myTeam->nb_team - 1]++;
    pthread_mutex_unlock(room1->entrer[0]);
    pthread_mutex_unlock(&room1->hallway[0]->accesGeneral);
}

//void sortirHallway(s_)

s_robot* initRobot(s_team* team, int numero) {
    s_robot* robot = malloc(sizeof(s_robot));
    robot->nb_robot = numero;
    robot->priority = numero;
    robot->type = WARRIOR; //TODO:Pour l'instant, on ne s'emmerde pas avec le type du robot
    robot->myTeam = team;
    return robot;
}

void initTeam(s_team* team, s_labyrinth* labyrinth, int nb) {
    team->nb_team = nb;
    // j'initialiser le mutex;
    team->mTeam = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    team->cPriorite = (pthread_cond_t) PTHREAD_COND_INITIALIZER;
    team->labyrinth = labyrinth;

    for (int i = 0; i < ROBOT_NUMBER; ++i) {
        team->member[i] = initRobot(team, i);
        team->member[i]->salleActuelle = &team->labyrinth->rooms[nb - 1];
    }
    team->nb_tour = NB_TOUR;

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