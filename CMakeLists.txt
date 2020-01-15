#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.15)

# Project name 
set(APP_NAME "MandelbrotSet")
project(${APP_NAME} VERSION 1.0
                    LANGUAGES CXX)

include_directories("${CMAKE_SOURCE_DIR}/src")

# Define sources and executable
add_executable(${APP_NAME} src/main.cpp src/stopwatch.cpp src/mandelbrot.cpp)

#Find any version 2.X of SFML
find_package(SFML 2.5 COMPONENTS graphics audio window system REQUIRED)
target_link_libraries(${APP_NAME} sfml-graphics sfml-audio sfml-window sfml-system)

# Add compile warnings
target_compile_options(${APP_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)




