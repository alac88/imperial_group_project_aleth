cmake_minimum_required(VERSION 3.9)

###############################################################################
## For compiling the evm_analyser alone
###############################################################################
set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

###############################################################################
## Compile libevmanalyser
###############################################################################
include_directories(
    ${CMAKE_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${BOOST_INCLUDE_DIRS}
)
add_definitions(-D__EMBEDDED_SOUFFLE__)
# add_definitions(-DEVMANALYSER_TEST)
add_compile_options(
    -Wno-error=unused-but-set-variable 
    -Wno-error=unused-parameter 
    -Wno-error=unused-variable
    -Wno-error=deprecated-declarations
)
if (APPLE)
    add_compile_options(
        -Wno-error=unknown-warning-option
    )
endif()
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
add_library(evmanalyser 
    STATIC 
    EVMAnalyser.cpp
    EVMAnalyser.h
    type.cpp
    type.h
    JSONLogger.cpp
    JSONLogger.h
)
target_link_libraries(evmanalyser
    ethploit
)

###############################################################################
## Compile libevmanalyser_test
###############################################################################
add_subdirectory(../libethploittest/evmanalyser-test
    ${CMAKE_CURRENT_BINARY_DIR}/../libethploittest/evmanalyser-test
)

###############################################################################
## Compile executiontrace-test
###############################################################################
add_subdirectory(../libethploittest/executiontrace-test
    ${CMAKE_CURRENT_BINARY_DIR}/../libethploittest/executiontrace-test
)

###############################################################################
## Create the gcov target. Run coverage tests with 'make gcov'
###############################################################################
set(OBJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/evmanalyser.dir)
message("-- Object files will be output to: ${OBJECT_DIR}")
add_custom_target(evmanalyser_gcov
    COMMAND mkdir coverage
    COMMAND ../libethploittest/evmanalyser-test/libevmanalyser_test --log_level=all
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_custom_command(TARGET evmanalyser_gcov
    COMMAND echo "=================== GCOV ===================="
    COMMAND gcov -abcfu ${CMAKE_SOURCE_DIR}/libethploit/EVMAnalyser.cpp -o ${OBJECT_DIR}
    | grep -A 5 "EVMAnalyser.cpp" > EVMAnalyserCoverageSummary.tmp
    COMMAND cat EVMAnalyserCoverageSummary.tmp
    COMMAND echo "-- Coverage files have been output to ${CMAKE_CURRENT_BINARY_DIR}/coverage"
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/coverage
)
add_dependencies(evmanalyser_gcov libevmanalyser_test)
# Make sure to clean up the coverage folder
set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES coverage)

###############################################################################
## Create the lcov target. Create html coverage report with 'make lcov'
###############################################################################
add_custom_target(evmanalyser_lcov
    COMMAND lcov -c -d --rc lcov_branch_coverage=1 . -o evmanalyser_coverage.info 
    COMMAND genhtml --rc genhtml_branch_coverage=1 evmanalyser_coverage.info --output-directory out
    WORKING_DIRECTORY ${OBJECT_DIR}
)

###############################################################################
## Create the gcov-clean target. This cleans the build as well as generated 
## .gcda and .gcno files.
###############################################################################
add_custom_target(evmanalyser_scrub
    COMMAND ${CMAKE_MAKE_PROGRAM} clean
    COMMAND rm -f ${OBJECT_DIR}/*.gcno
    COMMAND rm -f ${OBJECT_DIR}/*.gcda
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
)
add_dependencies(evmanalyser_scrub
    libevmanalyser_test_scrub
)


###############################################################################
## The original CMakeLists for libethploit
###############################################################################

add_library(ethploit
    ExecutionTrace.cpp
    ExecutionTrace.h
)
add_compile_options(
    -Wno-error=unused-but-set-variable 
    -Wno-error=unused-parameter 
    -Wno-error=unused-variable
    -Wno-error=deprecated-declarations 
)
target_link_libraries(ethploit
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
    COMMAND ../libethploittest/executiontrace-test/executiontrace-test
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

