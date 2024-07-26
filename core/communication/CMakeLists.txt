add_subdirectory(network)
add_subdirectory(serial)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)