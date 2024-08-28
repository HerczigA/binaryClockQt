add_subdirectory(positionResources)

file(GLOB SOURCES *.cpp)
file(GLOB HEADERS *.h)

set(ALL_SOURCES 
    ${ALL_SOURCES} 
    ${SOURCES}
    ${HEADERS}
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)