# sequence (clean up coverage folder -> compile -> execute test -> run coverage test -> generate coverage report):
# make 
# ./executiontrace-test
# make gcov
# make lcov

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
set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

# creates the executable
add_executable(executiontrace-test ExecutionTraceTest.cpp)

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir coverage
    COMMAND ./executiontrace-test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -abcfu ${CMAKE_SOURCE_DIR}/libethploittest/ExecutionTraceTest.cpp -o ${OBJECT_DIR}
    | grep -A 5 "ExecutionTraceTest.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/coverage
)
add_dependencies(gcov executiontrace-test)

# Create the lcov target. Create html coverage report with 'make lcov'
add_custom_target(lcov
    COMMAND lcov -c -d . -o coverage.info
    COMMAND lcov --remove coverage.info '/usr/include/*' ${BOOST_INCLUDE_DIRS}'/*' ${CMAKE_SOURCE_DIR}'/libdevcore/*' ${CMAKE_SOURCE_DIR}'/libethcore/*' -o coverage_filtered.info
    COMMAND genhtml coverage_filtered.info --output-directory out
    WORKING_DIRECTORY ${OBJECT_DIR}
)

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
