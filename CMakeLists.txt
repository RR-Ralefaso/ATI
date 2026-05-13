cmake_minimum_required(VERSION 3.14) # FetchContent is more stable here

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# --- 1. Automated Dependency Management ---
include(FetchContent)

# Declare the SDL2 dependency
FetchContent_Declare(
    SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        release-2.28.5  # Stable version
)

# Download and add to the build tree
FetchContent_MakeAvailable(SDL2)

# --- 2. Define Source Files ---
set(SOURCES 
    src/main.cpp 
    src/equations.cpp
)

# --- 3. Add the Executable ---
add_executable(${PROJECT_NAME} ${SOURCES})

# --- 4. Link SDL2 ---
# When using FetchContent, SDL2 exports the target as 'SDL2::SDL2' 
# or simply 'SDL2' depending on the version. 
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

if(WIN32)
    # SDL2main is required for the WinMain entry point on Windows
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

# --- 5. Run Helper ---
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running ${PROJECT_NAME}..."
    USES_TERMINAL
)