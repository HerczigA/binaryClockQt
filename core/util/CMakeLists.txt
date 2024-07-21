add_library(utilLib STATIC 
    util.cpp
    util.h
)

target_include_directories(utilLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(utilLib PUBLIC 
    Qt6::Core
)