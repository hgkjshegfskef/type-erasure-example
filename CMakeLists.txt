cmake_minimum_required(VERSION 3.20) # whatever
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(type_erasure LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "-Wall -Wextra")

if(CMAKE_GENERATOR MATCHES "Ninja")
    add_compile_options(-fdiagnostics-color=always)
endif()

add_subdirectory(src)
