add_subdirectory(binaryClock)
add_subdirectory(weatherForecast)
add_subdirectory(config)
add_subdirectory(position)
add_subdirectory(communication)

set(ALL_SOURCES
    ${ALL_SOURCES}
    PARENT_SCOPE
)

set(ALL_HEADERS
    ${ALL_HEADERS} 
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS 
    ${ALL_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    PARENT_SCOPE
)
