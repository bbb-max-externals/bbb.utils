cmake_minimum_required(VERSION 3.19)
project(bbb.utils)

set(C74_MIN_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/deps/min-api" CACHE PATH "Path to min-api")

add_subdirectory(source/projects/bbb.utils.shell)
add_subdirectory(source/projects/bbb.utils.osascript)
