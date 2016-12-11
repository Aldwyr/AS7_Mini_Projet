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
#define NB_TOUR 50;

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


#endif //AS7_MINI_PROJET_HEADER_H
