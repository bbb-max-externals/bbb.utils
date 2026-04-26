cmake_minimum_required(VERSION 3.19)

if(NOT DEFINED C74_MIN_API_DIR)
	set(C74_MIN_API_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../../deps/min-api")
endif()

include(${C74_MIN_API_DIR}/script/min-pretarget.cmake)

include_directories("${C74_INCLUDES}")
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/../../")

set(SOURCE_FILES
	${PROJECT_NAME}.cpp
)

add_library(${PROJECT_NAME} MODULE ${SOURCE_FILES})

include(${C74_MIN_API_DIR}/script/min-posttarget.cmake)
