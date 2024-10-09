cmake_minimum_required(VERSION 3.10)

# add_definitions(-DWITH_NEON) # If you are arm based, please use this line.

add_definitions(-DWITH_AVX2) # If you are x86 based, please use this tow lines.
add_definitions(-mavx2)

set(TARGET_NAME mat_mul)
set(CMAKE_CXX_STANDARD 11)
project(${TARGET_NAME})

aux_source_directory(. SRC_LIST)
add_executable(${TARGET_NAME} ${SRC_LIST})

find_package(OpenMP)
if(OpenMP_CXX_FOUND)
    message("OpenMP found.")
    target_link_libraries(${TARGET_NAME} PUBLIC OpenMP::OpenMP_CXX)
endif()

