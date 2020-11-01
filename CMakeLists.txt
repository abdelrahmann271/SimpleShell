cmake_minimum_required(VERSION 3.17)
project(SimpleShell C)

set(CMAKE_C_STANDARD 11)

add_executable(SimpleShell main.c CodeExamples.c takingInput.c)