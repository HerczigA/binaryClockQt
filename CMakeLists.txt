cmake_minimum_required(VERSION 3.16)

set(PROJECT AviCado)

project(${PROJECT} VERSION 0.1 LANGUAGES CXX)


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(QML_IMPORT_PATH ${CMAKE_SOURCE_DIR}/ui/qml CACHE STRING "" FORCE)


set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

# if(CMAKE_SYSTEM_PROCESSOR STREQUAL "arm")
#     add_compile_definitions(WIRINGPI_USAGE=1)
#     find_library(wiringPi_LIB wiringPi)
#     list(APPEND LinkLibraries ${wiringPi_LIB})
# else()
#     add_compile_definitions(WIRINGPI_USAGE=0)
# endif()

add_compile_definitions(WIRINGPI_USAGE=0)
    
set(CMAKE_PREFIX_PATH $ENV{HOME}/Qt6/qtHost/lib/cmake)

message(${CMAKE_PREFIX_PATH})

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Gui REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Core REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Positioning REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Network REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Mqtt REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Location REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(Qt6 6.3 COMPONENTS Qml REQUIRED PATHS ${CMAKE_PREFIX_PATH})

find_package(Qt6 6.3 COMPONENTS DBus REQUIRED PATHS ${CMAKE_PREFIX_PATH})
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLIB REQUIRED glib-2.0)
pkg_check_modules(GEOCLUE REQUIRED geoclue-2.0)

set(CMAKE_USE_RELATIVE_PATHS ON)
    
    # if(make_static)
    
    # else()

set(ALL_SOURCES "")
set(ALL_INCLUDE_DIRS "")
set(NEEDED_LIBS "")

# endif()


add_subdirectory(core)
add_subdirectory(mainApp)
add_subdirectory(ui)

file(GLOB_RECURSE QML_COMPONENTS ui/qml/*.qml)

message(STATUS "QML_COMPONENTS: ${QML_COMPONENTS}")

message("CMAKE_SYSTEM_NAME " ${CMAKE_SYSTEM_NAME})
message("CMAKE_SYSTEM_PROCESSOR " ${CMAKE_SYSTEM_PROCESSOR})

qt_add_resources(RESOURCE resources.qrc)

message(STATUS "ALL SOURCES: ${ALL_SOURCES}")

qt_add_executable(${PROJECT}
    ${RESOURCE}
    ${ALL_SOURCES}
    main.cpp
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
    LINK_FLAGS "-Wl,-rpath,$ORIGIN/lib"
)

target_include_directories(${PROJECT} PRIVATE
    ${ALL_INCLUDE_DIRS}
    ${GLIB_INCLUDE_DIRS}
    ${GEOCLUE_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT}
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Positioning
    Qt6::Network
    Qt6::Mqtt
    Qt6::Location
    Qt6::Qml
    Qt6::DBus
    ${GLIB_LIBRARIES}
    ${GEOCLUE_LIBRARIES}
)

install(TARGETS ${PROJECT}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
