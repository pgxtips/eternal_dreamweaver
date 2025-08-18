#include "raylib.h"
#include "debug_overlay.hpp"
#include <string>

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 450;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI);
    InitWindow(screenWidth, screenHeight, "Eternal Dreamweaver");
    SetTargetFPS(60);

    DebugOverlay debug;
    debug.init();
    
    std::string sceneName = "MainMenu";

    // game loop
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        int fps = GetFPS();

        // update
        // ...

        // draw
        BeginDrawing();
            ClearBackground(RAYWHITE);
            DrawText("Eternal Dreamweaver", 190, 200, 20, BLACK);

            debug.beginFrame();
            debug.draw(dt, fps, sceneName);
            debug.endFrame();
         
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
