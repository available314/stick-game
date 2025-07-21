cmake_minimum_required(VERSION 3.31)
project(untitled)


set(CMAKE_CXX_STANDARD 20)

include_directories(include/)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
        src/*.cpp
)

add_subdirectory(libs/SFML)

add_executable(yandex_group ${SOURCES})
target_link_libraries(yandex_group
        sfml-graphics
        sfml-window
        sfml-system
)