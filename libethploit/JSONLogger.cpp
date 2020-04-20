#include "JSONLogger.h"

using namespace std;

JSONLogger::JSONLogger() {
    reentrancyJSON.open(REENTRANCY_JSON, ofstream::app);
    lockedEtherJSON.open(LOCKED_ETHER_JSON, ofstream::app);
    unhandledExceptionJSON.open(UNHANDLED_EXCEPTION_JSON, ofstream::app);
    logJSON.open(TRANSACTION_JSON, ofstream::app);
}

JSONLogger::~JSONLogger() {
    reentrancyJSON.close();
    lockedEtherJSON.close();
    unhandledExceptionJSON.close();
    logJSON.close();
}

void JSONLogger::setTransactionInfo(string _account, string _transactionHash, int64_t _blockNumber) {
    account = _account;
    transactionHash = _transactionHash;
    blockNumber = _blockNumber;
}

void JSONLogger::addJSONHeader(Json::Value &json) {
    json["account"] = account;
    json["transaction_hash"] = transactionHash;
    json["block_number"] = blockNumber;
}

void JSONLogger::logReentrancy(std::string reentrancyChain, std::string totalEther) {
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["reentrancy_chain"] = reentrancyChain;
    json["total_ether_in_wei"] = totalEther;
    
    reentrancyJSON << json << endl;
}

void JSONLogger::logLockedEther(string contractAddress) {
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["contract_address"] = contractAddress;

    lockedEtherJSON << json << endl;
}

void JSONLogger::logUnhandledException(int stackID) {
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["stack_id"] = stackID; // StackID is meaningless outside the context
    
    unhandledExceptionJSON << json << endl;
}

void JSONLogger::logTransaction(int transactionCount, string totalTransfer) {
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["transaction_count"] = transactionCount;
    json["ether_checked_in_wei"] = totalTransfer;
    
    logJSON << json << endl;
}