cmake_minimum_required(VERSION 3.0)
project(libsml C)

include(CMakeDependentOption)

cmake_dependent_option(
	SML_WITHOUT_TRANSPORT "Disable the SML transport layer functionality (POSIX only)" OFF
	"NOT WIN32" ON
)

if(NOT CMAKE_BUILD_TYPE)
    message(STATUS "Setting build type to Release as none was specified.")
    set(CMAKE_BUILD_TYPE "Release" CACHE STRING "The build type (Debug/Release)")
endif()

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules")

add_subdirectory(sml)

if(NOT WIN32)
	enable_testing()
	add_subdirectory(test)
endif()

if(NOT SML_WITHOUT_TRANSPORT)
    add_subdirectory(examples)
endif()