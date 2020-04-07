#include <set>

#include "EVMAnalyser.h"

#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "DetectionLogic.cpp"
#endif
#include <iostream>

#define FORERED "\x1B[31m"
#define RESETTEXT "\x1B[0m"
#define OUTPUT std::cout << "[Middleware]: " 

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
        OUTPUT << "The populated instruction has ID number " << executionTraceCount << std::endl; 
        newTuple << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer;
        relDirectCall->insert(newTuple);
        executionTraceCount++;
    } else if (executionTrace->instruction == "DELEGATECALL") {
        souffle::tuple newTupleCall(relDirectCall);
        OUTPUT << "The populated instruction has ID number " << executionTraceCount << std::endl; 
        newTupleCall << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer; // valueTransfer, receiveAddress not needed here
        relDirectCall->insert(newTupleCall);
        executionTraceCount++;
    } else if (executionTrace->instruction == "PUSH") {
        // Reserved for call_result fact
    } else if (executionTrace->instruction == "JUMPI") {
        // Reserved for influence_condition fact
    } else {
        OUTPUT << "No currently exisited relation matches up with this instruction!" 
            << std::endl;
        return false; 
    }

    prog->run(); // for prototype, run everytime receive a new executionTrace

    return true;
}

void EVMAnalyser::callEntry(int gas, std::string contractAddress) {
    // Note that the DELEGATECALL relation has been populated now
    // So Minus 1 to refer back the DELEGATECALL
    souffle::tuple newTuple(relCallEntry); 
    newTuple << executionTraceCount-1 << gas << contractAddress;
    relCallEntry->insert(newTuple);

    OUTPUT << "callEntry for " << executionTraceCount << " has been populated"
        << std::endl;

    prog->run();
}

void EVMAnalyser::callExit(int gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << executionTraceCount-1 << gas; // Minus 1 to refer back the DELEGATECALL
    relCallExit->insert(newTuple); 

    OUTPUT << "callExit for " << executionTraceCount-1 << " has been populated"
        << std::endl;

    prog->run();
}

void EVMAnalyser::extractReentrancyAddresses() {
    
}

bool EVMAnalyser::queryExploit(std::string exploitName) {
    if (souffle::Relation *rel = prog->getRelation(exploitName)) {
        // Re-entrancy 
        if (exploitName == "reentrancy") {
            if (rel->size() != 0) {
                std::set<int> idSet;
                int C;
                std::string A1, A2;
                int P, P2;
                int count = 0;

                for (auto &output : *rel ) {
                    count++;
                    output >> C >> A1 >> A2 >> P >> P2;
                    idSet.insert(C);
                    // std::cout << "[Middleware]: Query Result: " << count << " Re-entrancy from address: " 
                    //     << A1 << " to address: " << A2 << " has been detected with " << P 
                    //     << " and " << P2 << " value trasfered. "
                    //     << std::endl;
                }

                // Assuming there is only one re-entrancy chain
                int totalP = 0;
                for (auto &output : *relDirectCall) {
                    int COriginal;
                    std::string A1Original, A2Original;
                    int POriginal;

                    output >> COriginal >> A1Original >> A2Original >> POriginal;

                    if (idSet.find(COriginal) != idSet.end()) {
                        totalP += POriginal;
                    }

                    if (COriginal == C) { // C is the last identifier
                        OUTPUT << FORERED <<"Query Result: " << " Re-entrancy from address: " 
                            << A1Original << " to address: " << A2Original << " has been detected with " << totalP 
                            << " value trasfered in total." << RESETTEXT
                            << std::endl;         
                    }
                }
                return true;
            } else {
                OUTPUT << "No re-entrancy has been detected." << std::endl;
                return false;
            }
        }
    
        // Locked ethers
        if (exploitName == "locked_ether") {
            if (rel->size() != 0) {
                std::string contractAddress; 
                int id;
                int gas;
                int count = 0;

                for (auto &output : *rel) {
                    count++;
                    output >> id >> gas >> contractAddress;
                    OUTPUT << FORERED << "Query Result: " << count << " Contract in address: " 
                        << contractAddress << " has been locked"  << RESETTEXT << std::endl; 
                }
                return true; 
            } else {
                OUTPUT << "No locked ether has been detected." << std::endl;
                return false; 
            }
        }

        // Unhandled reception
        if (exploitName == "unhandled_reception") {
            if (rel->size() != 0) {
                std::string contractAddress; 
                int id;
                int gas;
                int count = 0;

                for (auto &output : *rel) {
                    count++;
                    output >> id >> gas >> contractAddress;
                    OUTPUT << "Query Result: " << count << " Contract in address: " 
                        << contractAddress << " has been locked" << std::endl; 
                }
                return true; 
            } else {
                OUTPUT << "No locked ether has been detected." << std::endl;
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
