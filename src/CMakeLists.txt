cmake_minimum_required (VERSION 2.6)

project (Tasks)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lpthread -g")

add_subdirectory(main)
add_subdirectory(queue)
add_subdirectory(task)
add_subdirectory(test)

enable_testing()
