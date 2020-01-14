#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.15)


# Enable debug symbols by default
# must be done before project() statement
if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
endif()
# (you can also set it on the command line: -D CMAKE_BUILD_TYPE=Release)

project(myproject)

include_directories("${CMAKE_SOURCE_DIR}/src")

# Define sources and executable
set(EXECUTABLE_NAME "myproject")
add_executable(${EXECUTABLE_NAME} src/main.cpp src/stopwatch.cpp src/mandelbrot.cpp)


#Find any version 2.X of SFML
#See the FindSFML.cmake file for additional details and instructions
find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()


message("${CMAKE_SOURCE_DIR}/src")



