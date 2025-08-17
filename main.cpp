#include "raylib.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Eternal Dreamweaver");
    SetTargetFPS(60);

    // game loop
    while (!WindowShouldClose()) {
        // update
        // ...

        // draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Eternal Dreamweaver", 190, 200, 20, BLACK);
            DrawFPS(screenWidth - 80, screenHeight - 25);
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
