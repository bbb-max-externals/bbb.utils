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

set(HELP_SOURCE "${CMAKE_CURRENT_SOURCE_DIR}/${PROJECT_NAME}.maxhelp")
set(HELP_DEST "${CMAKE_CURRENT_SOURCE_DIR}/../../../help/${PROJECT_NAME}.maxhelp")
if(EXISTS "${HELP_SOURCE}")
	add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different "${HELP_SOURCE}" "${HELP_DEST}"
	)
endif()

include(${C74_MIN_API_DIR}/script/min-posttarget.cmake)
