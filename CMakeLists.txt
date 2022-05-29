cmake_minimum_required(VERSION 3.0)

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

add_compile_options(-Wall -Wextra)

add_executable(parking-management src/main.c ${SRC_FILES} ${HEADER_FILES})