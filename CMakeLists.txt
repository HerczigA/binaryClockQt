cmake_minimum_required(VERSION 3.16)

set(PROJECT AviCado)

project(${PROJECT} VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
    add_compile_definitions(WIRINGPI_USAGE=1)
    find_library(wiringPi_LIB wiringPi)
    list(APPEND LinkLibraries ${wiringPi_LIB})
else()
    add_compile_definitions(WIRINGPI_USAGE=0)
endif()

set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt6/qtHost/lib/cmake)
# set(QTHOST_PATH $ENV{HOME}/Qt6/QtHost/lib/cmake)
message(${CMAKE_PREFIX_PATH})

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Gui REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Core REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Positioning REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Network REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Mqtt REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Location REQUIRED PATHS ${CMAKE_PREFIX_PATH})

set(CMAKE_USE_RELATIVE_PATHS ON)

# if(make_static)

# else()
# file(GLOB_RECURSE COMPONENT_SOURCES components/*.cpp)
# file(GLOB_RECURSE COMPONENT_HEADERS components/*.h)
# set(MAIN_APP mainApp/mainApp.cpp mainApp/mainApp.h)

# endif()


add_subdirectory(mainApp)
add_subdirectory(core)

include_directories(${CMAKE_SOURCE_DIR})

file(GLOB_RECURSE QML_COMPONENTS qml/*.qml)

message(QML_COMPONENTS ${QML_COMPONENTS})


# set(COMPONENT_SOURCES ${COMPONENT_SOURCES} threadModul/threadModul.cpp)
# set(COMPONENT_HEADERS ${COMPONENT_HEADERS} threadModul/threadModul.h)

# set(COMPONENTS ${COMPONENT_SOURCES} ${COMPONENT_HEADERS} )

message("CMAKE_SYSTEM_NAME " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM_PROCESSOR " ${CMAKE_SYSTEM_PROCESSOR})

qt_add_resources(COMPONENTS resources.qrc)

qt_add_executable(${PROJECT}
    # ${COMPONENTS}
    # ${MAIN_APP}
    main.cpp
    resources.qrc
)

qt_add_qml_module(${PROJECT}
    URI binaryClock
    VERSION 1.0
    QML_FILES
    ${QML_COMPONENTS}
)

set_target_properties(${PROJECT} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    BUILD_WITH_INSTALL_RPATH FALSE
    # LINK_FLAGS "-Wl,-rpath,$ORIGIN/lib"
)

# target_include_directories(${PROJECT} PUBLIC
#     ${CMAKE_CURRENT_SOURCE_DIR}/util
#     # ${CMAKE_CURRENT_SOURCE_DIR}/components/binaryClock
#     # ${CMAKE_CURRENT_SOURCE_DIR}/components/weatherForecast
#     ${CMAKE_CURRENT_SOURCE_DIR}/components/Communication/serial/i2c
#     ${CMAKE_CURRENT_SOURCE_DIR}/components/Communication/Network
#     ${CMAKE_CURRENT_SOURCE_DIR}/components/Communication/Network/Extensions
#     # ${CMAKE_CURRENT_SOURCE_DIR}/components/config
#     ${CMAKE_CURRENT_SOURCE_DIR}/components/position
#     ${CMAKE_CURRENT_SOURCE_DIR}/components/storeObject
#     ${CMAKE_CURRENT_SOURCE_DIR}/mainApp
#     # ${CMAKE_CURRENT_SOURCE_DIR}/threadModul
# )

target_link_libraries(${PROJECT}
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Positioning
    Qt6::Network
    Qt6::Mqtt
    Qt6::Location
    # coreLib
    mainAppLib
)

install(TARGETS ${PROJECT}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
