cmake_minimum_required(VERSION 3.5)
project(executiontrace-test)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE 1)

set(OBJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/executiontrace-test.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS /vol/project/2019/530/g1953010/.hunter/_Base/c022f0c/af070fb/93b97cb/Install/include)

# creates the executable
add_executable(executiontrace-test ExecutionTraceTest.cpp)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir -p coverage
    COMMAND ${CMAKE_MAKE_PROGRAM} test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -a ${CMAKE_SOURCE_DIR}/libethploittest/*.cpp -o ${OBJECT_DIR}
    | grep -A 5 "ExecutionTraceTest.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/coverage
)
add_dependencies(gcov executiontrace-test)

# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

# Create the gcov-clean target. This cleans the build as well as generated 
# .gcda and .gcno files.
add_custom_target(scrub
COMMAND ${CMAKE_MAKE_PROGRAM} clean
COMMAND rm -f ${OBJECT_DIR}/*.gcno
COMMAND rm -f ${OBJECT_DIR}/*.gcda
WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)

# indicates the include paths
target_include_directories(executiontrace-test PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(
    executiontrace-test
    PUBLIC ethploit
)

# declares a test with our executable
add_test(NAME output_test COMMAND executiontrace-test)
