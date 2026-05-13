cmake_minimum_required(VERSION 3.14)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Automated Dependency Management ---
include(FetchContent)

# Optional: Force CMake to check for updates on every re-configure
# set(FETCHCONTENT_UPDATES_DISCONNECTED OFF) 

# Declare SDL2
# Note: Using a specific tag is safer, but if you want the "latest" 
# updates, you could use a branch name like 'main' or 'SDL2'.
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.28.5  
    GIT_PROGRESS   TRUE
)

# Declare SDL_mixer
FetchContent_Declare(
    SDL_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG        release-2.8.0
    GIT_PROGRESS   TRUE
)

# Populate dependencies
FetchContent_MakeAvailable(SDL2 SDL_mixer)

# --- 2. Define Source Files ---
set(SOURCES 
    src/main.cpp 
    src/Equations.cpp
)

# --- 3. Add the Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 4. Link Libraries ---
# FetchContent for SDL2 usually exports targets in the SDL2:: namespace
target_link_libraries(${PROJECT_NAME} PRIVATE 
    SDL2::SDL2-static 
    SDL2_mixer::SDL2_mixer-static
)

if(WIN32)
    # SDL2::SDL2main is required for WinMain entry point on Windows
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

# --- 5. Run Helper ---
add_custom_target(run
    COMMAND ${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running ${PROJECT_NAME}..."
    WORKING_DIRECTORY ${CMAKE_PROJECT_DIR}
    USES_TERMINAL
)