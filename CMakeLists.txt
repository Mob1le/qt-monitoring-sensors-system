cmake_minimum_required(VERSION 3.20)

project(qt-monitoring-sensors-system VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Core
    Widgets
    Gui
)

add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
    src/main_window.cpp
    include/main_window.h
    include/detector_data_model.h
    src/detector_data_model.cpp
    include/detector.h
    src/detector.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Core
    Qt5::Widgets
    Qt5::Gui
)