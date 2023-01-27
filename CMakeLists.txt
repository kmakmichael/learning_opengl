cmake_minimum_required(VERSION 3.25)
project(learning_opengl VERSION 0.0)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(
    ${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}
    ${PROJECT_NAME} PUBLIC {CMAKE_CURRENT_SOURCE_DIR}/glfw/include
    )

target_link_directories(
    ${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/glfw/src
    )

target_link_libraries(${PROJECT_NAME} glfw ${GLFW_LIBRARIES})
