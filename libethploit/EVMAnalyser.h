#pragma once

#include "souffle/SouffleInterface.h"
#include "libethploit/ExecutionTrace.h"

#include "libdevcore/Common.h"

#include <string>
#include <vector>
#include <json/json.h>

class EVMAnalyser {
    static bool ethploitMode;

    // Trasaction information
    int64_t blockNumber;
    static int transactionCount;
    std::string transactionHash;
    std::string account;
    dev::u256 initialSenderBalance = 0;
    dev::u256 initialTotalBalance = 0;
    dev::u256 totalTransfer = 0;

    // Json files    
    /**
     * Example JSON for re-entrancy:
     * 
     *  {
     *    "account" : "1458777923",
     *    "reentrancy_chain" : "0x60 => 0x70 => 0x60",
     *    "total_ether" : 10,
     *    "transaction_hash" : "2007237709"
     *  }
     */ 
    std::ofstream reentrancyJSON;
    /**
     * Example JSON for locked ether:
     * 
     *   {
     *     "account" : "1784484492",
     *     "contract_address" : "0x60",
     *     "transaction_hash" : "74243042"
     *    }
     */ 
    std::ofstream lockedEtherJSON;
    std::ofstream unhandledExceptionJSON;
    std::ofstream logJSON;
    
    // Analysis-related
    int executionTraceCount;
    int latestID = 0;
    std::vector<int> stackIDs;
    std::vector<std::vector<int>> callStack;

    EVMAnalyser();
    ~EVMAnalyser(); 
    
    void initialiseJSON();
    void addJSONHeader(Json::Value &json);
    void extractReentrancyAddresses();
    void setAccount(std::string _account);
    void setupTransaction(std::string _transactionHash, dev::u256 senderBalance, dev::u256 receiverBalance, int64_t blockNumber);

    void swap(int pos); 

    void dup(int pos); 

    void jumpi();

    void argsRet(int nArgs, int nRet);

    void storeCallArgs(int nArgs);

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
    static EVMAnalyser* getInstance(std::string _account = "UNDEFINED", 
        std::string _transactionHash = "UNDEFINED", dev::u256 senderBalance = -1, dev::u256 receiverBalance = -1,
        int64_t _blockNum = -1);


    static void setEthploitMode();
    
    static bool isEthploitModeEnabled();

    bool populateExecutionTrace(dev::eth::ExecutionTrace* executionTrace);

    bool queryExploit(std::string exploitName);

    void cleanExecutionTrace();

    void callEntry(int gas, std::string contractAddress);

    void callExit(int gas);

    void instruction(std::string const& opcode, int nArgs, int nRet);

    void callResult(int result);

    int getStackID(int index);

    int getStackIDSize();

    int getCallStackSize();

    int getCallArgID(int callStackIndex, int argIndex);

};

/**
 * Extending EVMAnalyser for testing
 */ 
class EVMAnalyserTest : public EVMAnalyser {
  public:
    EVMAnalyserTest();

    static EVMAnalyserTest* getInstance(std::string _account = "UNDEFINED", 
                                        std::string _transactionHash = "UNDEFINED", 
                                        dev::u256 senderBalance = -1, 
                                        dev::u256 receiverBalance = -1);
    
    int getRelationSize(std::string relationName);
};

