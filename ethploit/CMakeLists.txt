add_library(
    ethploit
    Executiontrace.cpp
    Executiontrace.h
)

target_link_libraries(
    ethploit
    evm
    devcore
)