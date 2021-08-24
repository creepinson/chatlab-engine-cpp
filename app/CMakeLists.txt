cmake_minimum_required(VERSION 3.10)
project(chatlab_app VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

# add source files
file(GLOB_RECURSE SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} chatlab_engine)
target_link_directories(${PROJECT_NAME} PRIVATE chatlag_engine)
