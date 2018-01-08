add_executable(testtask testtask.cpp concrete_task.cpp main.cpp)

include_directories("${CMAKE_SOURCE_DIR}/task")

target_link_libraries(testtask task libgtest libgmock)

add_test(NAME testtask COMMAND testtask)
