add_library(util OBJECT 
    util.cpp
)

target_include_directories(util PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES}
    $<TARGET_OBJECTS:util>
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS 
    ${ALL_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    PARENT_SCOPE
)

target_link_libraries(util PUBLIC 
    Qt6::Core
)
