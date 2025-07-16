#ifndef BRUSHFACE_H
#define BRUSHFACE_H

#include <stdio.h>
#include "raylib.h"
#include "raymath.h"
#include "string.h"
#include "plane.h"

typedef struct {
    Vector3 pos_1; // [x y z]
    Vector3 pos_2; // [x y z]
    Vector3 pos_3; // [x y z]
    char texture[64];  // texture string name
    
    Vector4 uv_s; // [x y z offset]
    Vector4 uv_t; // [x y z offset]

    int uv_rotation; // degrees
    int u_scale; // horizontal texture scale
    int v_scale; // vertical texture scale

} BrushFace;

void brushface_print(BrushFace b, int face_index);
Plane brushface_to_plane(BrushFace face);

#endif // BRUSHFACE_H