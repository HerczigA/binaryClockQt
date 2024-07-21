add_subdirectory(i2c)

add_library(serialLib STATIC 
    serial.h
)

target_include_directories(serialLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(serialLib PUBLIC 
    Qt6::Core 
    utilLib
)
