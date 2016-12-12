//
// Created by gggue on 11/12/2016.
//

#include "header.h"


int nbTourRestant(s_team* team) {
    if (team->nb_tour > 0) {
        team->nb_tour--;
        return 1;
    }
    else
        return -1;
}

void javanceDuneCase(s_room* room1, s_robot* robot) {
    // je change de casse sur laquelle je suis.
    robot->caseActuelle = &room1->hallway[0]->cases[robot->suivant];
    // J'indique à la case suivante que je suis sur elle.
    room1->hallway[0]->cases[robot->suivant].QuiEstSurMoi = robot;
}

void avanceDansLeHallway(s_room* room1, s_robot* robot) {
    pthread_mutex_lock(room1->entrer[0]);
    if (room1->hallway[0]->cases[robot->suivant].QuiEstSurMoi == NULL){
        javanceDuneCase(room1,robot);
        // J'indique au robot derrière moi qu'il peux avancer.
        pthread_cond_signal(&robot->cQuiAttendQueJeBouge);
    } else {
        // J'attend que la personne sur la case suivante me signale que je peux avancer.
        pthread_cond_wait(&room1->hallway[0]->cases[robot->suivant].QuiEstSurMoi->cQuiAttendQueJeBouge, room1->entrer[0]);
        // Je peux avancer
        javanceDuneCase(room1,robot);
        // J'indique au robot derrière moi qu'il peux avancer.
        pthread_cond_signal(&robot->cQuiAttendQueJeBouge);
    }
    // J'indique à ma case précédente que je ne suis plus sur elle.
    if (robot->suivant != 0)
        room1->hallway[0]->cases[robot->suivant - 1].QuiEstSurMoi = NULL;

    printf("Robot numero %d de l'equipe %d, j'avance a la case numero %d.\n", robot->nb_robot, robot->myTeam->nb_team, robot->suivant);
    pthread_mutex_unlock(room1->entrer[0]);
}

void sortiHallway(s_room* room1, s_robot* robot) {
    pthread_mutex_lock(room1->entrer[0]);
    room1->hallway[0]->cpt--;
    if (room1->hallway[0]->cpt == 0) {
        // Je suis le dernier à sortir.
        printf("Je suis le robot numero : %d de l'equipe %d et je suis le dernier a sortir du couloir.\n",
               robot->nb_robot, robot->myTeam->nb_team);
        // J'ouvre toute les autres portes.
        for (int i = 0; i < 2; ++i) {
            if (room1->entrer[0] != &room1->hallway[0]->mAcces[i]) {
                pthread_mutex_unlock(&room1->hallway[0]->mAcces[i]);
            }
        }
    }
    //Le robot à changé de salle.
    pthread_mutex_unlock(room1->entrer[0]);
    for (int j = 0; j < 2; ++j) {
        if (room1 != room1->hallway[0]->room[j]) {
            robot->salleActuelle = room1->hallway[0]->room[j];
            break;
        }
    }
    printf(" Robot n %d de l'equipe %d. Je suis maintenant dans la salle suivante.\n", robot->nb_robot, robot->myTeam->nb_team);
}

void enterHallway(s_room* room1, s_robot* robot) {
    pthread_mutex_lock(&room1->hallway[0]->accesGeneral);
    pthread_mutex_lock(room1->entrer[0]);
    room1->hallway[0]->cpt++;
    if (room1->hallway[0]->cpt == 1) {
        // je bloque tout les autres acces au couloir.
        printf("Je suis le robot numero : %d de l'equipe %d et je suis le 1er dans le couloir.\n", robot->nb_robot, robot->myTeam->nb_team);
        for (int i = 0; i < 2; ++i) {
            if (room1->entrer[0] != &room1->hallway[0]->mAcces[i]) {
                pthread_mutex_lock(&room1->hallway[0]->mAcces[i]);
            }
        }
    } else
        printf("Je suis.Robot n %d de l'equipe %d, j'entrer.\n", robot->nb_robot, robot->myTeam->nb_team);
    // J'incrément le compteur d'équipe pour les autres robot de ma team.
    pthread_mutex_unlock(room1->entrer[0]);
    pthread_mutex_unlock(&room1->hallway[0]->accesGeneral);
}


s_robot* initRobot(s_team* team, int numero) {
    s_robot* robot = malloc(sizeof(s_robot));

    robot->cQuiAttendQueJeBouge = (pthread_cond_t) PTHREAD_COND_INITIALIZER;

    robot->suivant = 0;
    robot->nb_robot = numero;
    robot->priority = numero;
    robot->type = WARRIOR; //TODO:Pour l'instant, on ne s'emmerde pas avec le type du robot
    robot->myTeam = team;
    robot->caseActuelle = NULL;
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
    robot1->caseActuelle = NULL;
    pthread_cond_destroy(&robot1->cQuiAttendQueJeBouge);
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