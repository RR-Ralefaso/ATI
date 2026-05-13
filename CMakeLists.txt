cmake_minimum_required(VERSION 3.18)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# Fixed "POSITORY" to "GIT_REPOSITORY" and updated tags to stable SDL3 releases
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.0
    GIT_PROGRESS   TRUE
)

FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG        release-3.0.0
    GIT_PROGRESS   TRUE
)

FetchContent_MakeAvailable(SDL2 SDL_mixer)

set(SOURCES
    Main.cpp
    src/Equations.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# SDL3 uses SDL3::SDL3 targets; SDL2main is now integrated into the main library in SDL3
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
)

add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    USES_TERMINAL
)