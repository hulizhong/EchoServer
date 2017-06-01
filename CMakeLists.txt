
project(echoServer)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_VERBOSE_MAKEFILE on)
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-ggdb3 -O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
#set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
SET(CMAKE_BUILD_TYPE "debug") 

add_subdirectory(server)
add_subdirectory(client)

message(${PROJECT_BINARY_DIR})
message(${PROJECT_SOURCE_DIR})
message("pro cmakelist ", "------------ok")
