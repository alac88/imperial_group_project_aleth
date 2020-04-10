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
    relIsOutput = prog->getRelation("is_output");
    relCallResult = prog->getRelation("call_result");
    relInCondition = prog->getRelation("in_condition");
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

    argsRet(nArgs, nRet);
};

void EVMAnalyser::argsRet(int nArgs, int nRet) {
    if (nArgs > 0 && nRet == 1) {
        // create new ID
        latestID++;

        // for each arg
        for (int i = 0; i < nArgs; i++) {
            std::cout << "insert to is_output: " << latestID << " " << stackIDs[i] << std::endl;
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
        // remove args used
        stackIDs.erase(stackIDs.begin(), stackIDs.begin() + nArgs);
    } else if (nRet == 1) {
        // push new ID
        stackIDs.insert(stackIDs.begin(), ++latestID);
    }
    std::cout << "New state: ";
    for (auto &i : stackIDs) 
        std::cout << i << ", ";
    std::cout << std::endl;
}

void EVMAnalyser::callResult(int result) {
    // take latestID and result
    // insert tuple to call_result
    std::cout << "insert to call_result: " << latestID << " " << result << std::endl;
    souffle::tuple newTuple(relCallResult);
    newTuple << latestID << result;
    relCallResult->insert(newTuple); 
    std::cout << "New state: ";
    for (auto &i : stackIDs) 
        std::cout << i << ", ";
    std::cout << std::endl;

};

void EVMAnalyser::swap(int pos) {
    // no tuple insertion
    // swap IDs on stack
    std::swap(stackIDs[0], stackIDs[pos]);
    std::cout << "New state: ";
    for (auto &i : stackIDs) 
        std::cout << i << ", ";
    std::cout << std::endl;

}; // SWAP2 = swap first(0) and third(2) element

void EVMAnalyser::dup(int pos) {
    // create newID
    latestID++;

    // take ID of the original position
    // insert tuple to is_output
    std::cout << "insert to is_output: " << latestID << " " << stackIDs[pos - 1] << std::endl;
    souffle::tuple newTuple(relIsOutput);
    newTuple << latestID << stackIDs[pos - 1];
    relIsOutput->insert(newTuple); 

    // push newID to stack
    stackIDs.insert(stackIDs.begin(), latestID);
    std::cout << "New state: ";
    for (auto &i : stackIDs) 
        std::cout << i << ", ";
    std::cout << std::endl;

}; // DUP2 = dup second(1) element on the stack

void EVMAnalyser::jumpi() {
    // take second element on stack as condition 
    // insert tuple to in_condition
    std::cout << "insert to in_condition: " << stackIDs[1] << std::endl;
    // souffle::tuple newTuple(relInCondition);
    // newTuple << stackIDs[1];
    // relInCondition->insert(newTuple); 

    // remove first two elements on stack
    stackIDs.erase(stackIDs.begin(), stackIDs.begin() + 2);
    std::cout << "New state: ";
    for (auto &i : stackIDs) 
        std::cout << i << ", ";
    std::cout << std::endl;

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

        // Unhandled exception
        if (exploitName == "unhandled_exception") {
            if (rel->size() != 0) {
                std::string contractAddress; 
                // int id;
                // int gas;
                int count = 0;

                for (auto &output : *rel) {
                    count++;
                    // output >> id >> gas >> contractAddress;
                    OUTPUT << FORERED << "Query Result: " << count << " unhandled exception detected." << std::endl; 
                }
                return true; 
            } else {
                OUTPUT << "No unhandled exception has been detected." << std::endl;
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
    latestID = 0;
    stackIDs.clear();
}

EVMAnalyserTest* EVMAnalyserTest::getInstance() {
    return (EVMAnalyserTest *) EVMAnalyser::getInstance(); 
}

int EVMAnalyserTest::getRelationSize(std::string relationName) {
    return prog->getRelationSize(relationName);
}
