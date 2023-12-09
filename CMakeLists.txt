cmake_minimum_required(VERSION 3.27)
project(kr)

set(CMAKE_CXX_STANDARD 17)

include_directories(Eigen)

add_executable(kr main.cpp
        Method_MelderaNida.cpp
        Method_MelderaNida.h)
