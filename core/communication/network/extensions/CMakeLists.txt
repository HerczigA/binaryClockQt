add_library(jsonHandlerLib STATIC 
    jsonhandler.cpp 
    jsonhandler.h
)

target_include_directories(jsonHandlerLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(jsonHandlerLib PUBLIC 
    Qt6::Core 
    utilLib
)