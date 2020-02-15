add_executable(ethploit-test main.cpp)

target_link_libraries(ethploit-test PRIVATE ethereum evm ethashseal devcore Boost::program_options)

target_include_directories(ethploit-test PRIVATE ../utils)

install(TARGETS ethploit-test EXPORT alethTargets DESTINATION bin)
