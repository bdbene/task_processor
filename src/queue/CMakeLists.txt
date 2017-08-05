include_directories("${CMAKE_SOURCE_DIR}/task")
include_directories("${CMAKE_SOURCE_DIR}/queue/worker")

add_library(queue STATIC queue.cpp)

add_subdirectory(worker)

target_link_libraries(queue worker)
