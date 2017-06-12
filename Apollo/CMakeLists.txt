cmake_minimum_required(VERSION 2.8)
project(Apollo)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -g")
#set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
#set(LIBRARY_OUTPUT_DIR ${CMAKE_BINARY_DIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include_directories(${CMAKE_SOURCE_DIR}/include)

add_subdirectory(test)
add_subdirectory(utils)
#add_subdirectory(basic)
