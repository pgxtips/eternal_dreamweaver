#pragma once
#include <cstddef>
#include <cstdint>

enum class SceneID : std::uint8_t {
    MainMenu = 0,
    Game,
    Pause,

    COUNT,
};

constexpr std::size_t to_index(SceneID id) {
    return static_cast<std::size_t>(id);
}
