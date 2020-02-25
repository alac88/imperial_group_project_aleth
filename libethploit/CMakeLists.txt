add_library(
    ethploit
    ExecutionTrace.cpp
    ExecutionTrace.h
)

target_link_libraries(
    ethploit
    evm
    devcore
)

# sequence (clean up coverage folder -> run coverage test -> generate coverage report):
# make scrub (if this is not the first run of gcov)
# make gcov
# make lcov

set(OBJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/ethploit.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")

# Create the gcov target. Run coverage tests with 'make gcov'
add_custom_target(gcov
    COMMAND mkdir coverage
    COMMAND ../libethploittest/executiontrace-test
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(TARGET gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -abcfu ${CMAKE_SOURCE_DIR}/libethploit/ExecutionTrace.cpp -o ${OBJECT_DIR}
    | grep -A 5 "ExecutionTrace.cpp" > CoverageSummary.tmp
    COMMAND cat CoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/coverage
)
add_dependencies(gcov executiontrace-test)

# Create the lcov target. Create html coverage report with 'make lcov'
add_custom_target(lcov
    COMMAND lcov -c -d . -o coverage.info --rc lcov_branch_coverage=1
    COMMAND genhtml coverage.info --branch-coverage --output-directory out 
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

