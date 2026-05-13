cmake_minimum_required(VERSION 3.14)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Automated Dependency Management ---
include(FetchContent)

# Declare SDL2
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.28.5
)

# Declare SDL_mixer
FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG        release-2.8.0
)

# Make them both available
# Note: SDL2 must be available for SDL_mixer to configure correctly
FetchContent_MakeAvailable(SDL2 SDL_mixer)

# --- 2. Define Source Files ---
set(SOURCES 
    src/main.cpp 
    src/equations.cpp
)

# --- 3. Add the Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 4. Link Libraries ---
# We link both the base SDL2 and the Mixer extension
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL2::SDL2 
    SDL2_mixer::SDL2_mixer
)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

# --- 5. Run Helper ---
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running ${PROJECT_NAME}..."
    USES_TERMINAL
)