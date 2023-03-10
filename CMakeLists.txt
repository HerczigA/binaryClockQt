cmake_minimum_required(VERSION 3.16)

project(binaryClock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Qt6 6.3 COMPONENTS Quick REQUIRED)
find_package(Qt6 6.3 COMPONENTS Gui REQUIRED)
find_package(Qt6 6.3 COMPONENTS Core REQUIRED)

set(CMAKE_USE_RELATIVE_PATHS ON)

set(PROJECT appbinaryClock)

set(BIN_CLOCK_SRC binaryClock/binaryClock.cpp binaryClock/binaryClock.h
                    mainApp/mainApp.cpp mainApp/mainApp.h)

qt_add_executable(${PROJECT}
    ${BIN_CLOCK_SRC}
    main.cpp
)

qt_add_qml_module(${PROJECT}
    URI binaryClock
    VERSION 1.0
    QML_FILES
    main.qml
    binaryClock/BinaryClock.qml

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
    ${CMAKE_CURRENT_SOURCE_DIR}/binaryClock
    ${CMAKE_CURRENT_SOURCE_DIR}/mainApp
)

target_link_libraries(${PROJECT}
    PRIVATE
    Qt6::Quick
    Qt6::Core
    Qt6::Gui
#    pthread
)

install(TARGETS ${PROJECT}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
