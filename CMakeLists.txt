cmake_minimum_required(VERSION 2.8.4)
project(Iso CXX)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw-3.0.4)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/gl3w)

include_directories(${CMAKE_SOURCE_DIR}/libs/glfw-3.0.4/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/gl3w/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)
include_directories(${CMAKE_SOURCE_DIR}/src/ecs)
include_directories(${CMAKE_SOURCE_DIR}/src)

aux_source_directory(src SOURCES)
aux_source_directory(src/ecs SOURCES)

set(SOURCE_FILES main.cpp ${SOURCES})

add_executable(Iso ${SOURCE_FILES})

target_link_libraries(Iso gl3w glfw ${GLFW_LIBRARIES})
