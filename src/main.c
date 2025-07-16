#include <stdio.h>
#include "raylib.h"

#include "./headers/defs.h"
#include "./headers/global.h"
#include "./headers/camera.h"
#include "./headers/map.h"
#include "./headers/cleanup.h"

#include "./headers/init.h"
#include "./headers/draw.h"
#include "./headers/draw_gui.h"


// Program Entry Point
// -----------------------------
int main()
{
    camera_init();

    // Generates some random columns
    //float heights[MAX_COLUMNS] = { 0 };
    //Vector3 positions[MAX_COLUMNS] = { 0 };
    //Color colors[MAX_COLUMNS] = { 0 };

    // for (int i = 0; i < MAX_COLUMNS; i++)
    // {
    //     heights[i] = (float)GetRandomValue(1, 12);
    //     positions[i] = (Vector3){ (float)GetRandomValue(-15, 15), heights[i]/2.0f, (float)GetRandomValue(-15, 15) };
    //     colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    // }


    // Initialization
    // -----------------------------
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, GAME_TITLE);
    DisableCursor(); // Limit cursor to relative movement inside the window
    SetTargetFPS(FPS);

    init();

    // Main Game Loop
    while(!WindowShouldClose())
    {
        // Update
        // TODO : Update your variables here
        // -----------------------------
        
        // Vector3 move = {0};
        // if (IsKeyDown(KEY_W)) move.z -= 1.0f;
        // if (IsKeyDown(KEY_S)) move.z += 1.0f;
        // if (IsKeyDown(KEY_A)) move.x -= 1.0f;
        // if (IsKeyDown(KEY_D)) move.x += 1.0f;
        // move = Vector3Scale(move,camera_move_spd);
        // Vector3 rotation = { 0 };
        // rotation.y = GetMouseDelta().x * 0.003f;  // Yaw
        // rotation.x = GetMouseDelta().y * 0.003f;  // Pitch
        UpdateCamera(&camera, camera_mode);

        // Draw
        // -----------------------------
        BeginDrawing();
            ClearBackground(RAYWHITE);
            BeginMode3D(camera);
            draw();
                //DrawPlane((Vector3){ 0.0f, 0.0f, 0.0f }, (Vector2){ 32.0f, 32.0f }, LIGHTGRAY); // Draw ground
                //DrawCube((Vector3){ -16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, BLUE);     // Draw a blue wall
                //DrawCube((Vector3){ 16.0f, 2.5f, 0.0f }, 1.0f, 5.0f, 32.0f, LIME);      // Draw a green wall
                //DrawCube((Vector3){ 0.0f, 2.5f, 16.0f }, 32.0f, 5.0f, 1.0f, GOLD);      // Draw a yellow wall

                // Draw some cubes around
                // for (int i = 0; i < MAX_COLUMNS; i++)
                // {
                //     DrawCube(positions[i], 2.0f, heights[i], 2.0f, colors[i]);
                //     DrawCubeWires(positions[i], 2.0f, heights[i], 2.0f, MAROON);
                // }
                // Draw player cube
                // if (camera_mode == CAMERA_THIRD_PERSON)
                // {
                //     DrawCube(camera.target, 0.5f, 0.5f, 0.5f, PURPLE);
                //     DrawCubeWires(camera.target, 0.5f, 0.5f, 0.5f, DARKPURPLE);
                // }

            EndMode3D();
            draw_gui();

        EndDrawing();
        // -----------------------------
    }

    // De-Initialization
    // -----------------------------
    clean_up();
    CloseWindow();
    return 0;
    // -----------------------------
}