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
	
#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "-ggdb3")

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wconversion -Wcast-align")

#set (CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -Wfloat-equal -Wundef -Wconversion -Wcast-align -ggdb3)

add_executable(parking-management src/main.c ${SRC_FILES} ${HEADER_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(parking-management PRIVATE Threads::Threads)