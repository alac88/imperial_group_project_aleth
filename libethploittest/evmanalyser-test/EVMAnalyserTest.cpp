#define BOOST_TEST_MODULE libevmanalyser_test

#include<stdlib.h>

#include "boost/test/included/unit_test.hpp"
#include "turtle/mock.hpp"
#include "EVMAnalyser.h"

// Mock class of ExecutionTrace
MOCK_BASE_CLASS(ExecutionTraceMock, dev::eth::ExecutionTrace) {
    ExecutionTraceMock(std::string _instruction,
                         std::string _senderAddr, 
                         std::string _receiverAddr, 
                         int _valueTransfer)
        : dev::eth::ExecutionTrace() {
        instruction = _instruction;
        senderAddress = _senderAddr;
        receiveAddress = _receiverAddr;
        valueTransfer = _valueTransfer;
    }
};

// Note: Not a good idea to mock the Souffle generated classes since they involve
// with too many classes like relation and tuple as well as their virtual methods
// So makes more sense to assume the generated classes function properly and 
// based on it to run test of evm_analyser. 

// Fixtures
struct F {
    std::string randAccount;
    std::string randTransaction;

    F() {
        randAccount = std::to_string(rand());
        randTransaction = std::to_string(rand());

        analyser = EVMAnalyserTest::getInstance(randAccount, 
            randTransaction,
            rand(),
            rand());
        BOOST_TEST_MESSAGE("setup fixture");
    }

    ~F() {
        EVMAnalyserTest::getInstance(randAccount, 
            randTransaction,
            rand(),
            rand());
        analyser->cleanExecutionTrace();
        BOOST_TEST_MESSAGE("teardown fixture"); 
    }

    void addCall1() {
        ExecutionTraceMock et("CALL",
                                "0x60",
                                "0x70",
                                5);

        analyser->populateExecutionTrace(&et);          
    }

    void addCall2() {
        ExecutionTraceMock et("CALL",
                                "0x70",
                                "0x60",
                                5);

        analyser->populateExecutionTrace(&et);
    }

    void addCallEntry() {
        analyser->callEntry(1000, "0x60");
    }

    void addDelegateCall() {
        ExecutionTraceMock et("DELEGATECALL",
                                "0x70",
                                "0x60",
                                5);

        analyser->populateExecutionTrace(&et);
    }

    void addCallExit() {
        analyser->callExit(1000);
    }

    void addSwap1Instr() {
        analyser->instruction("SWAP1", 2, 2);
    }

    void addSwap5Instr() {
        analyser->instruction("SWAP5", 6, 6);
    }

    void addDup1Instr() {
        analyser->instruction("DUP1", 1, 2);
    }

    void addDup3Instr() {
        analyser->instruction("DUP3", 3, 4);
    }

    void addJumpIInstr() {
        analyser->instruction("JUMPI", 2, 0);
    }

    void addJumpIFInstr() {
        analyser->instruction("JUMPIF", 2, 0);
    }   
    
    void addJumpCIInstr() {
        analyser->instruction("JUMPCI", 2, 0);
    }

    void addCallInstr() {
        analyser->instruction("CALL", 7, 1);
    }  

    void addDelegateCallInstr() {
        analyser->instruction("DELEGATECALL", 6, 1);
    }      
    void addCallCodeInstr() {
        analyser->instruction("CALLCODE", 7, 1);
    }    

    void addCallResult(int success) {
        analyser->callResult(success);
    }
    
    void addInstruction(int nArgs, int nRet) {
        analyser->instruction("Test", nArgs, nRet);
    }

    int getStackID(int index) {
        return analyser->getStackID(index);
    }

    int getStackIDSize() {
        return analyser->getStackIDSize();
    }

    int getCallStackSize() {
        return analyser->getCallStackSize();
    }

    int getCallArgID(int callStackIndex, int argIndex) {
        return analyser->getCallArgID(callStackIndex, argIndex);
    }

    EVMAnalyserTest* analyser; 
};

