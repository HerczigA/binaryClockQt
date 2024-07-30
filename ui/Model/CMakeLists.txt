add_subdirectory(BinaryClockModel)
#add_subdirectory(WeatherForecastModel)

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
