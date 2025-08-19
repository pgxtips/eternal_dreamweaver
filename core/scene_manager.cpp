#include "scene_manager.hpp"
#include "scene_id.hpp"
#include <utility>

void SceneManager::registerFactory(SceneID id, SceneFactory factory) {
    m_factories[to_index(id)] = std::move(factory);
}

void SceneManager::set(SceneID id) {
    clear();
    push(id);
}

void SceneManager::push(SceneID id) {
    auto& make = m_factories[to_index(id)];
    if (!make) return;
    m_stack.emplace_back(make());
    m_stack.back()->onEnter();
}

void SceneManager::pop() {
    if (m_stack.empty()) return;
    m_stack.back()->onExit();
    m_stack.pop_back();
}

void SceneManager::handleInput() {
    if (!m_stack.empty()) m_stack.back()->handleInput();
}

void SceneManager::update() {
    if (!m_stack.empty()) m_stack.back()->update();
}

void SceneManager::draw() {
    // draw from the first scene that blocks below, up to the top
    int first = 0;
    for (int i = (int)m_stack.size() - 1; i >= 0; --i) {
        if (m_stack[i]->blocksBelow()) { first = i; break; }
    }
    for (int i = first; i < (int)m_stack.size(); ++i) {
        m_stack[i]->draw();
    }
}

std::string SceneManager::currentSceneName() const {
    return m_stack.empty() ? std::string{} : std::string(m_stack.back()->name());
}

void SceneManager::clear() {
    while (!m_stack.empty()) {
        m_stack.back()->onExit();
        m_stack.pop_back();
    }
}
