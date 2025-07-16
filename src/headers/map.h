#ifndef MAP_H
#define MAP_H

#include <stdio.h>
#include "./brushface.h"
#include "./brush.h"

#define MAX_LINE 1024
#define MAX_BRUSHES 1024

// struct to hold the data stored in .map file
typedef struct {
    int mapversion;

    int brush_count;
    Brush brushes[MAX_BRUSHES]; //contains all the brush faces in a map
} Map; 

extern Map map;

int map_parse(const char* filename);
void map_create_models();
void map_clear_models();

#endif // MAP_H
