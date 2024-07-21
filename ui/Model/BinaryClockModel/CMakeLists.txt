add_library(binaryClockModelLib STATIC 
    binaryClockModel.cpp 
    binaryClockModel.h
)

target_include_directories(binaryClockModelLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(binaryClockModelLib PUBLIC 
    Qt6::Core 
    utilLib
)
