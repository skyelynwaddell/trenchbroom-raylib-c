//#include <stdio.h>
//#include "raylib.h"
#include "../headers/camera.h"

Camera camera;
int camera_mode;
int camera_move_spd;

/*
camera_init
-- creates the 3d camera object
*/
void camera_init()
{
    camera.position = (Vector3){ 0.0f, 2.0f, 4.0 };
    camera.target = (Vector3){ 0.0f, 2.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 90.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    camera_mode = CAMERA_FREE;
}