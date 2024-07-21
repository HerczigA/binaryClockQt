add_library(mainAppLib STATIC 
    mainApp.cpp 
    mainApp.h
)

target_include_directories(mainAppLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(mainAppLib PUBLIC 
    Qt6::Core 
    # coreLib
    binaryClockLib
    weatherForecastLib
    utilLib
    configLib
    positionLib
    serialLib
    networkLib
)
