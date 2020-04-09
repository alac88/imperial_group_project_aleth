#include <set>
#include <queue>

#include "EVMAnalyser.h"
#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "DetectionLogic.cpp"
#endif
#include <iostream>

// Output related marcros
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

}

void EVMAnalyser::callExit(int gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << executionTraceCount-1 << gas; // Minus 1 to refer back the DELEGATECALL
    relCallExit->insert(newTuple); 

    OUTPUT << "callExit for " << executionTraceCount-1 << " has been populated"
        << std::endl;

}

void EVMAnalyser::instruction(std::string opcode, int nArgs, int nRet) {};

void EVMAnalyser::callResult(int result) {};

void EVMAnalyser::swap(int index) {}; // SWAP2 = swap the first(0) and the third(2) element

void EVMAnalyser::dup(int position) {}; // DUP2 = dup second(1) element on the stack

void EVMAnalyser::jumpi(int condition) {};

void EVMAnalyser::extractReentrancyAddresses() {
    souffle::Relation *rel = prog->getRelation("reentrancy");

    std::set<int> idSet;
    int count = 0;
    for (auto &output : *rel ) {
        int id;
        std::string senderAddr, receiverAddr;
        int ether1, ether2;

        count++;
        output >> id >> senderAddr >> receiverAddr >> ether1 >> ether2;
        idSet.insert(id);
    }

    int totalEther = 0;
    unsigned long i = 0;
    std::queue<std::string> chain;
    std::string receiverAddrPre = "Null";
    for (auto &output : *relDirectCall) {
        int idOriginal;
        std::string senderAddrOriginal, receiverAddrOriginal;
        int etherOriginal;

        output >> idOriginal >> senderAddrOriginal >> receiverAddrOriginal >> etherOriginal;

        if (idSet.find(idOriginal) != idSet.end()) {
            i++;
            chain.push(senderAddrOriginal);
            totalEther += etherOriginal;

            if ((senderAddrOriginal != receiverAddrPre && receiverAddrPre != "Null") || i == idSet.size()) {
                // Output the address chain
                if (senderAddrOriginal != receiverAddrPre) {
                    chain.pop();
                    totalEther -= etherOriginal;
                }

                OUTPUT << FORERED <<"Query Result: " << " Re-entrancy: ";

                std::string addrStart = chain.front();
                std::cout << addrStart;
                chain.pop();
                while (!chain.empty()) {
                    std::cout << " => " << chain.front();
                    chain.pop();
                }
                std::cout << " => " << addrStart << " has been detected with " << totalEther 
                    << " value trasfered in total." << RESETTEXT
                    << std::endl;

                // Reset
                if (senderAddrOriginal != receiverAddrPre) {
                    chain.push(senderAddrOriginal);
                    totalEther = etherOriginal;
                } else {
                    totalEther = 0;
                }
            }
        }

        receiverAddrPre = receiverAddrOriginal;
    }    
}

bool EVMAnalyser::queryExploit(std::string exploitName) {
    prog->run();

    if (souffle::Relation *rel = prog->getRelation(exploitName)) {
        // Re-entrancy 
        if (exploitName == "reentrancy") {
            if (rel->size() != 0) {
                extractReentrancyAddresses();
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
