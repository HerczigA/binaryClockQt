add_library(configLib STATIC 
    config.cpp 
    config.h
)

target_include_directories(configLib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(configLib PUBLIC 
    Qt6::Core 
    utilLib
)