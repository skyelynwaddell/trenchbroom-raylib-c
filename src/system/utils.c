#include "../headers/utils.h"
#include "string.h"

/*
string_equals
string[char* string] - The first string to be compared
string[char* string_to_compare_to] - the second string that is compared to the first string
-- compares two strings to see if they match
*/
int string_equals(char* string, char* string_to_compare_to)
{
    if (strcmp(string, string_to_compare_to) == 0) return 1;
    return 0;
}

/*
convert_trenchbroom_to_raylib_axis
-- raylib and trenchbroom dont use the same xyz axis, so we have to convert this here
-- so our map isnt sideways :P
*/
Vector3 convert_trenchbroom_to_raylib_axis(Vector3 v)
{
    return (Vector3) { v.x, v.z, -v.y };
}

/*
rotate_vector_around_axis
-- takes in a vector3, a vector3 axis, and the angle degrees
-- and rotates the origin vec around the second vector3
*/
Vector3 rotate_vector_around_axis(Vector3 vec, Vector3 axis, float angle)
{
    axis = Vector3Normalize(axis);
    float cos_theta = cosf(angle);
    float sin_theta = sinf(angle);

    return Vector3Add(
        Vector3Add(
            Vector3Scale(vec, cos_theta),
            Vector3Scale(Vector3CrossProduct(axis, vec), sin_theta)
        ),
        Vector3Scale(axis, Vector3DotProduct(axis, vec) * (1 - cos_theta))
    );
}

/*
Vector3DoubleCrossProduct
// Calculate two vectors cross product
*/
Vector3Double Vector3DoubleCrossProduct(Vector3Double v1, Vector3Double v2)
{
    Vector3Double result = { v1.y*v2.z - v1.z*v2.y, v1.z*v2.x - v1.x*v2.z, v1.x*v2.y - v1.y*v2.x };
    return result;
}

/*
Vector3DoubleScale
// Multiply vector by scalar
*/
Vector3Double Vector3DoubleScale(Vector3Double v, float scalar)
{
    Vector3Double result = { v.x*scalar, v.y*scalar, v.z*scalar };
    return result;
}

// Calculate two vectors dot product
double Vector3DoubleDotProduct(Vector3Double v1, Vector3Double v2)
{
    float result = (v1.x*v2.x + v1.y*v2.y + v1.z*v2.z);
    return result;
}

// Add two vectors
Vector3Double Vector3DoubleAdd(Vector3Double v1, Vector3Double v2)
{
    Vector3Double result = { v1.x + v2.x, v1.y + v2.y, v1.z + v2.z };
    return result;
}

// Subtract two vectors
Vector3Double Vector3DoubleSubtract(Vector3Double v1, Vector3Double v2)
{
    Vector3Double result = { v1.x - v2.x, v1.y - v2.y, v1.z - v2.z };
    return result;
}

// Normalize provided vector
Vector3Double Vector3DoubleNormalize(Vector3Double v)
{
    Vector3Double result = v;

    float length = sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
    if (length != 0.0f)
    {
        float ilength = 1.0f/length;

        result.x *= ilength;
        result.y *= ilength;
        result.z *= ilength;
    }

    return result;
}