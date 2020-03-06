#include "EVMAnalyser.h"

#include "locked_ether/locked_ether.cpp"
#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "reentrancy/reentrancy.cpp"
#endif
#include <iostream>

EVMAnalyser::EVMAnalyser() {
    executionTraceCount = 1;
    prog = souffle::ProgramFactory::newInstance("reentrancy");
    relDirectCall = prog->getRelation("direct_call");
}

EVMAnalyser::~EVMAnalyser() {

}

EVMAnalyser* EVMAnalyser::getInstance() {
    static EVMAnalyser instance;
    return &instance; 
}

bool EVMAnalyser::populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace) {
    if (executionTrace->instruction == "CALL") {
        souffle::tuple newTuple(relDirectCall); // create tuple for the relation
        std::cout << "[Middleware]: " << executionTraceCount << std::endl; 
        newTuple << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer;
        relDirectCall->insert(newTuple);
        executionTraceCount++;
    } else {
        std::cout << "No currently exisited relation matches up with this instruction!" << std::endl;
        return false; 
    }

    prog->run(); // for prototype, run everytime receive a new executionTrace

    return true;
}

bool EVMAnalyser::queryExpoilt(std::string exploitName) {
    if (souffle::Relation *rel = prog->getRelation(exploitName)) {
        if (rel->size() != 0) {
            // if (exploitName == "reentrancy") {
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
        std::cout << "Wrong exploitName!" << std::endl;
        return false;
    }
}

void EVMAnalyser::cleanExecutionTrace() {
    prog->purgeInputRelations();
    prog->purgeInternalRelations(); // Remenber to clean the internal relations e.g. call in the re-entrancy
    prog->purgeOutputRelations();

    executionTraceCount = 1;
}

EVMAnalyserTest* EVMAnalyserTest::getInstance() {
    return (EVMAnalyserTest *) EVMAnalyser::getInstance(); 
}

int EVMAnalyserTest::getRelationSize(std::string relationName) {
    return prog->getRelationSize(relationName);
}