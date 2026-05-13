cmake_minimum_required(VERSION ION 3.18)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

FetchContent_Declare(
    SDL2
POSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-3.4.8
)

FetchContent_Declare(
    SDL_mixer
POSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG release-3.2.2
)

FetchContent_MakeAvailable(SDL2 SDL_mixer)

set(SOURCES
    Main.cpp
    src/Equations.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_mixer::SDL2_mixer
)

add_custom_target(run

    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)