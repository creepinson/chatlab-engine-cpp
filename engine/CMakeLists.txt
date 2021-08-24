cmake_minimum_required(VERSION "3.10")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY build)

# set the project name
project(chatlab_engine VERSION 0.0.1 LANGUAGES C CXX)

# add source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

# add the executable
add_library(
    ${PROJECT_NAME}
    ${SOURCES}
)
target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        
)

# Glfw
add_subdirectory(libs/glfw)

# data parser library
add_subdirectory("libs/json")

# imgui
#add_subdirectory("libs/imgui")
find_package(imgui REQUIRED)
#include_directories("libs/imgui")
#link_directories("libs/imgui")


# gl loader
add_subdirectory(libs/glew)

# glm
add_subdirectory("libs/glm")

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
        nlohmann_json::nlohmann_json
        imgui
        glm::glm
        glfw
        libglew_static
    PRIVATE
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
