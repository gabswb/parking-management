cmake_minimum_required(VERSION 3.1)

project(parking-management)

set(SRC_FILES
	src/vehicle.c
	src/utils.c
	src/clock.c
)

set(HEADER_FILES
	src/vehicle.h
	src/utils.h
	src/global.h
	src/clock.h
)
	
#set(CMAKE_BUILD_TYPE Debug)

#set(CMAKE_CXX_FLAGS "-ggdb3")

#set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wfloat-equal -Wundef -Wconversion -Wcast-align")

#set (CMAKE_CXX_STANDARD 11)

#cmake -DCMAKE_BUILD_TYPE=Release ..

set(CMAKE_CXX_FLAGS_DEBUG_INIT "-Wall -Wextra -Wfloat-equal -Wundef -g")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-Wall -Wextra -Wfloat-equal -Wundef")

#add_compile_options(-Wall -Wextra -Wfloat-equal -Wundef -ggdb3)

add_executable(parking-management src/main.c ${SRC_FILES} ${HEADER_FILES})

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
target_link_libraries(parking-management PRIVATE Threads::Threads)	