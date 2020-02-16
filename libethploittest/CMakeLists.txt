cmake_minimum_required(VERSION 2.8.7)
project(my_first_test)
enable_testing()

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS /vol/project/2019/530/g1953010/.hunter/_Base/c022f0c/af070fb/93b97cb/Install/include)

# creates the executable
add_executable(test_executable ExecutionTraceTest.cpp)
# indicates the include paths
target_include_directories(test_executable PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(
    test_executable
    PUBLIC ethploit
)

# declares a test with our executable
add_test(NAME test1 COMMAND test_executable)