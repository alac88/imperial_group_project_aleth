#include <set>
#include <queue>
#include <fstream>
#include <json/json.h>

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

void EVMAnalyser::initialiseJSON() {
    // New JSON tuples default to be appended to the current files.
    reentrancyJSON.open("reentrancy.json", std::ios::app);
    lockedEtherJSON.open("locked_ether.json", std::ios::app);
}

void EVMAnalyser::setTransactionHash(std::string _transactionHash) {
    transactionHash = _transactionHash;
}

void EVMAnalyser::setAccount(std::string _account) {
    account = _account;
}

EVMAnalyser* EVMAnalyser::getInstance(std::string _account, std::string _transactionHash) {
    static EVMAnalyser instance;
    if (_transactionHash != "UNDEFINED") {
        instance.setTransactionHash(_transactionHash);
    }
    if (_account != "UNDEFINED") {
        instance.setAccount(_account);
    }
    instance.initialiseJSON();
    return &instance; 
}

bool EVMAnalyser::populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace) {
    if (executionTrace->instruction == "CALL" || 
        executionTrace->instruction == "STATICCALL") { // Treating three types of call as the same for now 
        souffle::tuple newTuple(relDirectCall); // create tuple for the relation
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "The populated instruction has ID number " << executionTraceCount << std::endl;
#endif
        newTuple << executionTraceCount
                << executionTrace->senderAddress
                << executionTrace->receiveAddress
                << (int) executionTrace->valueTransfer;
        relDirectCall->insert(newTuple);
        executionTraceCount++;
    } else if (executionTrace->instruction == "DELEGATECALL") {
        souffle::tuple newTupleCall(relDirectCall);
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "The populated instruction has ID number " << executionTraceCount << std::endl; 
#endif
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
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "No currently exisited relation matches up with this instruction!" 
            << std::endl;
#endif
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

#ifdef EVMANALYSER_DEBUG
    OUTPUT << "callEntry for " << executionTraceCount << " has been populated"
        << std::endl;
#endif

}

void EVMAnalyser::callExit(int gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << executionTraceCount-1 << gas; // Minus 1 to refer back the DELEGATECALL
    relCallExit->insert(newTuple); 

#ifdef EVMANALYSER_DEBUG
    OUTPUT << "callExit for " << executionTraceCount-1 << " has been populated"
        << std::endl;
#endif

}

void EVMAnalyser::extractReentrancyAddresses() {
    souffle::Relation *rel = prog->getRelation("reentrancy");
    Json::Value json(Json::objectValue);

    // Standard json fields
    json["account"] = account;
    json["transaction_hash"] = transactionHash;

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

#ifdef EVMANALYSER_DEBUG
                OUTPUT << FORERED <<"Query Result: " << " Re-entrancy: ";
#endif

                std::string reentrancyChain = chain.front();
                std::string addrStart = chain.front();
#ifdef EVMANALYSER_DEBUG
                std::cout << addrStart;
#endif                
                chain.pop();
                while (!chain.empty()) {
#ifdef EVMANALYSER_DEBUG
                    std::cout << " => " << chain.front();
#endif              
                    reentrancyChain += " => " + chain.front();
                    chain.pop();
                }
#ifdef EVMANALYSER_DEBUG        
                std::cout << " => " << addrStart << " has been detected with " << totalEther 
                    << " value trasfered in total." << RESETTEXT
                    << std::endl;
#endif
                reentrancyChain += " => " + addrStart;
                json["reentrancy_chain"] = reentrancyChain;
                json["total_ether"] = totalEther;

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

    // Save the new json tuple
    reentrancyJSON << json << std::endl;
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
#ifdef EVMANALYSER_DEBUG
                OUTPUT << "No re-entrancy has been detected." << std::endl;
#endif
                return false;
            }
        }
    
        // Locked ethers
        if (exploitName == "locked_ether") {
            if (rel->size() != 0) {
                int count = 0;

                for (auto &output : *rel) {
                    std::string contractAddress; 
                    int id;
                    int gas;

                    count++;
                    output >> id >> gas >> contractAddress;
#ifdef EVMANALYSER_DEBUG
                    OUTPUT << FORERED << "Query Result: " << count << " Contract in address: " 
                        << contractAddress << " has been locked"  << RESETTEXT << std::endl; 
#endif
                    Json::Value json(Json::objectValue);
                    json["account"] = account;
                    json["transaction_hash"] = transactionHash;
                    json["contract_address"] = contractAddress;
                    lockedEtherJSON << json << std::endl;
                }
                return true; 
            } else {
#ifdef EVMANALYSER_DEBUG
                OUTPUT << "No locked ether has been detected." << std::endl;
#endif
                return false; 
            }
        }

        // Unhandled reception
        if (exploitName == "unhandled_reception") {
            if (rel->size() != 0) {
                int count = 0;

                for (auto &output : *rel) {
                    std::string contractAddress; 
                    int id;
                    int gas;

                    count++;
                    output >> id >> gas >> contractAddress;
#ifdef EVMANALYSER_DEBUG
                    OUTPUT << "Query Result: " << count << " Contract in address: " 
                        << contractAddress << " has been locked" << std::endl; 
#endif
                }
                return true; 
            } else {
#ifdef EVMANALYSER_DEBUG
                OUTPUT << "No locked ether has been detected." << std::endl;
#endif
                return false; 
            }
        }
    }

#ifdef EVMANALYSER_DEBUG
    OUTPUT << "Wrong exploit name!" << std::endl;
#endif
    return false;
}

void EVMAnalyser::cleanExecutionTrace() {
    prog->purgeInputRelations();
    prog->purgeInternalRelations(); // Remenber to clean the internal relations e.g. call in the re-entrancy
    prog->purgeOutputRelations();

    reentrancyJSON.close();
    lockedEtherJSON.close();

    executionTraceCount = 1;
}

EVMAnalyserTest* EVMAnalyserTest::getInstance(std::string _account, std::string _transactionHash) {
    return (EVMAnalyserTest *) EVMAnalyser::getInstance(_account, _transactionHash); 
}

int EVMAnalyserTest::getRelationSize(std::string relationName) {
    return prog->getRelationSize(relationName);
}
