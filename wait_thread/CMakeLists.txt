cmake_minimum_required(VERSION 3.5)
project(wait_thread C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-Wall -Wextra -Wfloat-equal -Wshadow -Wold-style-cast -Wsign-conversion")

set(CMAKE_EXE_LINKER_FLAGS "-pthread")
add_executable(wait_thread main.c)