#include "stdio.h"
#include "raylib.h"
#include "raymath.h"
#include "../headers/map.h"
#include "../headers/triangle.h"
#include "../headers/brushtopolygon.h"
#include "../headers/polygon.h"

/*
draw
-- any calls to render -things- into the 3D world should be placed here
*/
void draw()
{
    polygon_draw_all();
}