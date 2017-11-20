cmake_minimum_required(VERSION 2.8)
project(my_cloud)
SET(TARGET my_cloud)

SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -Wall -g -ggdb")
SET(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -m32")
include_directories(
        car_washer_cloud/
)
include_directories(/usr/include/sys)
#link_directories(./lib)

set(SOURCE_FILES
        car_washer_cloud/block_server.c
        )

#add_library(libsrp.a STATIC)

add_executable(${TARGET} ${SOURCE_FILES} )
target_link_libraries(${TARGET} -lpthread )
