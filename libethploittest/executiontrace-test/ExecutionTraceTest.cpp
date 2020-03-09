#define BOOST_TEST_MODULE ExecutionTraceTest
#include <boost/test/included/unit_test.hpp> 
#include <libethploit/ExecutionTrace.h>

using namespace std;
using namespace dev;
using namespace dev::eth;

BOOST_AUTO_TEST_SUITE(ExecutionTraceTestSuite)
  Instruction instruction = Instruction::CALL;
  Address sender ("1122334455667788991011121314151617181920");
  Address receiver ("1122334455667788991011121314151617181921");
  u256 gas = 10;
  uint64_t m_PC = 6;
  uint64_t returning_PC = 8;
  u256 valueTransfer = 0;
  u256 SP = 1;
  u256 SPP = 2;
  u256* m_SP = &SP;
  u256* m_SPP = &SPP;

  BOOST_AUTO_TEST_CASE(constructor_test)
  {
    ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer, gas, m_PC, m_SP, m_SPP);

    BOOST_TEST_MESSAGE("Constructor test: ");
    // Check if the values are stored in ExecutionTrace attributes 
    BOOST_TEST(execTrace.instruction == "CALL"); // TODO: perform better check here
    BOOST_TEST(execTrace.senderAddress == sender.hex());
    BOOST_TEST(execTrace.receiveAddress == receiver.hex());
    BOOST_TEST(execTrace.valueTransfer == valueTransfer);
    BOOST_TEST(execTrace.gas == gas);
    BOOST_TEST(execTrace.m_PC == m_PC);
    BOOST_TEST(*(execTrace.m_SP) == *m_SP);
    BOOST_TEST(*(execTrace.m_SPP) == *m_SPP);
    BOOST_TEST(execTrace.m_PC_post == 0);

  }

  BOOST_AUTO_TEST_CASE(setReturningPC_test)
  {
    ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer, gas, m_PC, m_SP, m_SPP);

    BOOST_TEST_MESSAGE("Method test - setReturningPC(): ");
    BOOST_TEST_MESSAGE("m_PC_post should be initialised to 0.");
    BOOST_TEST(execTrace.m_PC_post == 0);
    execTrace.setReturningPC(returning_PC);
    BOOST_TEST_MESSAGE("m_PC_post's value is set to returning_PC.");
    BOOST_TEST(execTrace.m_PC_post == returning_PC);
  }

  BOOST_AUTO_TEST_CASE(print_test) 
  {
    ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer, gas, m_PC, m_SP, m_SPP);

    ostringstream buffer;

    // Save cout's buffer here
    auto cout_buff = cout.rdbuf();

    // Redirect cout to buffer
    cout.rdbuf(buffer.rdbuf());
    
    execTrace.print();
    
    // When done redirect cout to its old self
    cout.rdbuf(cout_buff);

    BOOST_TEST(string("CALL\n") == buffer.str(), boost::test_tools::per_element());
  }
BOOST_AUTO_TEST_SUITE_END()