#pragma once
#include "rlImGui.h"
#include "imgui.h"
#include <string>


struct DebugOverlay {
    bool enabled = true;

    void init() {
        // true = load default ImGui style
        rlImGuiSetup(true); 
    }

    void shutdown() {
        rlImGuiShutdown();
    }

    void beginFrame() {
        if (!enabled) return;
        rlImGuiBegin();
    }

    void endFrame() {
        if (!enabled) return;
        rlImGuiEnd();
    }

    void draw(float dt, int fps, const std::string& sceneName) {
        if (!enabled) return;

        ImGui::Begin("Debug Overlay");
        ImGui::Text("FPS: %d", fps);
        ImGui::Text("dt: %.3f", dt);
        ImGui::Text("Scene: %s", sceneName.c_str());
        ImGui::Separator();

        // Example tweakable values
        static float waveAmplitude = 1.0f;
        static bool showNodes = true;
        ImGui::SliderFloat("Wave Amplitude", &waveAmplitude, 0.1f, 5.0f);
        ImGui::Checkbox("Show Nodes", &showNodes);

        ImGui::End();
    }
};
