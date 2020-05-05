#include <set>
#include <queue>
#include <iostream>
#include <fstream>
#include <boost/algorithm/string.hpp>

#include "type.h"
#include "EVMAnalyser.h"
#include "souffle/SouffleInterface.h"
#ifndef EVMANALYSER_TEST
    #include "DetectionLogic.cpp"
#endif

// Output related marcros
#define FORERED "\x1B[31m"
#define RESETTEXT "\x1B[0m"
#define OUTPUT std::cout << "[Middleware]: " 

int EVMAnalyser::transactionCount = 0;
bool EVMAnalyser::ethploitMode = false;

EVMAnalyser::EVMAnalyser() {
    executionTraceCount = 1;

    prog = souffle::ProgramFactory::newInstance("DetectionLogic");

    relDirectCall = prog->getRelation("direct_call");
    relCallEntry = prog->getRelation("call_entry");
    relCallExit = prog->getRelation("call_exit");
    relIsOutput = prog->getRelation("is_output");
    relCallResult = prog->getRelation("call_result");
    relInCondition = prog->getRelation("in_condition");

    logger = new JSONLogger();
}

EVMAnalyser::~EVMAnalyser() {
    delete logger;
}

EVMAnalyser* EVMAnalyser::getInstance(std::string account, 
                                      std::string _transactionHash, 
                                      dev::u256 senderBalance, 
                                      dev::u256 receiverBalance,
                                      int64_t blockNumber) {
    static EVMAnalyser instance;
    if (_transactionHash != "UNDEFINED" && account != "UNDEFINED") {
        instance.setupTransaction(account, _transactionHash, senderBalance, receiverBalance, blockNumber);
    }
    return &instance; 
}

void EVMAnalyser::setEthploitMode() {
    ethploitMode = true;
};

bool EVMAnalyser::isEthploitModeEnabled() {
    return ethploitMode;
}

void EVMAnalyser::setBadTransaction() {
    badTransaction = true;
}

void EVMAnalyser::setupTransaction(std::string account,
                                   std::string _transactionHash, 
                                   dev::u256 senderBalance, 
                                   dev::u256 receiverBalance,
                                   int64_t blockNumber) {
    if (senderBalance != -1 && receiverBalance != -1) {
        if (transactionHash != _transactionHash) {// New transaction
            badTransaction = false;
            logger->setTransactionInfo(account, _transactionHash, blockNumber);

            // Update transaction information
            transactionCount++;
            transactionHash = _transactionHash;
            initialSenderBalance = senderBalance;
            initialTotalBalance = senderBalance + receiverBalance;
        } else {// Same transaction
            dev::u256 totalDifference = initialTotalBalance - (senderBalance + receiverBalance);
            totalTransfer += initialSenderBalance - senderBalance + totalDifference;
        }

    }
}

