cmake_minimum_required(VERSION 3.18)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)

# --- Dependencies ---

# Fetching SDL3 (Renamed from SDL2 to match the actual library being downloaded)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-3.2.0
    GIT_PROGRESS   TRUE
)

# Fetching SDL3_mixer
FetchContent_Declare(
    SDL3_mixer
    GIT_REPOSITORY https://github.com/libsdl-org/SDL_mixer.git
    GIT_TAG        main
    GIT_PROGRESS   TRUE
)

# Make sure these names match the Declare blocks exactly
FetchContent_MakeAvailable(SDL3 SDL3_mixer)

# --- Executable ---

set(SOURCES
    Main.cpp
    src/Equations.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

# Link against the SDL3 namespace targets
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_mixer::SDL3_mixer
)

# --- Helper Targets ---

# Use generator expressions ($<TARGET_FILE>) so it works even if the 
# binary is placed in a subfolder (like /build/Debug/ATI.exe)
add_custom_target(run
    COMMAND $<TARGET_FILE:${PROJECT_NAME}>
    DEPENDS ${PROJECT_NAME}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    USES_TERMINAL
)