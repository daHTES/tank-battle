cmake_minimum_required(VERSION 3.13 FATAL_ERROR) 


set(PROJECT_NAME BattleTank)
project(${PROJECT_NAME}) 

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} 
src/main.cpp
src/RenderGraphics/ShaderFunc.cpp
src/RenderGraphics/ShaderFunc.h) 

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)


add_subdirectory(lib/glfw)
target_link_libraries(${PROJECT_NAME} glfw)

add_subdirectory(lib/glad)
target_link_libraries(${PROJECT_NAME} glad)

