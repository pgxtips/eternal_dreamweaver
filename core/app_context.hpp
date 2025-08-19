#pragma once

struct DreamWorld; struct RenderCtx;

class AppContext {
public:
    static AppContext& Instance();

    void Init(int screenW, int screenH, DreamWorld* world, RenderCtx* renderer);
    void SetDelta(float dt);

    // getters
    float dt() const { return m_dt; }
    int screenW() const { return m_screenW; }
    int screenH() const { return m_screenH; }
    DreamWorld* world() const { return m_world; }
    RenderCtx* renderer() const { return m_renderer; }

    // non-copyable
    AppContext(const AppContext&) = delete;
    AppContext& operator=(const AppContext&) = delete;

private:
    AppContext() = default;
    float m_dt = 0.f;
    int   m_screenW = 0, m_screenH = 0;
    DreamWorld* m_world = nullptr;
    RenderCtx*  m_renderer = nullptr;
};
