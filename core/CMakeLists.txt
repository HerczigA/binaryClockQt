set(ALL_OBJECT_FILES "")
set(ALL_INCLUDE_DIRS "")

add_subdirectory(binaryClock)
add_subdirectory(weatherForecast)
add_subdirectory(config)
add_subdirectory(util)
add_subdirectory(position)
add_subdirectory(communication)

add_library(coreLib STATIC 
    ${ALL_OBJECT_FILES}
)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES}
    $<TARGET_OBJECTS:coreLib>
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS 
    ${ALL_INCLUDE_DIRS} 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    PARENT_SCOPE
)

target_include_directories(coreLib PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
)