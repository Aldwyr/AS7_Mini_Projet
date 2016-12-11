cmake_minimum_required(VERSION 3.6)
project(AS7_Mini_Projet)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c header.h team.c team.h labyrinth.c labyrinth.h)
add_executable(AS7_Mini_Projet ${SOURCE_FILES})