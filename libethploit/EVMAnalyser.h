#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include <string>

class EVMAnalyser {
    int executionTraceCount;
    EVMAnalyser();
    ~EVMAnalyser(); 
  protected:
    souffle::SouffleProgram *prog;
    souffle::Relation *relDirectCall;
    souffle::Relation *queReentrancy;
  public:
    static EVMAnalyser* getInstance();

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();
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

