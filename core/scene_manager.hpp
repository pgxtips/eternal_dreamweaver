#pragma once
#include <string>
#include <vector>
#include <memory>
#include "core/scene.hpp"
#include "core/scene_id.hpp"

class SceneManager {
public:
    using FactoryArray = std::array<SceneFactory, to_index(SceneID::COUNT)>;

    void registerFactory(SceneID id, SceneFactory factory);

    // immediate operations
    void set (SceneID id);
    void push(SceneID id); 
    void pop ();

    // per-frame 
    void handleInput();
    void update();
    void draw();

    // for debug 
    std::string currentSceneName() const;

private:
    FactoryArray m_factories {}; 
    std::vector<ScenePtr> m_stack;

    void clear();  // helper for set()
};
