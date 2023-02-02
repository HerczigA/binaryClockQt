cmake_minimum_required(VERSION 3.16)

project(binaryClock VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.2 COMPONENTS Quick REQUIRED)
find_package(Qt6 REQUIRED COMPONENTS Core)


set(PROJECT appbinaryClock)

set(BIN_CLOCK_SRC binaryClock/binaryClock.cpp binaryClock/binaryClock.h)

qt_add_executable(${PROJECT}
    ${BIN_CLOCK_SRC}
    main.cpp
)

qt_add_qml_module(${PROJECT}
    URI binaryClock
    VERSION 1.0
    QML_FILES main.qml 
)

set_target_properties(${PROJECT} PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(${PROJECT} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/binaryClock
)

target_link_libraries(${PROJECT}
    PRIVATE
    Qt6::Quick
    Qt6::Core
)

install(TARGETS ${PROJECT}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
