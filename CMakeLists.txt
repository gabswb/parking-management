cmake_minimum_required(VERSION 3.1)

project(parking-management)

set(SRC_FILES
	src/vehicle.c
	src/utils.c
)

set(HEADER_FILES
	src/vehicle.h
	src/utils.h
	src/global.h
)


#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wconversion -Wcast-align")

set (CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -Wfloat-equal -Wundef -Wconversion -Wcast-align)

add_executable(parking-management src/main.c ${SRC_FILES} ${HEADER_FILES})