#ifndef UTILS_H
#define UTILS_H

#include "raymath.h"

/*
Vector3Double
*/
typedef struct {
    double x;
    double y;
    double z;
} Vector3Double;

Vector3Double Vector3DoubleCrossProduct(Vector3Double v1, Vector3Double v2);
Vector3Double Vector3DoubleScale(Vector3Double v, float scalar);
double Vector3DoubleDotProduct(Vector3Double v1, Vector3Double v2);
Vector3Double Vector3DoubleAdd(Vector3Double v1, Vector3Double v2);
Vector3Double Vector3DoubleSubtract(Vector3Double v1, Vector3Double v2);
Vector3Double Vector3DoubleNormalize(Vector3Double v);
Vector3 rotate_vector_around_axis(Vector3 vec, Vector3 axis, float angle);
Vector3 convert_trenchbroom_to_raylib_axis(Vector3 v);
int string_equals(char* string, char* string_to_compare_to);

#endif // UTILS_H

