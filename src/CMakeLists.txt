cmake_minimum_required(VERSION 3.8)


file(GLOB SRCS *.cpp)

add_library(
        optimization_methods
        STATIC
        ${SRCS}
)

target_include_directories(
        optimization_methods
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Eigen)

target_include_directories(
        optimization_methods
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/methods_lib
)

set_target_properties(
        optimization_methods PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

