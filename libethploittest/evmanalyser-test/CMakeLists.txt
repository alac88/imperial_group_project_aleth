cmake_minimum_required(VERSION 3.5)
project(libevmanalyser_test)
enable_testing()

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

# creates the executable
add_executable(libevmanalyser_test 
    EVMAnalyserTest.cpp
)

# indicates the include paths
target_include_directories(libevmanalyser_test 
  PRIVATE 
    ${BOOST_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../libethploit
)

target_link_libraries(libevmanalyser_test
    PUBLIC 
    evmanalyser
)

###############################################################################	
## Create the gcov-clean target. This cleans the build as well as generated 	
## .gcda and .gcno files.	
###############################################################################	
set(OBJECT_DIR ${CMAKE_CURRENT_BINARY_DIR}/CMakeFiles/libevmanalyser_test.dir)	
add_custom_target(libevmanalyser_test_scrub	
    COMMAND ${CMAKE_MAKE_PROGRAM} clean	
    COMMAND rm -f ${OBJECT_DIR}/*.gcno	
    COMMAND rm -f ${OBJECT_DIR}/*.gcda	
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}	
) 