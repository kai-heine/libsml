cmake_minimum_required(VERSION 3.0)
project(libsml C)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to Release as none was specified.")
    set(CMAKE_BUILD_TYPE "Release")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

add_subdirectory(sml)

enable_testing()
add_subdirectory(test)

add_subdirectory(examples)