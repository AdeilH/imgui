add_library(imgui_lib
        imgui.cpp
        imgui_demo.cpp
        imgui_draw.cpp
        imgui_tables.cpp
        imgui_widgets.cpp
)
target_include_directories(imgui_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

option(IMGUI_BUILD_ALLEGRO5_BACKEND "Build the Dear ImGui Allegro 5 backend" ON)
option(IMGUI_BUILD_GLFW3_BACKEND "Build the Dear ImGui GLFW 3 and OpenGL 3 backends" ON)

if(IMGUI_BUILD_ALLEGRO5_BACKEND AND SABAAT_IMGUI_BACKEND STREQUAL "ALLEGRO5")
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALLEGRO REQUIRED IMPORTED_TARGET allegro-5 allegro_primitives-5)

    add_library(imgui_allegro5 backends/imgui_impl_allegro5.cpp)
    target_include_directories(imgui_allegro5 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backends)
    target_link_libraries(imgui_allegro5 PUBLIC imgui_lib PkgConfig::ALLEGRO)
endif()

if(IMGUI_BUILD_GLFW3_BACKEND AND SABAAT_IMGUI_BACKEND STREQUAL "GLFW3")
    find_package(glfw3 REQUIRED)
    find_package(OpenGL REQUIRED)

    add_library(imgui_glfw3
            backends/imgui_impl_glfw.cpp
            backends/imgui_impl_opengl3.cpp
    )
    target_include_directories(imgui_glfw3 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/backends)
    target_link_libraries(imgui_glfw3 PUBLIC imgui_lib glfw OpenGL::GL)
endif()