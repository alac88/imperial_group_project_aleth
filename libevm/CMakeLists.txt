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

set(sources
    EVMC.cpp EVMC.h
    ExtVMFace.cpp ExtVMFace.h
    Instruction.cpp Instruction.h
    LegacyVM.cpp LegacyVM.h
    LegacyVMConfig.h
    LegacyVMCalls.cpp
    LegacyVMOpt.cpp
    VMFace.h
    VMFactory.cpp VMFactory.h
)

add_library(evm ${sources})

target_link_libraries(
    evm
    PUBLIC ethcore devcore evmc::evmc ethploit evmanalyser
    PRIVATE aleth-interpreter aleth-buildinfo jsoncpp_lib_static Boost::program_options evmc::loader
)

if(EVM_OPTIMIZE)
    target_compile_definitions(evm PRIVATE EVM_OPTIMIZE)
endif()
