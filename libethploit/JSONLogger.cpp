#include "JSONLogger.h"

using namespace std;

JSONLogger::JSONLogger(string _account, string _transactionHash, int64_t _blockNumber) :
    account(_account), transactionHash(_transactionHash), blockNumber(_blockNumber) {
}

void JSONLogger::addJSONHeader(Json::Value &json) {
    json["account"] = account;
    json["transaction_hash"] = transactionHash;
    json["block_number"] = blockNumber;
}

void JSONLogger::logReentrancy(Json::Value json) {
    reentrancyJSON.open(REENTRANCY_JSON, std::ofstream::app);
    addJSONHeader(json);
    reentrancyJSON << json << endl;
    reentrancyJSON.close();
}

void JSONLogger::logLockedEther(Json::Value json) {
    lockedEtherJSON.open(LOCKED_ETHER_JSON, std::ofstream::app);
    addJSONHeader(json);
    lockedEtherJSON << json << endl;
    lockedEtherJSON.close();
}

void JSONLogger::logUnhandledException(Json::Value json) {
    unhandledExceptionJSON.open(UNHANDLED_EXCEPTION_JSON, std::ofstream::app);
    addJSONHeader(json);
    reentrancyJSON << json << endl;
    unhandledExceptionJSON.close();
}

void JSONLogger::logTransaction(Json::Value json) {
    logJSON.open("log.json", std::ofstream::app);
    addJSONHeader(json);
    logJSON << json << endl;
    logJSON.close();
}