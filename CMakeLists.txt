cmake_minimum_required(VERSION 3.19)
project(bbb.utils)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(NOT DEFINED C74_MIN_API_DIR)
	set(C74_MIN_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/min-api")
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(source/projects/bbb.utils.shell)
add_subdirectory(source/projects/bbb.utils.osascript)
