###############################################################################
## Shared configurations
###############################################################################

cmake_minimum_required(VERSION 3.5)
enable_testing()

add_compile_options(
    -Wno-error=unused-but-set-variable 
    -Wno-error=unused-parameter 
    -Wno-error=unused-variable
    -Wno-error=deprecated-declarations
)

###############################################################################
## Boost test configurations
###############################################################################
add_definitions(-D__EMBEDDED_SOUFFLE__)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-g -O0 -Wall -fprofile-arcs -ftest-coverage")
set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)

# indicates the location of the boost installation tree.
# hard-coded for our simple example.
set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

