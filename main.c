#include <unistd.h>
#include "header.h"

void *debutExploration(void *args) {
    s_robot* robot = (s_robot*) args;
    int t;
//    sleep(10);
    while (1) {
        pthread_mutex_lock(&robot->myTeam->mTeam);
        t = nbTourRestant(robot->myTeam);
        pthread_mutex_unlock(&robot->myTeam->mTeam);
        if (t == -1)
            break;
        // Le robot entre est s'il est le 1er à entrer prends la 1er case du couloir.
        enterHallway(robot->salleActuelle, robot);
        while (robot->suivant < NB_CASE) {
            avanceDansLeHallway(robot->salleActuelle, robot);
            sleep(1);
            robot->suivant++;
        }
        pthread_cond_signal(&robot->cQuiAttendQueJeBouge);
        robot->salleActuelle->hallway[0]->cases[robot->suivant - 1].QuiEstSurMoi = NULL;
        robot->suivant = 0;
        sortiHallway(robot->salleActuelle, robot);
    }
    printf("J'en ai marre, je me casse.\n");
    return NULL;
}

int main() {
    // On creée les thread;
    pthread_t robotsTeamA[ROBOT_NUMBER];
    pthread_t rebotsTeamB[ROBOT_NUMBER];

    // le labyrinth puis les team;
    s_labyrinth labyrinth;
    initLabyrinth(&labyrinth);
    s_team team1;
    s_team team2;
    initTeam(&team1, &labyrinth, 1);
    initTeam(&team2, &labyrinth, 2);

    for (int i = 0; i < ROBOT_NUMBER; ++i) {
        if (i%2 == 0) {
            pthread_create(&robotsTeamA[i], NULL, &debutExploration, team1.member[i]);
            pthread_create(&rebotsTeamB[i], NULL, &debutExploration, team2.member[i]);
        }
        else {
            pthread_create(&rebotsTeamB[i], NULL, &debutExploration, team2.member[i]);
            pthread_create(&robotsTeamA[i], NULL, &debutExploration, team1.member[i]);
        }
    }
    for (int j = 0; j < ROBOT_NUMBER; ++j) {
        pthread_join(robotsTeamA[j], NULL);
        //pthread_join(rebotsTeamB[j], NULL);
    }

    destroyTeam(&team1);
    destroyTeam(&team2);
    destroyLabyrinth(&labyrinth);
    return 0;
}