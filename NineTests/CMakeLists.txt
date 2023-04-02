cmake_minimum_required(VERSION 3.5)
project(NineTests)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "" FORCE)
endif()

### Set up output paths
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/bin)

if (WIN32)
    message("Using Windows D3D9 API")
    if (NOT D3D9_INCLUDE_DIR)
        set(D3D9_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/extern/directx/include")
        set(D3D9_LIBRARY "${PROJECT_SOURCE_DIR}/extern/directx/lib/d3d9.lib")
    endif()
endif()

set(SRC_FILES
    "NineTests.c"
    "NineTests.h"
    "visual.h"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${D3D9_LIBRARY}
)
