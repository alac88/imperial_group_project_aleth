#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>

class EVMAnalyser {
    int executionTraceCount;
    /**
     * Example JSON for re-entrancy
     */ 
    std::ofstream reentrancyJSON;
    std::ofstream lockedEtherJSON;

    EVMAnalyser();
    ~EVMAnalyser(); 
    
    void initialiseJSON(); 
    void extractReentrancyAddresses();
    void setTransactionHash(std::string _transactionHash);
    void setAccount(std::string _account);

  protected:
    std::string transactionHash;
    std::string account;

    souffle::SouffleProgram *prog;

    souffle::Relation *relDirectCall;
    souffle::Relation *relCallEntry;
    souffle::Relation *relCallExit;
    souffle::Relation *queReentrancy;

  public:
    static EVMAnalyser* getInstance(std::string _account = "UNDEFINED", 
        std::string _transactionHash = "UNDEFINED");

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();

    void callEntry(int gas, std::string contractAddress);

    void callExit(int gas);
};

/**
 * Extending EVMAnalyser for testing
 */ 
class EVMAnalyserTest : public EVMAnalyser {
  public:
    EVMAnalyserTest();

    static EVMAnalyserTest* getInstance();
    
    int getRelationSize(std::string relationName);
};

