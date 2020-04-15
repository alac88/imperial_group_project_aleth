#include <set>
#include <queue>
#include <fstream>
#include <json/json.h>
#include <boost/algorithm/string.hpp>

#include "EVMAnalyser.h"
#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "DetectionLogic.cpp"
#endif
#include <iostream>
// #define EVMANALYSER_DEBUG
// #define EVMANALYSER_RESULT

// Output related marcros
#define FORERED "\x1B[31m"
#define RESETTEXT "\x1B[0m"
#define OUTPUT std::cout << "[Middleware]: " 

int EVMAnalyser::transactionCount = 0;

EVMAnalyser::EVMAnalyser() {
    executionTraceCount = 1;

    prog = souffle::ProgramFactory::newInstance("DetectionLogic");

    relDirectCall = prog->getRelation("direct_call");
    relCallEntry = prog->getRelation("call_entry");
    relCallExit = prog->getRelation("call_exit");
    relIsOutput = prog->getRelation("is_output");
    relCallResult = prog->getRelation("call_result");
    relInCondition = prog->getRelation("in_condition");
}

EVMAnalyser::~EVMAnalyser() {
    // An default constructor for testing
}

void EVMAnalyser::initialiseJSON() {
    // New JSON tuples default to be appended to the current files.
    reentrancyJSON.open("reentrancy.json", std::ofstream::app);
    lockedEtherJSON.open("locked_ether.json", std::ofstream::app);
    unhandledExceptionJSON.open("unhandled_exception.json", std::ofstream::app);
    logJSON.open("log.json", std::ofstream::app);
}

void EVMAnalyser::setTransactionHash(std::string _transactionHash) {
    transactionHash = _transactionHash;
}

void EVMAnalyser::setAccount(std::string _account) {
    account = _account;
}

EVMAnalyser* EVMAnalyser::getInstance(std::string _account, std::string _transactionHash, dev::u256 senderBalance, dev::u256 receiverBalance) {
    static EVMAnalyser instance;
    if (_transactionHash != "UNDEFINED") {
        instance.setupTransaction(_transactionHash, senderBalance, receiverBalance);
    }
    if (_account != "UNDEFINED") {
        instance.setAccount(_account);
    }
    return &instance; 
}

void EVMAnalyser::setupTransaction(std::string _transactionHash, dev::u256 senderBalance, dev::u256 receiverBalance) {
    if (senderBalance != -1 && receiverBalance != -1) {
        if (transactionHash != _transactionHash) {
            initialiseJSON();
            transactionHash = _transactionHash;
            transactionCount++;
            initialSenderBalance = senderBalance;
            initialTotalBalance = senderBalance + receiverBalance;
        } else {
            dev::u256 totalDifference = initialTotalBalance - (senderBalance + receiverBalance);
            totalTransfer += initialSenderBalance - senderBalance + totalDifference;
        }

    }
}

