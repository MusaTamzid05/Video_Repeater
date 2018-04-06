cmake_minimum_required(VERSION 2.8)

project(testas)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")


file(GLOB SOURCES "src/*cpp")
add_executable(testas ${SOURCES})

include_directories( include )

target_link_libraries(testas vlc )
