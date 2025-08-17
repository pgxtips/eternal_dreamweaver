cmake_minimum_required(VERSION 4.0)
project(Eternal_Dreamweaver LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(FETCHCONTENT_BASE_DIR "${CMAKE_SOURCE_DIR}/.deps")

include(FetchContent)

# Turn off shared builds, and skip raylib extras
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

set(CMAKE_POLICY_VERSION_MINIMUM 4.0)

# Pin a specific version/commit for reproducible builds
set(RAYLIB_TAG 5.0 CACHE STRING "raylib tag/commit to fetch")

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG        ${RAYLIB_TAG}
)
FetchContent_MakeAvailable(raylib) 

add_executable(eternal_dreamweaver main.cpp)
target_link_libraries(eternal_dreamweaver PRIVATE raylib)
