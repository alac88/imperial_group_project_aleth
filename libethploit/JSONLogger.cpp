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

void JSONLogger::logReentrancy(std::string reentrancyChain, std::string totalEther) {
    fstream reentrancyJSON;
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["reentrancy_chain"] = reentrancyChain;
    json["total_ether_in_wei"] = totalEther;
    
    reentrancyJSON.open(REENTRANCY_JSON, std::ofstream::app);
    reentrancyJSON << json << endl;
    reentrancyJSON.close();
}

void JSONLogger::logLockedEther(string contractAddress) {
    fstream lockedEtherJSON;
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["contract_address"] = contractAddress;

    lockedEtherJSON.open(LOCKED_ETHER_JSON, std::ofstream::app);
    lockedEtherJSON << json << endl;
    lockedEtherJSON.close();
}

void JSONLogger::logUnhandledException(int stackID) {
    fstream unhandledExceptionJSON;
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["stack_id"] = stackID; // StackID is meaningless outside the context
    
    unhandledExceptionJSON.open(UNHANDLED_EXCEPTION_JSON, std::ofstream::app);
    unhandledExceptionJSON << json << endl;
    unhandledExceptionJSON.close();
}

void JSONLogger::logTransaction(int transactionCount, string totalTransfer) {
    fstream logJSON;
    Json::Value json(Json::objectValue);

    addJSONHeader(json);
    json["transaction_count"] = transactionCount;
    json["ether_checked_in_wei"] = totalTransfer;
    
    logJSON.open(TRANSACTION_JSON, std::ofstream::app);
    logJSON << json << endl;
    logJSON.close();
}