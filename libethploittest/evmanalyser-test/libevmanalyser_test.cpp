#define BOOST_TEST_MODULE libevmanalyser_test
#include "boost/test/included/unit_test.hpp"
#include "turtle/mock.hpp"
#include "evm_analyser.h"

// Mock class of ExecutionTrace
MOCK_BASE_CLASS(mock_execution_trace, dev::eth::ExecutionTrace) {
    mock_execution_trace(std::string _instruction,
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
        analyser = Evm_analyser_test::get_instance();
        BOOST_TEST_MESSAGE("setup fixture");
    }

    ~F() {
        analyser->clean_execution_trace();
        BOOST_TEST_MESSAGE("teardown fixture"); 
    }

    void add_call1() {
        mock_execution_trace et("CALL",
                                "0x60",
                                "0x70",
                                5,
                                10);

        analyser->populate_execution_trace(&et);          
    }

    void add_call2() {
        mock_execution_trace et("CALL",
                                "0x70",
                                "0x60",
                                5,
                                10);

        analyser->populate_execution_trace(&et);
    }

    Evm_analyser_test* analyser; 
};

// Test cases
BOOST_FIXTURE_TEST_SUITE(libevmanalyser_test, F)

    BOOST_AUTO_TEST_CASE(get_the_sigleton_of_libevmanalyser) {
        BOOST_TEST(analyser != nullptr);
    }

    BOOST_AUTO_TEST_CASE(the_libevmanalyser_has_no_execution_trace_just_after_being_constructed) {
        BOOST_TEST(analyser->get_relation_size("reentrancy") == 0);
    }

    BOOST_AUTO_TEST_CASE(populate_a_given_trace) {
        add_call1();

        BOOST_TEST(analyser->get_relation_size("direct_call") == 1);
    }

    BOOST_AUTO_TEST_CASE(populate_a_unrecognised_given_trace) {
         mock_execution_trace et("WRONG_CALL",
                                 "0x70",
                                 "0x60",
                                 5,
                                 10);

        BOOST_TEST(analyser->populate_execution_trace(&et) == false);
        BOOST_TEST(analyser->get_relation_size("direct_call") == 0);
    }

    BOOST_AUTO_TEST_CASE(query_a_reentrancy) {
        add_call1();
        add_call2();

        BOOST_TEST(analyser->query_expoilt("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(query_multiple_reentrancy) {
        mock_execution_trace et1("CALL", "0x60", "0x70", 5, 10);
        analyser->populate_execution_trace(&et1);

        mock_execution_trace et2("CALL", "0x70", "0x80", 5, 10);
        analyser->populate_execution_trace(&et2);
        
        mock_execution_trace et3("CALL", "0x80", "0x90", 5, 10);
        analyser->populate_execution_trace(&et3);
        
        mock_execution_trace et4("CALL", "0x90", "0x100", 5, 10);
        analyser->populate_execution_trace(&et4);
        
        mock_execution_trace et5("CALL", "0x90", "0x100", 5, 10);
        analyser->populate_execution_trace(&et5);

        mock_execution_trace et6("CALL", "0x100", "0x110", 5, 10);
        analyser->populate_execution_trace(&et6);
     
        mock_execution_trace et7("CALL", "0x110", "0x120", 5, 10);
        analyser->populate_execution_trace(&et7);

        mock_execution_trace et8("CALL", "0x120", "0x130", 5, 10);
        analyser->populate_execution_trace(&et8);
     
        mock_execution_trace et9("CALL", "0x130", "0x140", 5, 10);
        analyser->populate_execution_trace(&et9);
     
        mock_execution_trace et10("CALL", "0x140", "0x150", 5, 10);
        analyser->populate_execution_trace(&et10);
     
        mock_execution_trace et11("CALL", "0x150", "0x160", 5, 10);
        analyser->populate_execution_trace(&et11);
     
        mock_execution_trace et12("CALL", "0x160", "0x170", 5, 10);
        analyser->populate_execution_trace(&et12);
     
        mock_execution_trace et13("CALL", "0x170", "0x180", 5, 10);
        analyser->populate_execution_trace(&et13);
     
        mock_execution_trace et14("CALL", "0x180", "0x60", 5, 10);
        analyser->populate_execution_trace(&et14);

        BOOST_TEST(analyser->query_expoilt("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(not_allow_wrong_exploit_name) {
        add_call1();
        add_call2();

        BOOST_TEST(analyser->query_expoilt("wrong_reentrancy") == false);        
    }

    BOOST_AUTO_TEST_CASE(report_no_exploit) {
        add_call2();

        BOOST_TEST(analyser->query_expoilt("reentrancy") == false);        
    }

    BOOST_AUTO_TEST_CASE(clean_all_execution_trace) {
        add_call1();

        analyser->clean_execution_trace(); 

        BOOST_TEST(analyser->get_relation_size("direct_call") == 0);
    }
BOOST_AUTO_TEST_SUITE_END()