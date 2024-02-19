cmake_minimum_required(VERSION 3.8)

add_executable(example main.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../data/rbf.txt ${CMAKE_CURRENT_BINARY_DIR}/rbf.txt)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/../plot/data_real_plot.py ${CMAKE_CURRENT_BINARY_DIR}/data_real_plot.py)

set_target_properties(
        example PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

target_include_directories(
        example
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/methods_lib
)

target_include_directories(
        example
        PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/../include/Eigen
)

target_link_libraries(example optimization_methods)