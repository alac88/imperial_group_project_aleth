#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>

class EVMAnalyser {
    int executionTraceCount;

    EVMAnalyser();
    ~EVMAnalyser(); 
    
    void extractReentrancyAddresses();

  protected:
    souffle::SouffleProgram *prog;
    souffle::SouffleProgram *prog_locked_ether;
    souffle::Relation *relDirectCall;
    souffle::Relation *relCallEntry;
    souffle::Relation *relCallExit;
    souffle::Relation *queReentrancy;
  public:
    static EVMAnalyser* getInstance();

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();

    void transactionBegins(int gas, std::string callerAddress);

    void transactionEnds(int gas);
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

