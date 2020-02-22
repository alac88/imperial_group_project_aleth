set(BOOST_INCLUDE_DIRS ${BOOST_ROOT}/include)

add_executable(executiontrace-test ExecutionTraceTest.cpp)

target_include_directories(executiontrace-test PRIVATE ${BOOST_INCLUDE_DIRS})

target_link_libraries(
    executiontrace-test
    PUBLIC ethploit
)

