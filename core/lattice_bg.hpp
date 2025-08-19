#pragma once
#include "raylib.h"
#include <vector>

class LatticeBG {
public:
    struct Config {
        int   nodeCount  = 140;
        float linkRadius = 140.0f;
        Color nodeColor  = {160,240,255,200}; // cyan-frost
        Color lineColor  = {120,220,255,110};
    };

    void init(int w, int h);
    void resize(int w, int h);
    void update(float dt);
    void draw() const;

    // small runtime tweaks
    void setColors(Color node, Color line) { nodeColor = node; lineColor = line; }
    void setLinkRadius(float r)            { linkRadius = r; }

    int width()  const { return W; }
    int height() const { return H; }

private:
    struct Node { Vector2 p, v; float phase; };

    int W = 0, H = 0;
    float linkRadius = 140.0f;
    Color nodeColor  = {160,240,255,200};
    Color lineColor  = {120,220,255,110};
    std::vector<Node> nodes;
};
