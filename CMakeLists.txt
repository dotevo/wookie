cmake_minimum_required(VERSION 2.8.4)
project(wookie CXX)

set(wookie_LIBRARIES wookie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

option(WOOKIE_BUILD_TESTS "Build the WOOKIE test programs" ON)
option(WOOKIE_BUILD_SHARED "Build the shared lib" OFF)

#Build GLFW
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW test programs" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw)

#Build GL3W
execute_process(COMMAND python ${CMAKE_SOURCE_DIR}/libs/gl3w/gl3w_gen.py)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/gl3w)



#Includes
include_directories(${CMAKE_SOURCE_DIR}/libs/glfw/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/gl3w/include)
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)


#Wookie
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")
aux_source_directory(src SOURCES)
aux_source_directory(src/ecs SOURCES)

if (WOOKIE_BUILD_SHARED)
    add_library(wookie SHARED ${SOURCES} ${HEADERS})
else()
    add_library(wookie ${SOURCES} ${HEADERS})
endif()

if (WOOKIE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
