#pragma once

#include <fstream>
#include <json/json.h>

#define REENTRANCY_JSON "reentrancy.json"
#define LOCKED_ETHER_JSON "locked_ether.json"
#define UNHANDLED_EXCEPTION_JSON "unhandled_exception.json"

class JSONLogger {
    std::string account;
    std::string transactionHash;
    int64_t blockNumber;

    void addJSONHeader(Json::Value &json);

    std::ofstream reentrancyJSON;
    std::ofstream lockedEtherJSON;
    std::ofstream unhandledExceptionJSON;
    std::ofstream logJSON;

  public:
    JSONLogger(std::string _account, std::string _transactionHash, int64_t _blockNumber);
    
    void logReentrancy(Json::Value json);
    void logLockedEther(Json::Value json);
    void logUnhandledException(Json::Value json);

    void logTransaction(Json::Value json);

};