#include "raylib.h"

#include "scenes/register_scenes.hpp"
#include "core/scene_manager.hpp"
#include "core/debug_overlay.hpp"
#include "core/app_context.hpp"

int main(void) {
    /*const int screenWidth = 1920;*/
    /*const int screenHeight = 1080;*/

    const int screenWidth = 1280;
    const int screenHeight = 720;

    SetConfigFlags(FLAG_WINDOW_HIGHDPI | FLAG_FULLSCREEN_MODE);
    InitWindow(screenWidth, screenHeight, "Eternal Dreamweaver");
    SetTargetFPS(60);

    AppContext::Instance().Init(GetScreenWidth(), GetScreenHeight(),
                            nullptr, nullptr);
    DebugOverlay debug;
    debug.init();
    
    SceneManager sm;

    RegisterMainMenu(sm);

    sm.set(SceneID::MainMenu);

    // game loop
    while (!WindowShouldClose()) {

        AppContext::Instance().SetDelta(GetFrameTime());
        if (IsWindowResized()) {
            AppContext::Instance().Init(GetScreenWidth(), GetScreenHeight(),
                    AppContext::Instance().world(),
                    AppContext::Instance().renderer());
        }

        sm.handleInput();
        sm.update();

        BeginDrawing();

        sm.draw();
        // nothing below this point  
        if (debug.enabled) {
            debug.beginFrame();
            debug.draw(GetFrameTime(), GetFPS(), sm.currentSceneName());
            debug.endFrame();
        }
        EndDrawing();
    }

    CloseWindow();
    return 0;
}
