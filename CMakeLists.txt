cmake_minimum_required(VERSION 3.16)

set(PROJECT mainApp)

project(${PROJECT} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED)
find_package(Qt6 6.3 COMPONENTS Gui REQUIRED)
find_package(Qt6 6.3 COMPONENTS Core REQUIRED)
find_package(Qt6 6.3 COMPONENTS Positioning REQUIRED)
find_package(Qt6 6.3 COMPONENTS Network REQUIRED)
find_package(Qt6 6.3 COMPONENTS Mqtt REQUIRED)


set(CMAKE_USE_RELATIVE_PATHS ON)

file(GLOB_RECURSE COMPONENT_SOURCES components/*.cpp)
file(GLOB_RECURSE COMPONENT_HEADERS components/*.h)

list(APPEND QML_COMPONENTS
    components/binaryClock/BinaryClock.qml
    components/weatherForecast/WeatherForecast.qml
)

set(MAIN_APP mainApp/mainApp.cpp mainApp/mainApp.h)

set(COMPONENTS ${COMPONENT_SOURCES} ${COMPONENT_HEADERS}  util/util.h)

qt_add_resources(COMPONENTS resources.qrc)

qt_add_executable(${PROJECT}
    ${COMPONENTS}
    ${MAIN_APP}
    main.cpp
)

qt_add_qml_module(${PROJECT}
    URI binaryClock
    VERSION 1.0
    QML_FILES
    main.qml
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

target_include_directories(${PROJECT} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/util
    ${CMAKE_CURRENT_SOURCE_DIR}/components/binaryClock
    ${CMAKE_CURRENT_SOURCE_DIR}/components/weatherForecast
    ${CMAKE_CURRENT_SOURCE_DIR}/components/Communication/Network
    ${CMAKE_CURRENT_SOURCE_DIR}/mainApp
)

target_link_libraries(${PROJECT}
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
    Qt6::Positioning
    Qt6::Network
    Qt6::Mqtt
)

install(TARGETS ${PROJECT}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
