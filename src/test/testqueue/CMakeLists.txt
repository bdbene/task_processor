add_executable(testqueue testqueue.cpp main.cpp)

include_directories("${CMAKE_SOURCE_DIR}/queue")

target_link_libraries(testqueue queue libgtest libgmock)

add_test(NAME testqueue COMMAND testqueue)
