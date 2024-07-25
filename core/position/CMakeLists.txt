add_library(position OBJECT 
    position.cpp 
)

target_include_directories(position PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    ${Qt6Positioning_INCLUDE_DIRS}
    ${Qt6Location_INCLUDE_DIRS}
)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES} 
    $<TARGET_OBJECTS:position> 
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS 
    ${ALL_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${Qt6Positioning_INCLUDE_DIRS}
    ${Qt6Location_INCLUDE_DIRS}
    PARENT_SCOPE
)

message("asd")
message(STATUS "Qt6Positioning_INCLUDE_DIRS: ${Qt6Positioning_INCLUDE_DIRS}")
message(STATUS "Qt6Location_INCLUDE_DIRS: ${Qt6Location_INCLUDE_DIRS}")
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})


target_link_libraries(position PUBLIC 
    Qt6::Core
    Qt6::Positioning
    Qt6::Location
)

