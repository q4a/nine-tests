project(NineTests)

option(USE_PANFORK "Use panfork" OFF)

if (USE_PANFORK)
    add_definitions(-DD3DADAPTERPATH="/home/q/panfork-rel/lib/arm-linux-gnueabihf/d3d/d3dadapter9.so")
else()
    add_definitions(-DD3DADAPTERPATH='"/home/q/mesa-rel/lib/arm-linux-gnueabihf/d3d/d3dadapter9.so"')
endif()
add_definitions(-DD3DADAPTER9_WITHDRI2=0)


set(SRC_FILES
    "../Xnine.c"
    "../dri3.c"
    "NineTests.c"
)

add_executable(${PROJECT_NAME} ${SRC_FILES})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/..
    ${CMAKE_SOURCE_DIR}/../include
    ${CMAKE_SOURCE_DIR}/../include/D3D9
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    X11
    Xext
    xcb
    xcb-present
    xcb-dri3
    xcb-xfixes
    X11-xcb
)
