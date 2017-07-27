set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

include_directories("${CMAKE_SOURCE_DIR}/queue"
					"${CMAKE_SOURCE_DIR}/task")

set(EXTRA_LIBS ${EXTRA_LIBS} queue)

add_executable(Tasks main.cpp)

target_link_libraries(Tasks ${EXTRA_LIBS})
