cmake_minimum_required(VERSION 3.30)
project(Blok3 C)

set(CMAKE_C_STANDARD 11)

add_executable(Blok3 main.c)

target_link_libraries(Blok3 ws2_32)
