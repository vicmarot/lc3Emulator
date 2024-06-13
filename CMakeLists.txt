cmake_minimum_required(VERSION 3.10)
project(lc3)

set(CMAKE_C_STANDARD 99)

include_directories(include)

add_executable(lc3
    src/main.c
    src/cpu.c
    src/deviceMemory.c
    src/operations.c
    src/utils.c
)
