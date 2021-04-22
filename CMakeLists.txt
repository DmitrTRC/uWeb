cmake_minimum_required(VERSION 3.19)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake
        CACHE STRING "Vcpkg toolchain file")

project(U_SERVER)

add_link_options(-lz)
add_link_options(-lpthread)

set(CMAKE_CXX_STANDARD 20)


add_link_options(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-osx/lib/libuSockets.a)
add_link_options(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-osx/lib/liblibuv.a)
add_link_options(${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/x64-osx/lib/libz.a)


find_path(UWEBSOCKETS_INCLUDE_DIRS "uwebsockets/App.h" ${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/installed/arm64-osx/include)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PRIVATE ${UWEBSOCKETS_INCLUDE_DIRS})
