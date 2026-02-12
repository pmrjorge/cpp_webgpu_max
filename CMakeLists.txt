cmake_minimum_required(VERSION 4.1)
project(untitled_dawn)

set(CMAKE_CXX_STANDARD 20)

set(DAWN_ROOT ${CMAKE_SOURCE_DIR}/external/dawn)
set(CMAKE_OSX_ARCHITECTURES arm64)

find_library(METAL_FRAMEWORK Metal Required)
find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)
find_library(QUARTZCORE_FRAMEWORK QuartzCore REQUIRED)

add_executable(untitled_dawn main.cpp)

add_library(dawn STATIC IMPORTED)

set_target_properties(dawn PROPERTIES
        IMPORTED_LOCATION ${DAWN_ROOT}/lib/libwebgpu_dawn.a
        INTERFACE_INCLUDE_DIRECTORIES ${DAWN_ROOT}/include
)

target_link_libraries(untitled_dawn PRIVATE
        dawn
        ${METAL_FRAMEWORK}
        ${FOUNDATION_FRAMEWORK}
        ${QUARTZCORE_FRAMEWORK}
)

