#define BOOST_TEST_MODULE CallTraceTest
#include <boost/test/included/unit_test.hpp> 
#include <libethploit/ExecutionTrace.h>

using namespace std;
using namespace dev;
using namespace dev::eth;

BOOST_AUTO_TEST_SUITE(CallTraceTestSuite)
  Instruction instruction = Instruction::CALL;
  Address sender ("1122334455667788991011121314151617181920");
  Address receiver ("1122334455667788991011121314151617181921");
  u256 valueTransfer = 10;

  BOOST_AUTO_TEST_CASE(constructor_test)
  {
    CallTrace callTrace (instruction, sender, receiver, valueTransfer);

    BOOST_TEST_MESSAGE("Constructor test: ");
    // Check if the values are stored in CallTrace attributes 
    BOOST_TEST(callTrace.instruction == "CALL"); 
    BOOST_TEST(callTrace.senderAddress == sender.hex());
    BOOST_TEST(callTrace.receiveAddress == receiver.hex());
    BOOST_TEST(callTrace.valueTransfer == valueTransfer);
  }

BOOST_AUTO_TEST_SUITE_END()