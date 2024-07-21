add_subdirectory(extensions)

add_library(networkLib STATIC 
    network.cpp 
    network.h
)

target_include_directories(networkLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(networkLib PUBLIC 
    Qt6::Core
    Qt6::Network
    utilLib
)
