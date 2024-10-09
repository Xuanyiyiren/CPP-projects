cmake_minimum_required(VERSION 3.10)
project(OpenBLASExample)

find_package(OpenBLAS REQUIRED)

add_executable(OpenBLASExample main.cpp)

if(OpenBLAS_FOUND)
    message("OpenBLAS found.")
    target_link_libraries(OpenBLASExample OpenBLAS::OpenBLAS)
endif()
