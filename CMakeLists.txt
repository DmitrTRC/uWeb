cmake_minimum_required(VERSION 3.19)
project(test)

set(CMAKE_CXX_STANDARD 20)

add_executable(test main.cpp)

#IF (uwebsockets_FOUND)
#find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
#include_directories(${UWEBSOCKETS_INCLUDE_DIRS})
#target_link_libraries (my_target ${uwebsockets_LIBRARIES})
#    target_include_directories(test PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
#endif()
find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h")
target_include_directories(test PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})

find_library(UWEBSOCKETS_LIBRARY uwebsockets)
link_libraries(test, ${UWEBSOCKETS_LIBRARY})