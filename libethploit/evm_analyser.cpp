#include "evm_analyser.h"

#include "locked_ether/locked_ether.cpp"
#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "reentrancy/reentrancy.cpp"
#endif
#include <iostream>

Evm_analyser::Evm_analyser() {
    execution_trace_count = 1;
    prog = souffle::ProgramFactory::newInstance("reentrancy");
    rel_direct_call = prog->getRelation("direct_call");
}

Evm_analyser::~Evm_analyser() {

}

Evm_analyser* Evm_analyser::get_instance() {
    static Evm_analyser instance;
    return &instance; 
}

bool Evm_analyser::populate_execution_trace(dev::eth::ExecutionTrace* execution_trace) {
    if (execution_trace->instruction == "CALL") {
        souffle::tuple newTuple(rel_direct_call); // create tuple for the relation
        std::cout << "[Middleware]: " << execution_trace_count << std::endl; 
        newTuple << execution_trace_count
                << execution_trace->senderAddress
                << execution_trace->receiveAddress
                << (int) execution_trace->valueTransfer;
        rel_direct_call->insert(newTuple);
        execution_trace_count++;
    } else {
        std::cout << "No currently exisited relation matches up with this instruction!" << std::endl;
        return false; 
    }

    prog->run(); // for prototype, run everytime receive a new execution_trace

    return true;
}

bool Evm_analyser::query_expoilt(std::string exploit_name) {
    if (souffle::Relation *rel = prog->getRelation(exploit_name)) {
        if (rel->size() != 0) {
            // if (exploit_name == "reentrancy") {
                int C;
                std::string A1, A2;
                int P, P2;

                for(auto &output : *rel ) {
                    output >> C >> A1 >> A2 >> P >> P2;
                    std::cout << "Re-entrancy from address: " << A1 << " to address: " << A2 
                        << " has been detected with " << P << " and " << P2 << " value trasfered. "
                        << std::endl;
                } 
                return true;
            // }
        } else {
            std::cout << "No re-entrancy has been detected." << std::endl;
            return false;
        }
    } else {
        std::cout << "Wrong exploit_name!" << std::endl;
        return false;
    }
}

void Evm_analyser::clean_execution_trace() {
    prog->purgeInputRelations();
    prog->purgeInternalRelations(); // Remenber to clean the internal relations e.g. call in the re-entrancy
    prog->purgeOutputRelations();

    execution_trace_count = 1;
}

Evm_analyser_test* Evm_analyser_test::get_instance() {
    return (Evm_analyser_test *) Evm_analyser::get_instance(); 
}

int Evm_analyser_test::get_relation_size(std::string relation_name) {
    return prog->getRelationSize(relation_name);
}