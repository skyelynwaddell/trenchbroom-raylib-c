#include "../headers/map.h"
#include "../headers/brush.h"
#include "../headers/brushface.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../headers/brushtopolygon.h"
#include "../headers/texturemanager.h"

Map map; // stores the currently loaded map

/*
parse_map
filename[const char*] -- the filename of the map to be loaded ie. "myamazingmap.map"
-- Stores the data about the currently loaded map.
*/
int map_parse(const char* filename)
{
    printf("\n \n");
    printf("Loading map data...\n");
    char fullpath[256];

    // add maps/ filepath to the filename
    snprintf(fullpath, sizeof(fullpath), "maps/%s", filename);

    FILE* file = fopen(fullpath, "r");
    if (!file)
    {
        perror("Failed to open .map file!");
        printf("Tried searching in: %s", fullpath);
        return false;
    }

    printf("Successfully opened map: %s\n", fullpath);

    char line[MAX_LINE];
    int in_entity = 0;
    int in_brush = 0;
    Brush current_brush = {0};
    int current_brushface_index = 0;


    while (fgets(line, sizeof(line), file))
    {
        char* trimmed = line;

        // trim leading whitespaces
        while(*trimmed == ' ' || *trimmed == '\t') trimmed++;

        //skip comments and empty lines
        //trimmed[strcspn(trimmed, "\r\n")] = 0;
        if (trimmed[0] == '/' && trimmed[1] == '/') continue;
        if (trimmed[0] == '\n' || trimmed[0] == '\0') continue;

        if (strcmp(trimmed, "{\n") == 0)
        {
            if (in_entity && !in_brush)
            {
                in_brush = 1;
                current_brushface_index = 0; // restart brush 
                memset(&current_brush, 0, sizeof(Brush)); //clear brush struct
                //printf(" Brush start\n");
            }
            else if (!in_entity)
            {
                in_entity = 1;
                //printf("Entity start\n");
            }
            continue;
        }

        if (strcmp(trimmed, "}\n") == 0)
        {
            if (in_brush)
            {
                if (map.brush_count < MAX_BRUSHES)
                {
                    map.brushes[map.brush_count++] = current_brush;
                    printf("Created BRUSH %i \n \n", map.brush_count-1);
                }
                in_brush = 0;
                //printf(" Brush end\n");
            }
            else if (in_entity)
            {
                in_entity = 0;
                //printf("Entity end\n");
            }
            continue;
        }

        //get key value pairs
        if (in_entity && !in_brush)
        {
            char key[128], value[128];

            if (sscanf(trimmed, "\"%127[^\"]\" \"%127[^\"]\"", key, value) == 2) 
            {
                //printf("  Property: %s = %s\n", key, value);

                // Get the Map Version of the Map file
                if (string_equals(key, "mapversion"))
                {
                    map.mapversion = atoi(value);
                    printf("Map Version: %i \n", map.mapversion);
                }
            }
        }


        //parse brush face
        if (in_brush)
        {
            BrushFace brushface = {0};
            char texture_name[64];
            //printf("   Brush Face: %s", trimmed);

            int matched = sscanf(trimmed,
                "( %f %f %f ) ( %f %f %f ) ( %f %f %f ) %63s [ %f %f %f %f ] [ %f %f %f %f ] %i %i %i",
                &brushface.pos_1.x, &brushface.pos_1.y, &brushface.pos_1.z,
                &brushface.pos_2.x, &brushface.pos_2.y, &brushface.pos_2.z,
                &brushface.pos_3.x, &brushface.pos_3.y, &brushface.pos_3.z,
                texture_name,
                &brushface.uv_s.x, &brushface.uv_s.y, &brushface.uv_s.z, &brushface.uv_s.w,
                &brushface.uv_t.x, &brushface.uv_t.y, &brushface.uv_t.z, &brushface.uv_t.w,
                &brushface.uv_rotation, &brushface.u_scale, &brushface.v_scale
            );

            // success
            if (matched == 21)
            {
                // get texture name
                strncpy(brushface.texture, texture_name, sizeof(brushface.texture));
                brushface.texture[sizeof(brushface.texture) - 1] = '\0';

                //re-orientate the map so its not sideways
                //brushface.pos_1 = convert_trenchbroom_to_raylib_axis(brushface.pos_1);
                //brushface.pos_2 = convert_trenchbroom_to_raylib_axis(brushface.pos_2);
                //brushface.pos_3 = convert_trenchbroom_to_raylib_axis(brushface.pos_3);

                if (current_brushface_index < BRUSH_FACE_COUNT)
                {
                    current_brush.brush_faces[current_brushface_index++] = brushface;
                    current_brush.brush_face_count = current_brushface_index;
                    brushface_print(brushface, current_brushface_index);
                }
            } else {
                //failed
                printf("!!! Failed to parse brush face line: %s (matched %d)\n", trimmed, matched);
            }
        }
    }

    printf("Loaded %i brushes. \n", map.brush_count);

    //generate polygons
    printf("Generating map polygons from brushes.... \n");
    for (int i=0; i < map.brush_count; i++)
    {
        printf("Generating Polygon: %i \n", i);
        polygon_generate_from_brush(&map.brushes[i]);
        
        // loop over all faces in brush
        for (int j= 0; j < map.brushes[i].brush_face_count; j++)
        {
            Plane plane = brushface_to_plane(map.brushes[i].brush_faces[j]);
            polygon_sort_vertices(&map.brushes[i].polys[j], (Vector3){ plane.normal.x, plane.normal.y, plane.normal.z });
        }
    }

    fclose(file);
    map_create_models();
    return true;
}

