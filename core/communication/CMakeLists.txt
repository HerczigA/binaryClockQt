# add_subdirectory(network)
add_subdirectory(serial)

set(ALL_SOURCES
    ${ALL_SOURCES}
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)