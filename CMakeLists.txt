cmake_minimum_required(VERSION 3.10)
project(AudioToImage VERSION 1.0)

# 1. Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 2. Find Dependencies
# This looks for the development files on your system
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW3 REQUIRED fftw3)

# 3. Include Directories
# Tells the compiler to look in 'src' for Equations.hpp and stb_image_write.h
include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIRS})

# 4. Define the Executable
# We name it 'ati_app' to avoid confusion with your directory names
add_executable(ati_app app.cpp src/Equations.cpp)

# 5. Link Libraries
# Connects the compiled code to the actual library binaries
target_link_libraries(ati_app 
    ${SDL2_LIBRARIES} 
    SDL2_mixer 
    ${FFTW3_LIBRARIES} 
    m
)

# 6. Post-Build: Auto-Run the Program
# This command runs the executable immediately after a successful build
add_custom_command(TARGET ati_app POST_BUILD
    COMMAND ./ati_app
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
    COMMENT "Launching AudioMapper..."
)