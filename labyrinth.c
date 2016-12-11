//
// Created by gggue on 11/12/2016.
//

#include "labyrinth.h"



s_hallway* initHallway(s_room* room1, s_room* room2) {
    s_hallway* hallway = malloc(sizeof(s_hallway));
    hallway->mAcces[0] = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    hallway->mAcces[1] = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;
    hallway->accesGeneral = (pthread_mutex_t) PTHREAD_MUTEX_INITIALIZER;


    for (int i = 0; i < NB_TEAM; ++i) {
        hallway->cptteam[i] = 0;
    }
    hallway->room[0] = room1;
    hallway->room[1] = room2;
    //    printf("test : %p\n", hallway);
    return hallway;
}

void initLabyrinth(s_labyrinth* labyrinth) {
    labyrinth->hallways[0] = initHallway(&labyrinth->rooms[0],&labyrinth->rooms[1]); //TODO: à free
    labyrinth->rooms[0].hallway[0] = labyrinth->hallways[0];
    labyrinth->rooms[0].entrer[0] = &labyrinth->hallways[0]->mAcces[0];
    labyrinth->rooms[1].hallway[0] = labyrinth->hallways[0];
    labyrinth->rooms[1].entrer[0] = &labyrinth->hallways[0]->mAcces[1];
//    printf("test : %p\n", labyrinth->hallways[0]);

}

void destroyHallway(s_hallway* hallway1) {
    if (pthread_mutex_destroy(&hallway1->accesGeneral)) {
        printf ("erreur lors de la destruction du mutex");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_destroy(&hallway1->mAcces[0])) {
        printf ("erreur lors de la destruction du mutex");
        exit(EXIT_FAILURE);
    }
    if (pthread_mutex_destroy(&hallway1->mAcces[1])) {
        printf ("erreur lors de la destruction du mutex");
        exit(EXIT_FAILURE);
    }

    hallway1->room[0] = NULL;
    hallway1->room[1] = NULL;
    free(hallway1);

}

void destroyLabyrinth(s_labyrinth* labyrinth1) {
    destroyHallway(labyrinth1->hallways[0]);
    labyrinth1->hallways[0] = NULL;

    labyrinth1->rooms[0].hallway[0] = NULL;
    labyrinth1->rooms[1].hallway[0] = NULL;
    labyrinth1->rooms[0].entrer[0] = NULL;
    labyrinth1->rooms[1].entrer[0] = NULL;
}
