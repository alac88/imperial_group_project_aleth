#pragma once

#include <fstream>
#include <json/json.h>

#define REENTRANCY_JSON "reentrancy.json"
#define LOCKED_ETHER_JSON "locked_ether.json"
#define UNHANDLED_EXCEPTION_JSON "unhandled_exception.json"
#define TRANSACTION_JSON "log.json"

class JSONLogger {
    std::string account;
    std::string transactionHash;
    int64_t blockNumber;

    std::fstream reentrancyJSON;
    std::fstream lockedEtherJSON;
    std::fstream unhandledExceptionJSON;
    std::fstream logJSON;


    void addJSONHeader(Json::Value &json);

  public:
    JSONLogger();
    ~JSONLogger();
    
    void setTransactionInfo(std::string _account, std::string _transactionHash, int64_t _blockNumber);

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
    void logReentrancy(std::string reentrancyChain, std::string totalEther);
    /**
     * Example JSON for locked ether:
     * 
     *   {
     *     "account" : "1784484492",
     *     "contract_address" : "0x60",
     *     "transaction_hash" : "74243042"
     *    }
     */ 
    void logLockedEther(std::string contractAddress);
    void logUnhandledException(int stackID);

    void logTransaction(int transactionCount, std::string totalTransfer);

};