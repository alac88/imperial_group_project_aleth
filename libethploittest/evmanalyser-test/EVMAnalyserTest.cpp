#define BOOST_TEST_MODULE libevmanalyser_test
#include "boost/test/included/unit_test.hpp"
#include "turtle/mock.hpp"
#include "EVMAnalyser.h"

// Mock class of ExecutionTrace
MOCK_BASE_CLASS(ExecutionTraceMock, dev::eth::ExecutionTrace) {
    ExecutionTraceMock(std::string _instruction,
                         std::string _senderAddr, 
                         std::string _receiverAddr, 
                         int _valueTransfer, 
                         int _gas)
        : dev::eth::ExecutionTrace() {
        instruction = _instruction;
        senderAddress = _senderAddr;
        receiveAddress = _receiverAddr;
        valueTransfer = _valueTransfer;
        gas = _gas;
        
        // uint64_t m_PC;  // program counter
        // uint64_t m_PC_post = 0; // returning program counter for delegate call
        // u256* m_SP;    // stack pointer
        // u256* m_SPP;    // stack pointer    
    }
};

// Note: Not a good idea to mock the Souffle generated classes since they involve
// with too many classes like relation and tuple as well as their virtual methods
// So makes more sense to assume the generated classes function properly and 
// based on it to run test of evm_analyser. 

// Fixtures
struct F {
    F() {
        // static factory_Sf_reentrancy __factory_Sf_reentrancy_instance;
        analyser = EVMAnalyserTest::getInstance();
        BOOST_TEST_MESSAGE("setup fixture");
    }

    ~F() {
        analyser->cleanExecutionTrace();
        BOOST_TEST_MESSAGE("teardown fixture"); 
    }

    void addCall1() {
        ExecutionTraceMock et("CALL",
                                "0x60",
                                "0x70",
                                5,
                                10);

        analyser->populateExecutionTrace(&et);          
    }

    void addCall2() {
        ExecutionTraceMock et("CALL",
                                "0x70",
                                "0x60",
                                5,
                                10);

        analyser->populateExecutionTrace(&et);
    }

    void addCallEntry() {
        analyser->callEntry(1000, "0x60");
    }

    void addDelegateCall() {
        ExecutionTraceMock et("DELEGATECALL",
                                "0x70",
                                "0x60",
                                5,
                                10);

        analyser->populateExecutionTrace(&et);
    }

    void addCallExit() {
        analyser->callExit(1000);
    }

    EVMAnalyserTest* analyser; 
};

// Test cases
BOOST_FIXTURE_TEST_SUITE(libevmanalyser_test, F)

    BOOST_AUTO_TEST_CASE(get_the_sigleton_of_libevmanalyser) {
        BOOST_TEST(analyser != nullptr);
    }

    BOOST_AUTO_TEST_CASE(the_libevmanalyser_has_no_execution_trace_just_after_being_constructed) {
        BOOST_TEST(analyser->getRelationSize("reentrancy") == 0);
    }

    BOOST_AUTO_TEST_CASE(populate_a_given_trace) {
        addCall1();

        BOOST_TEST(analyser->getRelationSize("direct_call") == 1);
    }

    BOOST_AUTO_TEST_CASE(populate_a_unrecognised_given_trace) {
         ExecutionTraceMock et("WRONG_CALL",
                                 "0x70",
                                 "0x60",
                                 5,
                                 10);

        BOOST_TEST(analyser->populateExecutionTrace(&et) == false);
        BOOST_TEST(analyser->getRelationSize("direct_call") == 0);
    }

    BOOST_AUTO_TEST_CASE(query_a_reentrancy) {
        addCall1();
        addCall2();

        BOOST_TEST(analyser->queryExploit("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(query_multiple_reentrancy) {
        ExecutionTraceMock et1("CALL", "0x60", "0x70", 5, 10);
        analyser->populateExecutionTrace(&et1);

        ExecutionTraceMock et2("CALL", "0x70", "0x80", 5, 10);
        analyser->populateExecutionTrace(&et2);
        
        ExecutionTraceMock et3("CALL", "0x80", "0x90", 5, 10);
        analyser->populateExecutionTrace(&et3);
        
        ExecutionTraceMock et4("CALL", "0x90", "0x100", 5, 10);
        analyser->populateExecutionTrace(&et4);
        
        ExecutionTraceMock et5("CALL", "0x90", "0x100", 5, 10);
        analyser->populateExecutionTrace(&et5);

        ExecutionTraceMock et6("CALL", "0x100", "0x110", 5, 10);
        analyser->populateExecutionTrace(&et6);
     
        ExecutionTraceMock et7("CALL", "0x110", "0x120", 5, 10);
        analyser->populateExecutionTrace(&et7);

        ExecutionTraceMock et8("CALL", "0x120", "0x130", 5, 10);
        analyser->populateExecutionTrace(&et8);
     
        ExecutionTraceMock et9("CALL", "0x130", "0x140", 5, 10);
        analyser->populateExecutionTrace(&et9);
     
        ExecutionTraceMock et10("CALL", "0x140", "0x150", 5, 10);
        analyser->populateExecutionTrace(&et10);
     
        ExecutionTraceMock et11("CALL", "0x150", "0x160", 5, 10);
        analyser->populateExecutionTrace(&et11);
     
        ExecutionTraceMock et12("CALL", "0x160", "0x170", 5, 10);
        analyser->populateExecutionTrace(&et12);
     
        ExecutionTraceMock et13("CALL", "0x170", "0x180", 5, 10);
        analyser->populateExecutionTrace(&et13);
     
        ExecutionTraceMock et14("CALL", "0x180", "0x60", 5, 10);
        analyser->populateExecutionTrace(&et14);

        BOOST_TEST(analyser->queryExploit("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(query_a_locked_ether) {
        addCallEntry();
        addDelegateCall();
        addCallExit();

        BOOST_TEST(analyser->queryExploit("locked_ether"));        
    }

    BOOST_AUTO_TEST_CASE(not_allow_wrong_exploit_name) {
        addCall1();
        addCall2();

        BOOST_TEST(analyser->queryExploit("wrong_reentrancy") == false);        
    }

    BOOST_AUTO_TEST_CASE(report_no_exploit) {
        addCall2();

        BOOST_TEST(analyser->queryExploit("reentrancy") == false);        
    }

    BOOST_AUTO_TEST_CASE(clean_all_execution_trace) {
        addCall1();

        analyser->cleanExecutionTrace(); 

        BOOST_TEST(analyser->getRelationSize("direct_call") == 0);
    }
BOOST_AUTO_TEST_SUITE_END()