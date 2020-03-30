#include "EVMAnalyser.h"

#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "DetectionLogic.cpp"
#endif
#include <iostream>

EVMAnalyser::EVMAnalyser() {
    executionTraceCount = 1;
    prog = souffle::ProgramFactory::newInstance("DetectionLogic");
    relDirectCall = prog->getRelation("direct_call");
    relCallEntry = prog->getRelation("call_entry");
    relCallExit = prog->getRelation("call_exit");
}

EVMAnalyser::~EVMAnalyser() {
    // An default constructor for testing
}

EVMAnalyser* EVMAnalyser::getInstance() {
    static EVMAnalyser instance;
    return &instance; 
}

bool EVMAnalyser::populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace) {
    if (executionTrace->instruction == "CALL" || 
        executionTrace->instruction == "STATICCALL") { // Treating three types of call as the same for now 
        souffle::tuple newTuple(relDirectCall); // create tuple for the relation
        std::cout << "[Middleware]: The populated instruction has ID number " << executionTraceCount << std::endl; 
        newTuple << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer;
        relDirectCall->insert(newTuple);
        executionTraceCount++;
    } else if (executionTrace->instruction == "DELEGATECALL") {
        souffle::tuple newTupleCall(relDirectCall);
        std::cout << "[Middleware]: The populated instruction has ID number " << executionTraceCount << std::endl; 
        newTupleCall << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer; // valueTransfer, receiveAddress not needed here
        relDirectCall->insert(newTupleCall);
        executionTraceCount++;

        // Maybe also populate a call_entry fact
        // souffle::tuple newTupleCall(relCallEntry);

    } else if (executionTrace->instruction == "CALL_EXIT") {
        // Whether should we use the exectuationTrace datastructure or a separate method to input this relation?
    } else {
        std::cout << "[Middleware]: No currently exisited relation matches up with this instruction!" 
            << std::endl;
        return false; 
    }

    prog->run(); // for prototype, run everytime receive a new executionTrace

    return true;
}

void EVMAnalyser::callEntry(int gas, std::string contractAddress) {
    souffle::tuple newTuple(relCallEntry); 
    newTuple << executionTraceCount << gas << contractAddress;
    relCallEntry->insert(newTuple);

    prog->run();
    // TODO: should increase executionTraceCount here?
    // So executionTraceCount is for detecting re-entrancy exploit in place of the original program counter
    // Maybe not increasing since the beginning of transcation is not an instruction but a flag
}

void EVMAnalyser::callExit(int gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << executionTraceCount << gas;
    relCallExit->insert(newTuple); 

    prog->run();
}

void EVMAnalyser::extractReentrancyAddresses() {
    
}

bool EVMAnalyser::queryExploit(std::string exploitName) {
    if (souffle::Relation *rel = prog->getRelation(exploitName)) {
        // Re-entrancy 
        if (exploitName == "reentrancy") {
            if (rel->size() != 0) {
                int C;
                std::string A1, A2;
                int P, P2;
                int count = 0;

                for (auto &output : *rel ) {
                    count++;
                    output >> C >> A1 >> A2 >> P >> P2;
                    std::cout << "[Middleware]: Query Result: " << count << " Re-entrancy from address: " 
                        << A1 << " to address: " << A2 << " has been detected with " << P 
                        << " and " << P2 << " value trasfered. "
                        << std::endl;
                } 
                return true;
            } else {
                std::cout << "[Middleware]: No re-entrancy has been detected." << std::endl;
                return false;
            }
        }
    
        // Locked ethers
        if (exploitName == "locked_ether") {
            if (rel->size() != 0) {
                std::string A1; 
                int P1;
                int count = 0;

                for (auto &output : *rel) {
                    count++;
                    output >> A1 >> P1;
                    std::cout << "[Middleware]: Query Result: " << count << " Contract in address: " << A1 
                        << " has been locked" << std::endl; 
                }
                return true; 
            } else {
                std::cout << "[Middleware]: No locked ether has been detected." << std::endl;
                return false; 
            }
        }
    }
    
    std::cout << "[Middleware]: Wrong exploit name!" << std::endl;
    return false;
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
