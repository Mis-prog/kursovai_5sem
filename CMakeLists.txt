cmake_minimum_required(VERSION 3.8)

project(kr
        VERSION 0.0.2
        LANGUAGES CXX
)

add_subdirectory(src)

add_subdirectory(example)

add_subdirectory(googletest)

add_subdirectory(test)