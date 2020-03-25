#include "EVMAnalyser.h"

#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "locked_ether/locked_ether.cpp"
    #include "reentrancy/reentrancy.cpp"
    // #include "DetectionLogic.cpp"
#endif
#include <iostream>

EVMAnalyser::EVMAnalyser() {
    executionTraceCount = 1;
    // TODO: combine two datalog scripts so that there is no need to get multiple instances
    prog = souffle::ProgramFactory::newInstance("reentrancy");
    relDirectCall = prog->getRelation("direct_call");
    relCallEntry = prog->getRelation("call_entry");
    relCallExit = prog->getRelation("call_exit");
}

EVMAnalyser::~EVMAnalyser() {

}

EVMAnalyser* EVMAnalyser::getInstance() {
    static EVMAnalyser instance;
    return &instance; 
}

bool EVMAnalyser::populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace) {
    if (executionTrace->instruction == "CALL" || 
        executionTrace->instruction == "DELEGATECALL" ||
        executionTrace->instruction == "STATICCALL") { // Treating three types of call as the same for now 
        souffle::tuple newTuple(relDirectCall); // create tuple for the relation
        std::cout << "[Middleware]: " << executionTraceCount << std::endl; 
        newTuple << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer;
        relDirectCall->insert(newTuple);
        executionTraceCount++;
    } else if (executionTrace->instruction == "CALL_ENTRY") {
        // TODO: find out what is call_entry
        // Whether should we use the exectuationTrace datastructure or a separate method to input this relation?
    } else if (executionTrace->instruction == "CALL_EXIT") {
        // TODO: find out what is call_exit
        // Whether should we use the exectuationTrace datastructure or a separate method to input this relation?
    } else {
        std::cout << "No currently exisited relation matches up with this instruction!" 
            << std::endl;
        return false; 
    }

    prog->run(); // for prototype, run everytime receive a new executionTrace

    return true;
}

void EVMAnalyser::transactionBegins(int gas, std::string callerAddress) {
    souffle::tuple newTuple(relCallEntry); 
    newTuple << gas << callerAddress;
    relCallEntry->insert(newTuple);
    //TODO: should increase executionTraceCount here?
}

void EVMAnalyser::transactionEnds(int gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << gas;
    relCallExit->insert(newTuple); 
    //TODP: should increase exectutionTraceCount here?
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
                    std::cout << "Query Result: " << count << " Re-entrancy from address: " 
                        << A1 << " to address: " << A2 << " has been detected with " << P 
                        << " and " << P2 << " value trasfered. "
                        << std::endl;
                } 
                return true;
            } else {
                std::cout << "No re-entrancy has been detected." << std::endl;
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
                    std::cout << "Query Result: " << count << " Ether of Address: " << A1 
                        << " have been locked" << std::endl; 
                }
                return true; 
            } else {
                std::cout << "No re-entrancy has been detected." << std::endl;
                return false; 
            }
        }
    }
    
    std::cout << "Wrong exploit name!" << std::endl;
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