// Test cases
BOOST_FIXTURE_TEST_SUITE(libevmanalyser_test, F)

    BOOST_AUTO_TEST_CASE(get_the_sigleton_of_libevmanalyser) {
        BOOST_TEST(analyser != nullptr);
    }
    BOOST_AUTO_TEST_CASE(initial_ethploit_mode_is_off) {
        BOOST_TEST(!EVMAnalyserTest::isEthploitModeEnabled());
    } 
    BOOST_AUTO_TEST_CASE(set_ethploit_mode_on) {
        EVMAnalyserTest::setEthploitMode();
        BOOST_TEST(EVMAnalyserTest::isEthploitModeEnabled());
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
                                 5);

        BOOST_TEST(analyser->populateExecutionTrace(&et) == false);
        BOOST_TEST(analyser->getRelationSize("direct_call") == 0);
    }

    BOOST_AUTO_TEST_CASE(query_a_reentrancy) {
        addCall1();
        addCall2();

        BOOST_TEST(analyser->queryExploit("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(query_multiple_reentrancy) {
        ExecutionTraceMock et1("CALL", "0x60", "0x70", 5);
        analyser->populateExecutionTrace(&et1);

        ExecutionTraceMock et2("CALL", "0x70", "0x80", 5);
        analyser->populateExecutionTrace(&et2);
        
        ExecutionTraceMock et3("CALL", "0x80", "0x90", 5);
        analyser->populateExecutionTrace(&et3);
        
        ExecutionTraceMock et4("CALL", "0x90", "0x60", 5);
        analyser->populateExecutionTrace(&et4);
        
        ExecutionTraceMock et5("CALL", "0x90", "0x100", 5);
        analyser->populateExecutionTrace(&et5);

        ExecutionTraceMock et6("CALL", "0x100", "0x110", 5);
        analyser->populateExecutionTrace(&et6);
     
        ExecutionTraceMock et7("CALL", "0x110", "0x120", 5);
        analyser->populateExecutionTrace(&et7);

        ExecutionTraceMock et8("CALL", "0x120", "0x130", 5);
        analyser->populateExecutionTrace(&et8);
     
        ExecutionTraceMock et9("CALL", "0x130", "0x140", 5);
        analyser->populateExecutionTrace(&et9);
     
        ExecutionTraceMock et10("CALL", "0x140", "0x150", 5);
        analyser->populateExecutionTrace(&et10);
     
        ExecutionTraceMock et11("CALL", "0x150", "0x160", 5);
        analyser->populateExecutionTrace(&et11);
     
        ExecutionTraceMock et12("CALL", "0x160", "0x170", 5);
        analyser->populateExecutionTrace(&et12);
     
        ExecutionTraceMock et13("CALL", "0x170", "0x180", 5);
        analyser->populateExecutionTrace(&et13);
     
        ExecutionTraceMock et14("CALL", "0x180", "0x90", 5);
        analyser->populateExecutionTrace(&et14);

        BOOST_TEST(analyser->queryExploit("reentrancy"));        
    }

    BOOST_AUTO_TEST_CASE(query_a_locked_ether) {
        addDelegateCall();
        addCallEntry();
        addCallExit();

        BOOST_TEST(analyser->queryExploit("locked_ether"));        
    }

    BOOST_AUTO_TEST_CASE(initial_stackIDs_is_empty) {
        BOOST_TEST(getStackIDSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(initial_callStack_is_empty) {
        BOOST_TEST(getCallStackSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(getStackIDSize_returns_correct_value) {
        addInstruction(0, 1);
        BOOST_TEST(getStackIDSize() == 1);
    }

    BOOST_AUTO_TEST_CASE(getCallStackSize_returns_correct_value) {
        addCallInstr();
        BOOST_TEST(getCallStackSize() == 1);
    }

     BOOST_AUTO_TEST_CASE(add_instruction_with_return_value_increases_stack_size_by_one) {
        addInstruction(0, 1);
        int initialStackSize = getStackIDSize();
        BOOST_TEST(initialStackSize == 1);

        addInstruction(0, 1);
        BOOST_TEST(getStackIDSize() == initialStackSize + 1);
    }

    BOOST_AUTO_TEST_CASE(add_instruction_with_args_decreases_stack_size_by_nArgs) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        int initialStackSize = getStackIDSize();
        BOOST_TEST(initialStackSize == 2);
        
        int nArgs = 2;
        addInstruction(nArgs, 0);
        int finalStackSize = initialStackSize - nArgs;
        BOOST_TEST(getStackIDSize() == finalStackSize);
    }

    BOOST_AUTO_TEST_CASE(add_instruction_with_args_and_ret_returns_correct_stack_size) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        int initialStackSize = getStackIDSize();

        int nArgs = 2;
        int nRet = 1;
        addInstruction(2, 1);
        int finalStackSize = initialStackSize - nArgs + nRet;
        BOOST_TEST(getStackIDSize() == finalStackSize);
    }

    BOOST_AUTO_TEST_CASE(do_nothing_if_no_of_return_values_more_than_one) {
        addInstruction(0, 2);
        
        BOOST_TEST(getStackIDSize() == 0);
    }

    BOOST_AUTO_TEST_CASE(do_nothing_if_nArgs_needed_is_more_than_available) {
        addInstruction(0, 1);
        int initialStackSize = getStackIDSize();
        BOOST_TEST(initialStackSize == 1);
        
        int nArgs = 2;
        addInstruction(nArgs, 0);
        BOOST_TEST(getStackIDSize() == initialStackSize);
        
        nArgs = 3;
        addInstruction(nArgs, 1);
        BOOST_TEST(getStackIDSize() == initialStackSize);
    }

    BOOST_AUTO_TEST_CASE(delegatecall_instr_consumes_six_args) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
 
        BOOST_TEST(getStackIDSize() == 6);

        addDelegateCallInstr();
        
        BOOST_TEST(getStackIDSize() == 0);        
    } 
    
    BOOST_AUTO_TEST_CASE(callcode_instr_consumes_seven_args) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
 
        BOOST_TEST(getStackIDSize() == 7);

        addCallCodeInstr();
        
        BOOST_TEST(getStackIDSize() == 0);        
    }

    BOOST_AUTO_TEST_CASE(call_instr_consumes_seven_args) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
 
        BOOST_TEST(getStackIDSize() == 7);

        addCallInstr();
        
        BOOST_TEST(getStackIDSize() == 0);        
    }

    BOOST_AUTO_TEST_CASE(all_call_instructions_without_call_result_adds_to_callStack) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();
        
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addDelegateCallInstr();
        
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallCodeInstr();

        BOOST_TEST(getCallStackSize() == 3);        
        BOOST_TEST(analyser->getRelationSize("is_output") == 0);        
    }

    BOOST_AUTO_TEST_CASE(call_instr_with_call_result_consumes_one_item_from_callStack) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();

        BOOST_TEST(getCallStackSize() == 1);        

        addCallResult(1);    

        BOOST_TEST(getCallStackSize() == 0);   
        BOOST_TEST(analyser->getRelationSize("is_output") == 7);        
        BOOST_TEST(analyser->getRelationSize("call_result") == 1);             
    }

    BOOST_AUTO_TEST_CASE(call_result_adds_one_item_to_stackID) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();

        BOOST_TEST(getStackIDSize() == 0);        

        addCallResult(1);    

        BOOST_TEST(getStackIDSize() == 1);       
        BOOST_TEST(analyser->getRelationSize("call_result") == 1);         
    }

    BOOST_AUTO_TEST_CASE(call_result_takes_latest_callArgs_in_callStack) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();
        int firstCallID = getCallArgID(0, 0);

        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();
        int secondCallID = getCallArgID(0, 0);

        addCallResult(1);

        BOOST_TEST(getCallArgID(0, 0) == firstCallID);        
    }

    BOOST_AUTO_TEST_CASE(do_nothing_upon_call_result_if_no_item_in_callStack) {
        
        BOOST_TEST(getCallStackSize() == 0);        

        addCallResult(1);

        BOOST_TEST(getStackIDSize() == 0);        
        BOOST_TEST(analyser->getRelationSize("call_result") == 0);        
    }

    BOOST_AUTO_TEST_CASE(swap_exchanges_stackIDs_positions) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        BOOST_TEST(getStackID(0) == 2);
        BOOST_TEST(getStackID(1) == 1);

        addSwap1Instr();

        BOOST_TEST(getStackID(0) == 1);
        BOOST_TEST(getStackID(1) == 2);
        BOOST_TEST(analyser->getRelationSize("is_output") == 0);
    }

    BOOST_AUTO_TEST_CASE(swap_does_nothing_if_no_stackID_at_required_position) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        BOOST_TEST(getStackID(0) == 2);
        BOOST_TEST(getStackID(1) == 1);

        addSwap5Instr();

        BOOST_TEST(getStackID(0) == 2);
        BOOST_TEST(getStackID(1) == 1);
    }

    BOOST_AUTO_TEST_CASE(dup_adds_a_new_stackID) {
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 1);

        addDup1Instr();

        BOOST_TEST(getStackIDSize() == 2);
        BOOST_TEST(analyser->getRelationSize("is_output") == 1);
    }

    BOOST_AUTO_TEST_CASE(dup_does_nothing_if_no_stackID_at_required_position) {
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 1);

        addDup3Instr();

        BOOST_TEST(getStackIDSize() == 1);
        BOOST_TEST(analyser->getRelationSize("is_output") == 0);
    }

    BOOST_AUTO_TEST_CASE(jumpi_consumes_two_stackIDs) {
        addInstruction(0, 1);
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 2);

        addJumpIInstr();

        BOOST_TEST(getStackIDSize() == 0);
        BOOST_TEST(analyser->getRelationSize("in_condition") == 1);

    }

    BOOST_AUTO_TEST_CASE(jumpif_consumes_two_stackIDs) {
        addInstruction(0, 1);
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 2);

        addJumpIFInstr();

        BOOST_TEST(getStackIDSize() == 0);
        BOOST_TEST(analyser->getRelationSize("in_condition") == 1);
    }   
    
    BOOST_AUTO_TEST_CASE(jumpci_consumes_two_stackIDs) {
        addInstruction(0, 1);
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 2);

        addJumpCIInstr();

        BOOST_TEST(getStackIDSize() == 0);
        BOOST_TEST(analyser->getRelationSize("in_condition") == 1);
    }

    BOOST_AUTO_TEST_CASE(jumpi_does_nothing_if_less_than_two_stackIDs) {
        addInstruction(0, 1);

        BOOST_TEST(getStackIDSize() == 1);

        addJumpIInstr();

        BOOST_TEST(getStackIDSize() == 1);
        BOOST_TEST(analyser->getRelationSize("in_condition") == 0);
    }

    BOOST_AUTO_TEST_CASE(query_unhandled_exception) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);

        addCallInstr();
        addCallResult(0); // failed call
    
        BOOST_TEST(analyser->queryExploit("unhandled_exception"));        
    }

    BOOST_AUTO_TEST_CASE(report_no_unhandled_exception) {
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);

        addCallInstr();
        addCallResult(0);
        addInstruction(0, 1); // jump destination
        addJumpIInstr();
    
        BOOST_TEST(!analyser->queryExploit("unhandled_exception"));        
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

    BOOST_AUTO_TEST_CASE(clean_execution_trace_resets_state) {
        addCall1();
        BOOST_TEST(analyser->getRelationSize("direct_call") == 1);
        
        addCallEntry();
        BOOST_TEST(analyser->getRelationSize("call_entry") == 1);
        addCallExit();
        BOOST_TEST(analyser->getRelationSize("call_exit") == 1);


        addInstruction(0, 1);
        addInstruction(1, 1);

        BOOST_TEST(getStackIDSize() > 0);
        BOOST_TEST(analyser->getRelationSize("is_output") > 0);
        
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();

        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addInstruction(0, 1);
        addCallInstr();
        addCallResult(1);
        addJumpIInstr();
        BOOST_TEST(getCallStackSize() > 0);
        BOOST_TEST(analyser->getRelationSize("call_result") > 0);
        BOOST_TEST(analyser->getRelationSize("in_condition") > 0);
        
        analyser->cleanExecutionTrace(); 

        BOOST_TEST(getStackIDSize() == 0);
        BOOST_TEST(getCallStackSize() == 0);

        BOOST_TEST(analyser->getRelationSize("direct_call") == 0);
        BOOST_TEST(analyser->getRelationSize("call_result") == 0);
        BOOST_TEST(analyser->getRelationSize("in_condition") == 0);
        BOOST_TEST(analyser->getRelationSize("call_entry") == 0);
        BOOST_TEST(analyser->getRelationSize("call_exit") == 0);

    }
BOOST_AUTO_TEST_SUITE_END()