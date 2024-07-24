add_library(i2c OBJECT 
    i2c.cpp 
)

target_include_directories(i2c PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR} 
    ${PROJECT_SOURCE_DIR}
)

target_link_libraries(i2c PUBLIC 
    Qt6::Core
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:i2c> PARENT_SCOPE)
set(ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)
