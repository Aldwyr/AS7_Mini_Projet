#include <unistd.h>
#include "header.h"
#include "team.h"

void *debutExploration(void *args) {
    int entrerSalleNb;
    s_robot* robot = (s_robot*) args;
    printf("Je suis le %d robot de l'equipe %d,j'entre dans le Labyrinth.:D\n", robot->nb_robot, robot->myTeam->nb_team);
//    sleep(10);

    entrerSalleNb = robot->myTeam->nb_team - 1;


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
        pthread_join(rebotsTeamB[j], NULL);
    }

    destroyTeam(&team1);
    destroyTeam(&team2);
    destroyLabyrinth(&labyrinth);
    return 0;
}