/*
map_create_models
-- creates a model from a polygonal brush
*/
void map_create_models()
{
    float scale = 0.1f;
    float rotation_degrees = 0.0f; // change to 90.0f, 180.0f, etc. if needed
    float rotation_radians = rotation_degrees * (PI / 180.0f);

    // Precompute Y-axis rotation matrix (TrenchBroom Y is Raylib Z)
    float cos_theta = cosf(rotation_radians);
    float sin_theta = sinf(rotation_radians);

    for (int i = 0; i < map.brush_count; i++)
    {
        Brush *brush = &map.brushes[i];

        for (int j = 0; j < brush->brush_face_count; j++)
        {
            BrushFace *face = &brush->brush_faces[j];
            Polygon *poly = &brush->polys[j];

            if (poly->vertex_count < 3) continue;

            Texture2D texture = texture_get_cached(face->texture);

            // Centroid calculation (raw)
            Vector3 centroid = {0};
            for (int i = 0; i < poly->vertex_count; i++) {
                centroid = Vector3Add(centroid, poly->vertices[i]);
            }
            centroid = Vector3Scale(centroid, 1.0f / poly->vertex_count);

            int triangle_count = poly->vertex_count;
            Mesh mesh = {0};
            mesh.vertexCount = triangle_count * 3;
            mesh.triangleCount = triangle_count;

            mesh.vertices = (float *)MemAlloc(mesh.vertexCount * 3 * sizeof(float));
            mesh.texcoords = (float *)MemAlloc(mesh.vertexCount * 2 * sizeof(float));

            int index = 0;
            for (int i = 0; i < triangle_count; i++) {
                Vector3 verts[3] = {
                    poly->vertices[(i + 1) % poly->vertex_count],
                    poly->vertices[i],
                    centroid
                };

                Vector2 uvs[3] = {
                    polygon_project_to_uv(verts[0], face),
                    polygon_project_to_uv(verts[1], face),
                    polygon_project_to_uv(verts[2], face),
                };

                for (int v = 0; v < 3; v++) {
                    Vector3 p = verts[v];

                    // Coordinate conversion: (x, y, z) → (x, z, -y)
                    float x = p.x;
                    float y = p.z;    // swap Y and Z
                    float z = -p.y;   // invert old Y

                    // Apply Y-axis rotation (around new Y axis, which was TrenchBroom Z)
                    float x_rot = x * cos_theta - z * sin_theta;
                    float z_rot = x * sin_theta + z * cos_theta;

                    // Apply scale
                    x_rot *= scale;
                    y *= scale;
                    z_rot *= scale;

                    // Store vertex
                    mesh.vertices[index * 3 + 0] = x_rot;
                    mesh.vertices[index * 3 + 1] = y;
                    mesh.vertices[index * 3 + 2] = z_rot;

                    mesh.texcoords[index * 2 + 0] = uvs[v].x;
                    mesh.texcoords[index * 2 + 1] = uvs[v].y;

                    index++;
                }
            }

            UploadMesh(&mesh, false);
            Model model = LoadModelFromMesh(mesh);
            model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;

            models[model_count++] = model;
        }
    }
}

/*
map_clear_models
-- clears all the map models from memory
-- clear memory because raylib does not
-- call this when the game ends
*/
void map_clear_models()
{
    for (int i=0; i < model_count; i++)
    {
        UnloadModel(models[i]);
    }
}