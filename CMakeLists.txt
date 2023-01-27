cmake_minimum_required(VERSION 3.25)
project(learning_opengl VERSION 0.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# opengl
find_package(OpenGL REQUIRED)
include(FindOpenGL)

set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/external/glad/")
set(GLFW_SOURCES_DIR "${PROJECT_SOURCE_DIR}/external/glfw/")

# glad
add_subdirectory("${GLAD_SOURCES_DIR}/cmake" glad_cmake)
glad_add_library(glad_gl_core_33 REPRODUCIBLE API gl:core=3.3)

# glfw
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/external/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
        ${GLFW_SOURCES_DIR}/include
        OpenGL::GL
)

target_link_directories(
    ${PROJECT_NAME} PRIVATE 
        ${GLFW_SOURCES_DIR}/src
)

target_link_libraries(
    ${PROJECT_NAME} 
        glfw ${GLFW_LIBRARIES}
        glad_gl_core_33
)