bool EVMAnalyser::populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace) {
    if (executionTrace->instruction == "CALL" ||
        executionTrace->instruction == "DELEGATECALL" ||
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
    } else {
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "No existing relation matches up with this instruction!" 
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

void EVMAnalyser::instruction(std::string const& opcode, int nArgs, int nRet) {   
    if (opcode.find("SWAP") != std::string::npos) {
        int pos = std::stoi(opcode.substr(4));
        swap(pos);
        return;
    }
    if (opcode.find("DUP") != std::string::npos) {
        int pos = std::stoi(opcode.substr(3));
        dup(pos);
        return;
    }
    if (opcode.find("JUMPI") != std::string::npos 
        || opcode.find("JUMPIF") != std::string::npos 
        || opcode.find("JUMPCI") != std::string::npos) { 
        jumpi();
        return;
    }
    if (opcode == "DELEGATECALL" || opcode == "STATICCALL" || opcode == "CALL" || opcode == "CALLCODE") {
        storeCallArgs(nArgs);
        return;
    }

    argsRet(nArgs, nRet);
};

void EVMAnalyser::storeCallArgs(int nArgs) {
    std::vector<int> callArgs;
    for (int i = 0; i < nArgs; i++) {
        callArgs.push_back(stackIDs[i]);
    }
    
    callStack.insert(callStack.begin(), callArgs);
    // remove args used
    if (stackIDs.size() >= (unsigned) nArgs)
        stackIDs.erase(stackIDs.begin(), stackIDs.begin() + nArgs);
};

void EVMAnalyser::argsRet(int nArgs, int nRet) {
    if (nArgs > 0 && nRet == 1) {
        if (stackIDs.size() < (unsigned) nArgs) {
            std::cout << "Error: the number of arguments required does not match with the available arguments on the stack!\n";
            return;
        }
        // create new ID
        latestID++;

        // for each arg
        for (int i = 0; i < nArgs; i++) {
#ifdef EVMANALYSER_DEBUG
            OUTPUT << "insert to is_output: " << latestID << " " << stackIDs[i] << std::endl;
#endif
            // insert tuple to is_output
            souffle::tuple newTuple(relIsOutput);
            newTuple << latestID << stackIDs[i];
            relIsOutput->insert(newTuple); 
        }

        // remove args used
        stackIDs.erase(stackIDs.begin(), stackIDs.begin() + nArgs);
        // push new ID
        stackIDs.insert(stackIDs.begin(), latestID);
    } else if (nArgs > 0) {
        if (stackIDs.size() < (unsigned) nArgs) {
            std::cout << "Error: the number of arguments required does not match with the available arguments on the stack!\n";
            return;
        }

        // remove args used
        stackIDs.erase(stackIDs.begin(), stackIDs.begin() + nArgs);
    } else if (nRet == 1) {
        // push new ID
        stackIDs.insert(stackIDs.begin(), ++latestID);
    }
}

void EVMAnalyser::callResult(int result) {
    // create new ID when call result is received
    latestID++;

    if (callStack.size() < 1) {
        std::cout << "Error: there is no pending call arguments on the call stack!\n";
        return;
    }
    // take first callArgs in callStack
    auto callArgs = callStack[0];
    for (auto &arg : callArgs) {
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "insert to is_output: " << latestID << " " << arg << std::endl;
#endif
        // insert tuple to is_output
        souffle::tuple newTuple(relIsOutput);
        newTuple << latestID << arg;
        relIsOutput->insert(newTuple); 
    }

    // remove callArgs from callStack
    callStack.erase(callStack.begin());
    
    // insert tuple to call_result
#ifdef EVMANALYSER_DEBUG
    OUTPUT << "insert to call_result: " << latestID << " " << result << std::endl;
#endif
    souffle::tuple newTuple(relCallResult);
    newTuple << latestID << result;
    relCallResult->insert(newTuple); 

    // push new ID
    stackIDs.insert(stackIDs.begin(), latestID);
};

void EVMAnalyser::swap(int pos) {
    if (stackIDs.size() < 2) {
        std::cout << "Error: the number of arguments required does not match with the available arguments on the stack!\n";
        return;
    }
    // no tuple insertion
    // swap IDs on stack
    std::swap(stackIDs[0], stackIDs[pos]);
    // std::cout << "New state: ";
    // for (auto &i : stackIDs) 
    //     std::cout << i << ", ";
    // std::cout << std::endl;

}; // SWAP2 = swap first(0) and third(2) element

void EVMAnalyser::dup(int pos) {
    if (stackIDs.size() < (unsigned) pos) {
        std::cout << "Error: the number of arguments required does not match with the available arguments on the stack!\n";
        return;
    }
    // create newID
    latestID++;

    // take ID of the original position
    // insert tuple to is_output
#ifdef EVMANALYSER_DEBUG
    OUTPUT << "insert to is_output: " << latestID << " " << stackIDs[pos - 1] << std::endl;
#endif
    souffle::tuple newTuple(relIsOutput);
    newTuple << latestID << stackIDs[pos - 1];
    relIsOutput->insert(newTuple); 

    // push newID to stack
    stackIDs.insert(stackIDs.begin(), latestID);
}; // DUP2 = dup second(1) element on the stack

void EVMAnalyser::jumpi() {
    if (stackIDs.size() < 2) {
        std::cout << "Error: the number of arguments required does not match with the available arguments on the stack!\n";
        return;
    }
    // take second element on stack as condition 
    // insert tuple to in_condition
#ifdef EVMANALYSER_DEBUG
    OUTPUT << "insert to in_condition: " << stackIDs[1] << std::endl;
#endif
    souffle::tuple newTuple(relInCondition);
    newTuple << stackIDs[1];
    relInCondition->insert(newTuple); 

    // remove first two elements on stack
    stackIDs.erase(stackIDs.begin(), stackIDs.begin() + 2);
};

int EVMAnalyser::getStackID(int index) {
    if (stackIDs.size() >= (unsigned) index)
        return stackIDs[index];
    return -1;
};

int EVMAnalyser::getStackIDSize() {
    return stackIDs.size();
};

int EVMAnalyser::getCallStackSize() {
    return callStack.size();
};

int EVMAnalyser::getCallArgID(int callStackIndex, int argIndex) {
    return callStack[callStackIndex][argIndex];
};

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
                Json::Value json(Json::objectValue);

                // Standard json fields
                json["account"] = account;
                json["transaction_hash"] = transactionHash;

                // Output the address chain
                if (senderAddrOriginal != receiverAddrPre) {
                    chain.pop();
                    totalEther -= etherOriginal;
                }

#ifdef EVMANALYSER_RESULT
                OUTPUT << FORERED <<"Query Result: " << " Re-entrancy: ";
#endif

                std::string reentrancyChain = chain.front();
                std::string addrStart = chain.front();
#ifdef EVMANALYSER_RESULT
                std::cout << addrStart;
#endif                
                chain.pop();
                while (!chain.empty()) {
#ifdef EVMANALYSER_RESULT
                    std::cout << " => " << chain.front();
#endif              
                    reentrancyChain += " => " + chain.front();
                    chain.pop();
                }
#ifdef EVMANALYSER_RESULT        
                std::cout << " => " << addrStart << " has been detected with " << totalEther 
                    << " value transferred in total." << RESETTEXT
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

                // Save the new json tuple
                reentrancyJSON << json << std::endl;
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
#ifdef EVMANALYSER_RESULT
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
#ifdef EVMANALYSER_RESULT
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
#ifdef EVMANALYSER_RESULT
                OUTPUT << "No locked ether has been detected." << std::endl;
#endif
                return false; 
            }
        }

        // Unhandled exception
        if (exploitName == "unhandled_exception") {
            if (rel->size() != 0) {
                int stackID;
                int count = 0;

                for (auto &output : *rel) {
                    std::string contractAddress; 
                    int id;
                    int gas;

                    count++;
                    output >> stackID;
#ifdef EVMANALYSER_RESULT
                    OUTPUT << FORERED << "Query Result: " << count << " Unhandled exception detected. " 
                        << "StackID: " << stackID << RESETTEXT << std::endl; 
#endif
                    Json::Value json(Json::objectValue);
                    json["account"] = account;
                    json["transaction_hash"] = transactionHash;
                    json["stack_id"] = stackID; // StackID is meaningless outside the context
                    unhandledExceptionJSON << json << std::endl;
                }
                return true; 
            } else {
#ifdef EVMANALYSER_RESULT
                OUTPUT << "No unhandled exception has been detected." << std::endl;
#endif
                return false;
            }
        }
    }

#ifdef EVMANALYSER_RESULT
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
    unhandledExceptionJSON.close();

    Json::Value json(Json::objectValue);
    json["account"] = account;
    json["transaction_hash"] = transactionHash;
    json["transaction_count"] = transactionCount;
    json["ether_checked"] = dev::toString(totalTransfer);
    logJSON << json << std::endl;
    logJSON.close();

    executionTraceCount = 1;
    latestID = 0;
    stackIDs.clear();
    callStack.clear();
}

EVMAnalyserTest* EVMAnalyserTest::getInstance(std::string _account, std::string _transactionHash,
    dev::u256 _senderBalance, dev::u256 _receiverBalance) {
    return (EVMAnalyserTest *) EVMAnalyser::getInstance(_account, _transactionHash, _senderBalance, _receiverBalance); 
}

int EVMAnalyserTest::getRelationSize(std::string relationName) {
    return prog->getRelationSize(relationName);
}
