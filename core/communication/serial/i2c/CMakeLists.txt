add_library(i2cLib STATIC 
    i2c.cpp 
    i2c.h
)

target_include_directories(i2cLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(i2cLib PUBLIC 
    Qt6::Core 
    utilLib
)