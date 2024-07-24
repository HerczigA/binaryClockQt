add_library(position OBJECT 
    position.cpp 
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:position> PARENT_SCOPE)
set(ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

message("asd")
message(${CMAKE_CURRENT_SOURCE_DIR})
message(${PROJECT_SOURCE_DIR})

target_include_directories(position PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    $ENV{HOME}/Qt6/qtHost/include/QtPositioning
    )

target_link_libraries(position PUBLIC 
    Qt6::Core
    Qt6::Positioning
    Qt6::Location
)

