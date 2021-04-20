cmake_minimum_required(VERSION 3.19)

project(test)
set(OTHER_LDFLAGS -lz)
set(CMAKE_CXX_STANDARD 20)
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")

add_executable(test main.cpp)

target_include_directories(test PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
