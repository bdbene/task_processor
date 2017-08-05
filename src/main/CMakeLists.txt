set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories("${CMAKE_SOURCE_DIR}/queue"
					"${CMAKE_SOURCE_DIR}/task"
					"${CMAKE_SOURCE_DIR}/worker")

set(EXTRA_LIBS ${EXTRA_LIBS} queue pthread)

add_executable(Tasks main.cpp sample_task.cpp)

target_link_libraries(Tasks ${EXTRA_LIBS})
