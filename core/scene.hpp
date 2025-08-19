#pragma once
#include <functional>
#include <memory>

// interface for all scenes
struct IScene {
    virtual ~IScene() = default;

    virtual const char* name() const = 0;

    // lifecycle
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
    virtual void onPause() = 0;
    virtual void onResume() = 0;

    // per-frame
    virtual void handleInput() = 0;
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual bool blocksBelow() = 0;

};

using ScenePtr = std::unique_ptr<IScene>;
using SceneFactory = std::function<ScenePtr()>;
