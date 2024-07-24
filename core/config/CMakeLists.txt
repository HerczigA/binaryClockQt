add_library(config OBJECT 
    config.cpp 
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:config> PARENT_SCOPE)
set(ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

target_include_directories(config PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(config PUBLIC 
    Qt6::Core 
)
