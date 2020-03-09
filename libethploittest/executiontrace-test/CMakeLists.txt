project(executiontrace-test)
cmake_minimum_required(VERSION 3.5)
enable_testing()

add_executable(executiontrace-test ExecutionTraceTest.cpp)

target_include_directories(executiontrace-test PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(
    executiontrace-test
    PUBLIC ethploit
)

