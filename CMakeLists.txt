cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp)
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
target_include_directories(test PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})