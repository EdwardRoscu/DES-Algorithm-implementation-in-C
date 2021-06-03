cmake_minimum_required(VERSION 3.19)
project(DES_Algorithm_implementation_in_C C)

set(CMAKE_C_STANDARD 11)

add_subdirectory(src/lib)

add_executable(main src/main.c)

target_link_libraries(main DES)
target_link_libraries(main display)

target_link_libraries(DES convert)
