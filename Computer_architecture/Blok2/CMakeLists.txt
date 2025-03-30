cmake_minimum_required(VERSION 3.30)
project(Blok2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Blok2 main.c)

target_link_libraries(Blok2 winmm)