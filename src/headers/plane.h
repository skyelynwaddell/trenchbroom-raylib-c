#ifndef PLANE_H
#define PLANE_H

#include "raylib.h"
#include "./utils.h"

typedef struct {
    Vector3 normal; // plane normal (a,b,c)
    float distance; // plane distance from origin
} Plane;


#endif // PLANE_H