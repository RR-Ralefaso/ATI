cmake_minimum_required(VERSION 3.10)

project(ATI VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Find SDL2
find_package(SDL2 REQUIRED)

# 2. Define Source Files
set(SOURCES 
    src/main.cpp 
    src/equations.cpp
)

# 3. Add the Executable
add_executable(${PROJECT_NAME} ${SOURCES})

# 4. Link SDL2
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE SDL2::SDL2main)
endif()

# 5. Add "make run" capability
# This creates a command that depends on the executable being built first
add_custom_target(run
    COMMAND ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}
    DEPENDS ${PROJECT_NAME}
    COMMENT "Running ${PROJECT_NAME}..."
    USES_TERMINAL
)