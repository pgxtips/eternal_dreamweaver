#include "core/scene.hpp"
#include "core/scene_manager.hpp"
#include "core/app_context.hpp"
#include "raylib.h"

namespace {
struct MainMenuScene : IScene {
    const char* name() const override {return "MainMenu"; }

    // lifecycle
    void onEnter() override {
        SetTraceLogLevel(LOG_DEBUG);

        uiFont = LoadFontEx("assets/ArcaneWhispersPersonalUseRegular-j9J80.ttf", 128, nullptr, 0);
        GenTextureMipmaps(&uiFont.texture);
        SetTextureFilter(uiFont.texture, TEXTURE_FILTER_TRILINEAR);
    }

    void onExit() override {
        UnloadFont(uiFont);
    }

    void onPause() override {}
    void onResume() override {}

    // per-frame
    void handleInput() override {}
    void update() override {}

    static inline Vector2 TextSize(Font f, const char* txt, float size, float spacing = 1.0f) {
        return MeasureTextEx(f, txt, size, spacing);
    }
    static inline int CenterX(int w, int elemW) { return (w - elemW) / 2; }

    void draw() override {
        auto& app = AppContext::Instance();
        int W = app.screenW(), H = app.screenH();

        const float baseH = 720.0f;
        float s = H / baseH;

        const char* title = "ETERNAL DREAMWEAVER";
        float titleSize = 64 * s;
        Vector2 ts = TextSize(uiFont, title, titleSize);
        int tx = CenterX(W, (int)ts.x);
        int ty = (int)(80 * s);

        ClearBackground({10,12,24,255});

        // integer pixels
        auto ip = [](float v){ return (float)((int)std::round(v)); };

        DrawTextEx(uiFont, title, { ip(tx)+2, ip(ty)+2 }, titleSize, 1, Color{0,0,0,120});
        DrawTextEx(uiFont, title, {ip(tx), ip(ty)}, titleSize, 1, RAYWHITE);

        // menu items stacked
        const char* items[] = {"Enter Realm", "Settings", "Depart"};
        float itemSize = 42 * s;
        float y = ty + ts.y + 40 * s;
        for (int i=0; i<3; i++) {
            Vector2 ms = TextSize(uiFont, items[i], itemSize);
            int mx = CenterX(W, (int)ms.x);
            DrawTextEx(uiFont, items[i], {(float)mx, y}, itemSize, 1, LIGHTGRAY);
            y += ms.y + 18 * s;
        }
    }

    bool blocksBelow() override {return false;}

    Font uiFont{};
};
} // namespace

// public registration function
void RegisterMainMenu(SceneManager& sm) {
    sm.registerFactory(SceneID::MainMenu, [](){
        return std::make_unique<MainMenuScene>();
    });
}
