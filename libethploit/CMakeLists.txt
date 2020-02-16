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
