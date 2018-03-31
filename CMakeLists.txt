cmake_minimum_required(VERSION 3.9)
project(Malloc)

set(CMAKE_CXX_STANDARD 11)
add_executable(Malloc memgrind.c mymalloc.c)