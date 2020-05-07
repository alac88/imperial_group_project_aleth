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
