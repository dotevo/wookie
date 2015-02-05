cmake_minimum_required(VERSION 2.8.4)
project(wookie CXX)

set(wookie_LIBRARIES wookie)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(FindPkgConfig)

SET(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

#===OPTIONS===
option(WOOKIE_BUILD_TESTS "Build the WOOKIE test programs" ON)
option(WOOKIE_BUILD_SHARED "Build the shared lib" OFF)
option(WOOKIE_USE_SDL "Build with SDL" ON)

#===LIBS===
set(EXTRA_LIBS)

#JSONCPP
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/jsoncpp)
include_directories(${CMAKE_SOURCE_DIR}/libs/jsoncpp/include)
list(APPEND EXTRA_LIBS jsoncpp_lib_static)
message(STATUS "jsoncpp added")

#GLM
include_directories(${CMAKE_SOURCE_DIR}/libs/glm)
message(STATUS "GLM added")

#Build GLFW
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build the GLFW example programs" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build the GLFW test programs" FORCE)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/glfw)
include_directories(${CMAKE_SOURCE_DIR}/libs/glfw/include)
list(APPEND EXTRA_LIBS glfw ${GLFW_LIBRARIES})
message(STATUS "GLFW added")

#Build GL3W
execute_process(COMMAND python ${CMAKE_SOURCE_DIR}/libs/gl3w/gl3w_gen.py)
add_subdirectory(${CMAKE_SOURCE_DIR}/libs/gl3w)
list(APPEND EXTRA_LIBS gl3w)
include_directories(${CMAKE_SOURCE_DIR}/libs/gl3w/include)
message(STATUS "GL3W added")

add_definitions( -DWIN32 )

#SDL
if(WOOKIE_USE_SDL)
    add_definitions( -DHAVE_SDL )
    list(APPEND EXTRA_LIBS SDL2_image)
    list(APPEND EXTRA_LIBS SDL2)
    aux_source_directory(src/rendering/SDL SOURCES)
    message(STATUS "SDL added")
endif()

#JSONCPP
#find_package(Jsoncpp)
#if(JSONCPP_FOUND)
#    message(STATUS "JSONCPP found")
#    list(APPEND EXTRA_LIBS jsoncpp)
#else()
#    message(FATAL_ERROR "JSONCPP not found")
#    return()
#endif()

#Wookie
include_directories(${CMAKE_SOURCE_DIR}/include)
file(GLOB_RECURSE HEADERS "${CMAKE_SOURCE_DIR}/include/*.h")

aux_source_directory(src SOURCES)
aux_source_directory(src/ecs SOURCES)
aux_source_directory(src/core SOURCES)
aux_source_directory(src/rendering SOURCES)
aux_source_directory(src/rendering/GL SOURCES)
aux_source_directory(src/resource SOURCES)
aux_source_directory(src/item SOURCES)

if(WOOKIE_BUILD_SHARED)
    add_library(wookie SHARED ${SOURCES} ${HEADERS})
else()
    add_library(wookie ${SOURCES} ${HEADERS})
endif()

if(WOOKIE_BUILD_TESTS)
    add_subdirectory(tests)
endif()
