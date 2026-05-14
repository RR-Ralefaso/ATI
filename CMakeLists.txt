cmake_minimum_required(VERSION 3.10)
project(ATI_Project VERSION 2026.0)

set(CMAKE_CXX_STANDARD 17)

# Find Libraries
find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(FFTW3 REQUIRED fftw3)

# Include directories: tells compiler where src/ folder is
include_directories(src ${SDL2_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS} ${FFTW3_INCLUDE_DIRS})

# Define executable: Note the paths to your .cpp files
add_executable(ati_app app.cpp src/Equations.cpp)

# Link everything together
target_link_libraries(ati_app 
    ${SDL2_LIBRARIES} 
    SDL2_mixer 
    ${FFTW3_LIBRARIES} 
    m
)