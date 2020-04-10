#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>
#include <vector>

class EVMAnalyser {
    int executionTraceCount;
    
    int latestID = 0;
    std::vector<int> stackIDs;

    EVMAnalyser();
    ~EVMAnalyser(); 
    
    void extractReentrancyAddresses();

    void swap(int pos); 

    void dup(int pos); 

    void jumpi();

    void argsRet(int nArgs, int nRet);
  protected:
    souffle::SouffleProgram *prog;
    souffle::Relation *relDirectCall;
    souffle::Relation *relCallEntry;
    souffle::Relation *relCallExit;
    souffle::Relation *queReentrancy;
    souffle::Relation *relIsOutput;
    souffle::Relation *relCallResult;
    souffle::Relation *relInCondition;

  public:
    static EVMAnalyser* getInstance();

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();

    void callEntry(int gas, std::string contractAddress);

    void callExit(int gas);

    void instruction(std::string opcode, int nArgs, int nRet);

    void callResult(int result);
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

