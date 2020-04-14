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
  u256 valueTransfer = 0;

  BOOST_AUTO_TEST_CASE(constructor_test)
  {
    ExecutionTrace execTrace (instruction, sender, receiver, valueTransfer);

    BOOST_TEST_MESSAGE("Constructor test: ");
    // Check if the values are stored in ExecutionTrace attributes 
    BOOST_TEST(execTrace.instruction == "CALL"); // TODO: perform better check here
    BOOST_TEST(execTrace.senderAddress == sender.hex());
    BOOST_TEST(execTrace.receiveAddress == receiver.hex());
    BOOST_TEST(execTrace.valueTransfer == valueTransfer);
  }

BOOST_AUTO_TEST_SUITE_END()