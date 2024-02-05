cmake_minimum_required(VERSION 3.8)

add_executable(example main.cpp)

set_target_properties(
        example PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(
        optimization_methods
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/methods_lib
)

target_link_libraries(example optimization_methods)