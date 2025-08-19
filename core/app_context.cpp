#include "core/app_context.hpp"

AppContext& AppContext::Instance() {
    static AppContext s;
    return s;
}

void AppContext::Init(int w, int h, DreamWorld* world, RenderCtx* renderer) {
    m_screenW = w; 
    m_screenH = h;
    m_world = world; 
    m_renderer = renderer;
}
void AppContext::SetDelta(float dt) { m_dt = dt; }
