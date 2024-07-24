add_library(binaryClock OBJECT 
    binaryClock.cpp 
)

set(ALL_OBJECT_FILES ${ALL_OBJECT_FILES} $<TARGET_OBJECTS:binaryClock> PARENT_SCOPE)
set(ALL_INCLUDE_DIRS ${ALL_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} PARENT_SCOPE)

target_include_directories(binaryClock PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_SOURCE_DIR}
    )

target_link_libraries(binaryClock PUBLIC 
    Qt6::Core 
    # utilLib
)



# target_include_directories(fifthDay PUBLIC 
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${CMAKE_CURRENT_SOURCE_DIR}/..
# )
