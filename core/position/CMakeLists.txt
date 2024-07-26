set(ALL_SOURCES 
    ${ALL_SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/position.cpp
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)
    
set(NEEDED_LIBS ${NEEDED_LIBS} 
    Qt6::Core
    Qt6::Positioning
    Qt6::Location
    PARENT_SCOPE
)
