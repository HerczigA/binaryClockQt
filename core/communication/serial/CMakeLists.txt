add_library(serial INTERFACE)

target_include_directories(serial
    INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}
)

add_subdirectory(i2c)

set(ALL_OBJECT_FILES 
    ${ALL_OBJECT_FILES} 
    # $<TARGET_OBJECTS:serial>
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)

if(wiringPi_LIB)
    message("Found wiringPI")
    target_link_libraries(serial INTERFACE Qt6::Core ${wiringPi_LIB})
else()
    target_link_libraries(serial INTERFACE Qt6::Core)
endif()