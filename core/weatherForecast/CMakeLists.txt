add_library(weatherForecastLib STATIC 
    weatherforecast.cpp 
    weatherforecast.h
)

target_include_directories(weatherForecastLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(weatherForecastLib PUBLIC 
    Qt6::Core 
    utilLib
)
