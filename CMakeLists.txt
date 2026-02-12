cmake_minimum_required(VERSION 4.1)
project(untitled_dawn
        VERSION 0.1.0
        LANGUAGES CXX
)

set(DAWN_ROOT ${CMAKE_SOURCE_DIR}/external/dawn)
set(CMAKE_OSX_ARCHITECTURES arm64)

add_library(dawn STATIC IMPORTED)

set_target_properties(dawn PROPERTIES
        IMPORTED_LOCATION ${DAWN_ROOT}/lib/libwebgpu_dawn.a
        INTERFACE_INCLUDE_DIRECTORIES ${DAWN_ROOT}/include
)

find_library(METAL_FRAMEWORK Metal Required)
find_library(FOUNDATION_FRAMEWORK Foundation REQUIRED)
find_library(QUARTZCORE_FRAMEWORK QuartzCore REQUIRED)

add_executable(untitled_dawn main.cpp)

set_target_properties(untitled_dawn PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
        COMPILE_WARNING_AS_ERROR ON
)

target_link_libraries(untitled_dawn PRIVATE
        dawn
        ${METAL_FRAMEWORK}
        ${FOUNDATION_FRAMEWORK}
        ${QUARTZCORE_FRAMEWORK}
)

if (MSVC)
    target_compile_options(untitled_dawn PRIVATE /W4)
else()
    target_compile_options(untitled_dawn PRIVATE -Wall -Wextra -pedantic)
endif()

if (XCODE)
    set_target_properties(untitled_dawn PROPERTIES
            XCODE_GENERATE_SCHEME ON
            XCODE_SCHEME_ENABLE_GPU_FRAME_CAPTURE_MODE "Metal"
    )
endif()

if (EMSCRIPTEN)
    # Generate a full web page rather than a simple WebAssembly module
    set_target_properties(untitled_dawn PROPERTIES SUFFIX ".html")
endif()





