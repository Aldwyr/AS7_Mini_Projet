#include "header.h"

s_robot* initRobot(s_team* team) {
    s_robot* robot = malloc(sizeof(s_robot));
    robot->priority = 0;
    robot->type = WARRIOR; //TODO:Pour l'instant, on ne s'emmerde pas avec le type du robot
    robot->myTeam = team;
    return robot;
}

s_hallway* initHallway() {
    s_hallway* hallway = malloc(sizeof(s_hallway));
    hallway->mAcces = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;

//    printf("test : %p\n", hallway);
    return hallway;
}

void initLabyrinth(s_labyrinth* labyrinth) {
    labyrinth->hallways[0] = initHallway(); //TODO: à free
    labyrinth->rooms[0].hallway[0] = labyrinth->hallways[0];
    labyrinth->rooms[1].hallway[0] = labyrinth->hallways[0];
//    printf("test : %p\n", labyrinth->hallways[0]);

}

void initTeam(s_team* team, s_labyrinth* labyrinth) {
    team->member[0] = initRobot(team);
    team->mTeam = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    team->labyrinth = labyrinth;
}

int main() {
    // On creée les thread;
    pthread_t robot1Thread;
    pthread_t robot2Thread;

    // le labyrinth puis les team;
    s_labyrinth labyrinth;
    initLabyrinth(&labyrinth);
    s_team team1;
    s_team team2;
    initTeam(&team1, &labyrinth);
    initTeam(&team2, &labyrinth);
    return 0;
}