#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>
#include <vector>

class EVMAnalyser {
    int executionTraceCount;
    /**
     * Example JSON for re-entrancy
     */ 
    std::ofstream reentrancyJSON;
    std::ofstream lockedEtherJSON;
    
    int latestID = 0;
    std::vector<int> stackIDs;

    EVMAnalyser();
    ~EVMAnalyser(); 
    
    void initialiseJSON(); 
    void extractReentrancyAddresses();
    void setTransactionHash(std::string _transactionHash);
    void setAccount(std::string _account);

    void swap(int pos); 

    void dup(int pos); 

    void jumpi();

    void argsRet(int nArgs, int nRet);
  protected:
    std::string transactionHash;
    std::string account;

    souffle::SouffleProgram *prog;

    souffle::Relation *relDirectCall;
    souffle::Relation *relCallEntry;
    souffle::Relation *relCallExit;
    souffle::Relation *queReentrancy;
    souffle::Relation *relIsOutput;
    souffle::Relation *relCallResult;
    souffle::Relation *relInCondition;

  public:
    static EVMAnalyser* getInstance(std::string _account = "UNDEFINED", 
        std::string _transactionHash = "UNDEFINED");

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();

    void callEntry(int gas, std::string contractAddress);

    void callExit(int gas);

    void instruction(std::string const& opcode, int nArgs, int nRet);

    void callResult(int result);
};

/**
 * Extending EVMAnalyser for testing
 */ 
class EVMAnalyserTest : public EVMAnalyser {
  public:
    EVMAnalyserTest();

    static EVMAnalyserTest* getInstance(std::string _account = "UNDEFINED", 
        std::string _transactionHash = "UNDEFINED");
    
    int getRelationSize(std::string relationName);
};

