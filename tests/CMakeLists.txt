file(GLOB_RECURSE RES_FILES "resources/*")

add_executable(window window/main.cpp )
target_link_libraries(window wookie ${EXTRA_LIBS})

add_executable(resource resource/main.cpp )
target_link_libraries(resource wookie ${EXTRA_LIBS})

add_executable(item item/main.cpp )
target_link_libraries(item wookie ${EXTRA_LIBS})

file( COPY resources
    DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
)
message(STATUS "Resources copied to: ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}")

