cmake_minimum_required(VERSION 3.20)
project(CppProgrammingLab3 VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_library(container_vector INTERFACE)
target_include_directories(container_vector INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)


add_executable(CppProgrammingLab3 src/main.cpp)
target_link_libraries(CppProgrammingLab3 PRIVATE container_vector)

enable_testing()
add_subdirectory(tests)
