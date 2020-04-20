cmake_minimum_required(VERSION 3.15)
project(perc C)

set(CMAKE_C_STANDARD 99)

add_executable(perc src/main.c src/include/logging.h src/logging.c src/arguments.c src/include/arguments.h src/include/def.h)