cmake_minimum_required(VERSION 3.10)

# 1. Project Setup
project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find SDL2
# This assumes SDL2 is installed on your system (e.g., via apt install libsdl2-dev)
find_package(SDL2 REQUIRED)

# 3. Define Source Files
# It's cleaner to list them in a variable, especially as your project grows
set(SOURCES 
    src/main.cpp 
    src/equations.cpp
)

# 4. Add the Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 5. Link SDL2
# This automatically handles the include directories and library linking
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

# Special handling for Windows entry points (WinMain) if you ever cross-compile
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()