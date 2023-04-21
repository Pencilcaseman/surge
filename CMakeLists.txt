cmake_minimum_required(VERSION 3.10)
project(raylib-cpp)

file(GLOB_RECURSE RAYLIB_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        )

set(module_name "raylib-cpp")
add_library(${module_name} STATIC ${RAYLIB_SOURCES})

set(LIBRAPID_NO_WINDOWS_H ON) # RayLib defines some of the same macros as Windows.h, so we need to disable it

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/librapid)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib)
target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raygui/src)
target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${module_name} PUBLIC librapid raylib)
