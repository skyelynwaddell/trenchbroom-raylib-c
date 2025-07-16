#ifndef BRUSH_H
#define BRUSH_H

#include "../headers/brushface.h"
#include "../headers/polygon.h"

#define BRUSH_FACE_COUNT 64 // a brush can have up to 64 faces - must be convex

typedef struct {
    int brush_face_count;
    BrushFace brush_faces[BRUSH_FACE_COUNT];
    Polygon polys[64];
} Brush;


#endif // BRUSH_H