cmake_minimum_required(VERSION 4.0)
project(Eternal_Dreamweaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POLICY_VERSION_MINIMUM 4.0)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.deps")

# turn off shared builds, and skip raylib extras
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

set(RAYLIB_TAG 5.5 CACHE STRING "raylib tag/commit to fetch")

include(FetchContent)

# Dear ImGui (dep of rlimgui)
# ============================================
FetchContent_Declare(imgui
    GIT_REPOSITORY https://github.com/ocornut/imgui.git
    GIT_TAG v1.92.1
)
FetchContent_MakeAvailable(imgui)
add_library(imgui STATIC 
    ${imgui_SOURCE_DIR}/imgui.cpp
    ${imgui_SOURCE_DIR}/imgui_draw.cpp
    ${imgui_SOURCE_DIR}/imgui_tables.cpp
    ${imgui_SOURCE_DIR}/imgui_widgets.cpp
)
target_include_directories(imgui PUBLIC ${imgui_SOURCE_DIR})
# ============================================


# ============================================
# Raylib Imgui bindings lib
# ============================================
FetchContent_Declare(
    rlimgui
    GIT_REPOSITORY https://github.com/raylib-extras/rlImGui.git
    GIT_SUBMODULES ""
    GIT_TAG main
)
FetchContent_MakeAvailable(rlimgui)
# build rlImGui shim as a static lib
add_library(rlImGui STATIC
    ${rlimgui_SOURCE_DIR}/rlImGui.cpp
)
target_include_directories(rlImGui PUBLIC
  ${rlimgui_SOURCE_DIR}
  ${imgui_SOURCE_DIR}
)
target_link_libraries(rlImGui PUBLIC imgui raylib)
# ============================================



# ============================================
# raylib dep
# ============================================
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        ${RAYLIB_TAG}
)
FetchContent_MakeAvailable(raylib) 
# ============================================


file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    ${CMAKE_SOURCE_DIR}/core/*.cpp
    ${CMAKE_SOURCE_DIR}/scenes/*.cpp
)

add_executable(eternal_dreamweaver ${SOURCES})
target_include_directories(eternal_dreamweaver PRIVATE
  ${CMAKE_SOURCE_DIR}
  ${imgui_SOURCE_DIR}
  ${rlimgui_SOURCE_DIR}
)

target_link_libraries(eternal_dreamweaver PRIVATE raylib rlImGui)
