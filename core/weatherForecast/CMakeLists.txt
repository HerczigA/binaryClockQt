add_library(weatherForecast OBJECT 
    weatherforecast.cpp 
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:position> PARENT_SCOPE)
set(ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

target_include_directories(weatherForecast PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(weatherForecast PUBLIC 
    Qt6::Core 
)