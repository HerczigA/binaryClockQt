add_subdirectory(binaryClock)
add_subdirectory(weatherForecast)
add_subdirectory(config)
add_subdirectory(util)
add_subdirectory(position)
add_subdirectory(communication)

# Create the core static library
# add_library(coreLib STATIC
#     # $<TARGET_OBJECTS:binaryClock>
#     # $<TARGET_OBJECTS:weatherForecast>
#     # $<TARGET_OBJECTS:config>
#     # $<TARGET_OBJECTS:util>
#     # $<TARGET_OBJECTS:position>
#     # $<TARGET_OBJECTS:communication>
#     # binaryClock 
#     # weatherForecast 
#     # config 
#     # util 
#     # position 
#     # communication
# )


# # Link all component libraries to coreLib
# target_link_libraries(coreLib
#     PUBLIC
#     weatherForecast
#     config
#     util
#     position
#     communication
#     Qt6::Positioning
#     Qt6::Location
# )

# # Set include directories for coreLib
# target_include_directories(coreLib
#     PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}
#     ${PROJECT_SOURCE_DIR}
# )