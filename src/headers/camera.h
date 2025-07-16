#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include "raylib.h"

extern Camera camera;
extern int camera_mode;
extern int camera_move_spd;

void camera_init();

#endif