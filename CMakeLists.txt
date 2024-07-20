cmake_minimum_required(VERSION 3.25)

project(Falcon2RU
    DESCRIPTION "Falcon2RU"
    HOMEPAGE_URL "https://github.com/mkoushan/Falcon2RU"
    LANGUAGES CXX
    VERSION 0.1
)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON) # For clangd to know include directories
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src/)
