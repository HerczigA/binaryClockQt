set(ALL_SOURCES 
    ${ALL_SOURCES} 
    ${CMAKE_CURRENT_SOURCE_DIR}/i2c.cpp
    PARENT_SCOPE
)

set(ALL_INCLUDE_DIRS
    ${ALL_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    PARENT_SCOPE
)

# Add the header to a list of interface headers (optional, for documentation)
# set(INTERFACE_HEADERS
#     ${INTERFACE_HEADERS}
#     ${CMAKE_CURRENT_SOURCE_DIR}/i2c.h
#     PARENT_SCOPE
# )

set(NEEDED_LIBS ${NEEDED_LIBS} Qt6::Core PARENT_SCOPE)