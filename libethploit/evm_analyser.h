#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>

class Evm_analyser {
    int execution_trace_count;
    Evm_analyser();
    ~Evm_analyser(); 
  protected:
    souffle::SouffleProgram *prog;
    souffle::Relation *rel_direct_call;
    souffle::Relation *que_reentrancy;
  public:
    static Evm_analyser* get_instance();

    bool populate_execution_trace(dev::eth::ExecutionTrace* execution_trace);

    bool query_expoilt(std::string exploit_name);

    void clean_execution_trace();
};

/**
 * Extending Evm_analyser for testing
 */ 
class Evm_analyser_test : public Evm_analyser {
  public:
    Evm_analyser_test();

    static Evm_analyser_test* get_instance();
    
    int get_relation_size(std::string relation_name);
};

