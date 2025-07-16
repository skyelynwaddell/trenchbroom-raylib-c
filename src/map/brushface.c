#include "../headers/brushface.h"

/*
--------------------------
brushface_print
- prints a brush face's data to the console
*/
void brushface_print(BrushFace b, int face_index)
{
    printf("Brush Face %i:\n", face_index);
    printf("  Pos1: (%f, %f, %f)\n", b.pos_1.x, b.pos_1.y, b.pos_1.z);
    printf("  Pos2: (%f, %f, %f)\n", b.pos_2.x, b.pos_2.y, b.pos_2.z);
    printf("  Pos3: (%f, %f, %f)\n", b.pos_3.x, b.pos_3.y, b.pos_3.z);
    printf("  Texture: %s\n", b.texture);
    printf("  UV S: (%f, %f, %f, %f)\n", b.uv_s.x, b.uv_s.y, b.uv_s.z, b.uv_s.w);
    printf("  UV T: (%f, %f, %f, %f)\n", b.uv_t.x, b.uv_t.y, b.uv_t.z, b.uv_t.w);
    printf("  UV Rotation: %d\n", b.uv_rotation);
    printf("  U Scale: %d\n", b.u_scale);
    printf("  V Scale: %d\n", b.v_scale);
}

/*
--------------------------
brush_face_to_plane
face [BrushFace] - the passed in BrushFace to be calculated to a plane
- turns a BrushFace type into a plane
*/
Plane brushface_to_plane(BrushFace face)
{
    Vector3 edge1 = Vector3Subtract(face.pos_2, face.pos_1);
    Vector3 edge2 = Vector3Subtract(face.pos_3, face.pos_1);
    Vector3 normal = Vector3Normalize(Vector3CrossProduct(edge1,edge2));
    double distance = -Vector3DotProduct(normal, face.pos_1);
    return (Plane) { normal, distance };
}