bool EVMAnalyser::populateCallTrace(dev::eth::CallTrace* callTrace) {
    if (callTrace->instruction == "CALL" ||
        callTrace->instruction == "DELEGATECALL" ||
        callTrace->instruction == "STATICCALL") { // Treating three types of call as the same for now 
        souffle::tuple newTuple(relDirectCall); // create tuple for the relation
#ifdef EVMANALYSER_DEBUG
        OUTPUT << "The populated instruction has ID number " << executionTraceCount << std::endl;
#endif
        newTuple << executionTraceCount
                << callTrace->senderAddress
                << callTrace->receiveAddress
                << dev::toString(callTrace->valueTransfer);
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

void EVMAnalyser::callEntry(dev::u256 gas, std::string contractAddress) {
    // Note that the DELEGATECALL relation has been populated now
    // So Minus 1 to refer back the DELEGATECALL
    souffle::tuple newTuple(relCallEntry); 
    newTuple << executionTraceCount-1 << dev::toString(gas) << contractAddress;
    relCallEntry->insert(newTuple);

#ifdef EVMANALYSER_DEBUG
    OUTPUT << "callEntry for " << executionTraceCount << " has been populated"
        << std::endl;
#endif

}

void EVMAnalyser::callExit(dev::u256 gas) {
    souffle::tuple newTuple(relCallExit);
    newTuple << executionTraceCount-1 << dev::toString(gas); // Minus 1 to refer back the DELEGATECALL
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
            return;
        }
        // create new ID
        latestID++;

        // for each arg
        for (int i = 0; i < nArgs; i++) {
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
    if (callStack.size() < 1) {
        return;
    }
    // create new ID when call result is received
    latestID++;

    // take first callArgs in callStack
    auto callArgs = callStack[0];
    for (auto &arg : callArgs) {
        // insert tuple to is_output
        souffle::tuple newTuple(relIsOutput);
        newTuple << latestID << arg;
        relIsOutput->insert(newTuple); 
    }

    // remove callArgs from callStack
    callStack.erase(callStack.begin());
    
    // insert tuple to call_result
    souffle::tuple newTuple(relCallResult);
    newTuple << latestID << result;
    relCallResult->insert(newTuple); 

    // push new ID
    stackIDs.insert(stackIDs.begin(), latestID);
};

void EVMAnalyser::swap(int pos) {
    if (stackIDs.size() < (unsigned)(pos + 1)) {
        return;
    }
    // no tuple insertion
    // swap IDs on stack
    std::swap(stackIDs[0], stackIDs[pos]);

}; // SWAP2 = swap first(0) and third(2) element

void EVMAnalyser::dup(int pos) {
    if (stackIDs.size() < (unsigned) pos) {
        return;
    }
    // create newID
    latestID++;

    // take ID of the original position
    // insert tuple to is_output
    souffle::tuple newTuple(relIsOutput);
    newTuple << latestID << stackIDs[pos - 1];
    relIsOutput->insert(newTuple); 

    // push newID to stack
    stackIDs.insert(stackIDs.begin(), latestID);
}; // DUP2 = dup second(1) element on the stack

void EVMAnalyser::jumpi() {
    if (stackIDs.size() < 2) {
        return;
    }
    // take second element on stack as condition 
    // insert tuple to in_condition
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
        std::string ether1, ether2;

        count++;
        output >> id >> senderAddr >> receiverAddr >> ether1 >> ether2;
        idSet.insert(id);
    }

    dev::u256 totalEther = 0;
    unsigned long i = 0;
    std::queue<std::string> chain;
    std::string receiverAddrPre = "Null";
    for (auto &output : *relDirectCall) {
        int idOriginal;
        std::string senderAddrOriginal, receiverAddrOriginal;
        std::string etherOriginalStr;  // Ether transferred is passed as u256 via executionTrace
        dev::u256 etherOriginal;

        output >> idOriginal >> senderAddrOriginal >> receiverAddrOriginal >> etherOriginalStr;
        etherOriginal = dev::toU256(etherOriginalStr);

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

                // Save the new json tuple
                if (!badTransaction)
                    logger->logReentrancy(reentrancyChain, dev::toString(totalEther));

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
                    std::string gas;

                    count++;
                    output >> id >> gas >> contractAddress;
#ifdef EVMANALYSER_RESULT
                    OUTPUT << FORERED << "Query Result: " << count << " Contract in address: " 
                        << contractAddress << " has been locked"  << RESETTEXT << std::endl; 
#endif
                    if (!badTransaction)
                        logger->logLockedEther(contractAddress);
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
                    if (!badTransaction)
                        logger->logUnhandledException(stackID);
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
    if (!badTransaction)
        logger->logTransaction(transactionCount, dev::toString(totalTransfer));

    executionTraceCount = 1;
    latestID = 0;
    stackIDs.clear();
    callStack.clear();
}

EVMAnalyserTest* EVMAnalyserTest::getInstance(std::string _account, 
                                              std::string _transactionHash,
                                              dev::u256 _senderBalance, 
                                              dev::u256 _receiverBalance,
                                              int64_t _blockNumber) {
    return (EVMAnalyserTest *) EVMAnalyser::getInstance(_account, 
        _transactionHash, 
        _senderBalance, 
        _receiverBalance, 
        _blockNumber); 
}

int EVMAnalyserTest::getRelationSize(std::string relationName) {
    return prog->getRelationSize(relationName);
} // LCOV_EXCL_LINE
