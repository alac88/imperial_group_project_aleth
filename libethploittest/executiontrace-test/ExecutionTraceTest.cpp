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
  u256 valueTransfer = 10;

  BOOST_AUTO_TEST_CASE(constructor_test)
  {
    ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer);

    BOOST_TEST_MESSAGE("Constructor test: ");
    // Check if the values are stored in ExecutionTrace attributes 
    BOOST_TEST(execTrace.instruction == "CALL"); 
    BOOST_TEST(execTrace.senderAddress == sender.hex());
    BOOST_TEST(execTrace.receiveAddress == receiver.hex());
    BOOST_TEST(execTrace.valueTransfer == valueTransfer);
  }

  // BOOST_AUTO_TEST_CASE(unknown_instruction_gives_error_message)
  // {
  //   ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer);

  //   ostringstream buffer;

  //   // Save cout's buffer here
  //   auto cout_buff = cout.rdbuf();

  //   // Redirect cout to buffer
  //   cout.rdbuf(buffer.rdbuf());
    
  //   execTrace.print();
    
  //   // When done redirect cout to its old self
  //   cout.rdbuf(cout_buff);

  //   BOOST_TEST(string("CALL\n") == buffer.str(), boost::test_tools::per_element());
  // }

BOOST_AUTO_TEST_SUITE_END()