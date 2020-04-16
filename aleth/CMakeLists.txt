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

set(
    sources
    AccountManager.cpp AccountManager.h
    main.cpp
    MinerAux.cpp MinerAux.h
)

add_executable(aleth ${sources})
target_link_libraries(
    aleth 
    PRIVATE ethereum ethashseal evm web3jsonrpc webthree devcore Boost::program_options evmanalyser
)

target_include_directories(aleth PRIVATE ../utils)

if(MINIUPNPC)
    target_compile_definitions(aleth PRIVATE ETH_MINIUPNPC)
endif()

install(TARGETS aleth DESTINATION bin)
