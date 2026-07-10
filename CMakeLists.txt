cmake_minimum_required(VERSION 3.20)

project(qt-monitoring-sensors-system VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)

find_package(Qt5 REQUIRED COMPONENTS
    Widgets
    Core
    Gui
)

add_executable(${PROJECT_NAME} WIN32
    src/main.cpp
    src/main_window.cpp
    src/detector_table_model.cpp
    src/detector_data_generator.cpp

    include/detector_data_generator.h
    include/main_window.h
    include/detector_table_model.h
    include/proxy_model/detectors_proxy_model.h
)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
    ${CMAKE_SOURCE_DIR}/include/proxy_model
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt5::Widgets
    Qt5::Core
    Qt5::Gui
)

target_compile_options(${PROJECT_NAME} PRIVATE
    -Wall
    -Wextra
    -pedantic
)