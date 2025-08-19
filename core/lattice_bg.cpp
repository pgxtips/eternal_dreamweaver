#include "core/lattice_bg.hpp"
#include <random>
#include <cmath>

void LatticeBG::init(int w, int h) {
    W = w; H = h;

    Config cfg;
    linkRadius = cfg.linkRadius;
    nodeColor  = cfg.nodeColor;
    lineColor  = cfg.lineColor;

    nodes.clear();
    nodes.reserve(cfg.nodeCount);

    std::mt19937 rng(1337);
    std::uniform_real_distribution<float> rx(0.f, (float)W);
    std::uniform_real_distribution<float> ry(0.f, (float)H);
    std::uniform_real_distribution<float> rv(-20.f, 20.f);
    std::uniform_real_distribution<float> rph(0.f, 6.2831853f);

    for (int i = 0; i < cfg.nodeCount; ++i) {
        Node n;
        n.p = { rx(rng), ry(rng) };
        n.v = { rv(rng), rv(rng) };
        if (fabsf(n.v.x) < 6) n.v.x = (n.v.x < 0 ? -6.f : 6.f);
        if (fabsf(n.v.y) < 6) n.v.y = (n.v.y < 0 ? -6.f : 6.f);
        n.phase = rph(rng);
        nodes.push_back(n);
    }
}

void LatticeBG::resize(int w, int h) {
 if (w==W && h==H) return;
    float sx = (float)w / (float)W;
    float sy = (float)h / (float)H;
    for (auto& n : nodes) { n.p.x *= sx; n.p.y *= sy; }
    W = w; H = h;
}

void LatticeBG::update(float dt) {
    for (auto& n : nodes) {
        n.p.x += n.v.x * dt;
        n.p.y += n.v.y * dt;
        if (n.p.x < 0) n.p.x += W; else if (n.p.x >= W) n.p.x -= W;
        if (n.p.y < 0) n.p.y += H; else if (n.p.y >= H) n.p.y -= H;
        n.phase += dt * 0.7f;
    }
}

void LatticeBG::draw() const {
    // lines (subtle, alpha by distance)
    const float r2 = linkRadius * linkRadius;
    for (size_t i = 0; i < nodes.size(); ++i) {
        for (size_t j = i + 1; j < nodes.size(); ++j) {
            float dx = nodes[i].p.x - nodes[j].p.x;
            float dy = nodes[i].p.y - nodes[j].p.y;
            float d2 = dx*dx + dy*dy;
            if (d2 < r2) {
                float d = sqrtf(d2);
                float a = 1.0f - (d / linkRadius);
                Color c = lineColor; c.a = (unsigned char)(a * lineColor.a);
                DrawLineV(nodes[i].p, nodes[j].p, c);
            }
        }
    }

    // nodes (twinkle)
    BeginBlendMode(BLEND_ADDITIVE);
    for (const auto& n : nodes) {
        float tw = 0.65f + 0.35f * sinf(n.phase + n.p.x * 0.01f);
        float r  = 1.8f + 1.2f * tw;
        Color c = nodeColor; c.a = (unsigned char)(nodeColor.a * tw);
        DrawCircleV(n.p, r, c);
        DrawCircleV(n.p, r*2.8f, ColorAlpha(c, 0.25f)); // soft halo
    }
    EndBlendMode();
}
