# Reference: https://doc.qt.io/qt-6/cmake-manual.html

cmake_minimum_required(VERSION 3.21.1)

# Add folder where are supportive functions
set(CMAKE_MODULE_PATH ${PATH} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# modify to your own qt dir
set(CMAKE_PREFIX_PATH /Users/goldenpigeon/Qt/6.6.1/macos/lib/cmake/)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_BUILD_TYPE Debug)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Include Qt basic functions
include(QtCommon)

# Basic information about project

project(wifi-connector VERSION 1.0)

# Set PROJECT_VERSION_PATCH and PROJECT_VERSION_TWEAK to 0 if not present, needed by add_project_meta
fix_project_version()

# Set additional project information
set(COMPANY "GoldenPigeon")
set(COPYRIGHT "Copyright 2024 GoldenPigeon. All rights reserved.")
set(IDENTIFIER "io.github.goldenpigeon.wifi_connector")

set(SOURCE_FILES
    src/main.cpp
    src/mainwindow.cpp
    src/utils.cpp
)

file(GLOB MAIN_HEAD ${CMAKE_CURRENT_SOURCE_DIR}/include/*.h)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_project_meta(META_FILES_TO_INCLUDE)

set(RESOURCE_FILES example.qrc)

find_package(Qt6 COMPONENTS Widgets REQUIRED)

qt_standard_project_setup()

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE
    ${SOURCE_FILES} ${META_FILES_TO_INCLUDE} ${RESOURCE_FILES} ${MAIN_HEAD}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_precompile_headers(${PROJECT_NAME} INTERFACE QtWidgets.h)

target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

install(
    TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION /Applications
)
