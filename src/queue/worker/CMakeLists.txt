include_directories("${CMAKE_SOURCE_DIR}/task")
include_directories("${CMAKE_SOURCE_DIR}/queue")

add_library(worker STATIC worker.cpp)
