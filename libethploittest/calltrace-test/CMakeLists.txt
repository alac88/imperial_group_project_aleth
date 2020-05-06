project(calltrace-test)
cmake_minimum_required(VERSION 3.5)
enable_testing()

add_executable(calltrace-test CallTraceTest.cpp)

target_include_directories(calltrace-test PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(
    calltrace-test
    PUBLIC ethploit
)

