add_library(positionLib STATIC 
    position.cpp 
    position.h
)

target_include_directories(positionLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(positionLib PUBLIC 
    Qt6::Core
    Qt6::Positioning
    Qt6::Location
    utilLib
)
