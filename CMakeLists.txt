cmake_minimum_required(VERSION 3.10)
project(surge)

file(GLOB_RECURSE SURGE_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)

list(APPEND SURGE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/compat/imguiCompat.cpp")
list(APPEND SURGE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/compat/raylibCoreData.c")

set(module_name "surge")
add_library(${module_name} STATIC ${SURGE_SOURCES})

# RayLib should use static libraries
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build shared libraries" FORCE)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/librapid)

# ImGui

# Get GLFW from raylib
set(GLFW_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/src/external/glfw/include)

set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui)
set(IMGUI_SOURCES
        ${IMGUI_DIR}/imgui.cpp
        ${IMGUI_DIR}/imgui_demo.cpp
        ${IMGUI_DIR}/imgui_draw.cpp
        ${IMGUI_DIR}/imgui_tables.cpp
        ${IMGUI_DIR}/imgui_widgets.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/compat/imgui_impl_raylib.cpp
        # ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp

        ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
        ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        ${IMGUI_DIR}
        ${IMGUI_DIR}/backends
        ${GLFW_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/compat
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/src
)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib)
target_include_directories(raylib PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends
        ${CMAKE_CURRENT_SOURCE_DIR}/compat
        ${CMAKE_CURRENT_SOURCE_DIR}/vendor/raylib/src
)

target_include_directories(${module_name} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(${module_name} PUBLIC librapid raylib imgui)
