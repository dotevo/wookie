
add_executable(window window/main.cpp )
target_link_libraries(window wookie gl3w glfw ${GLFW_LIBRARIES})
