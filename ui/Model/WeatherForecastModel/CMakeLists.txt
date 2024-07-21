add_library(weatherForecastModelLib STATIC 
    weatherForecastModel.cpp 
    weatherForecastModel.h
)

target_include_directories(weatherForecastModelLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(weatherForecastModelLib PUBLIC 
    Qt6::Core 
)
