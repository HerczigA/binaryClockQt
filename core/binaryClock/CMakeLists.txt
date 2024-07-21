add_library(binaryClockLib STATIC 
    binaryClock.cpp 
    binaryClock.h
)

target_include_directories(binaryClockLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(binaryClockLib PUBLIC 
    Qt6::Core 
    utilLib
)
