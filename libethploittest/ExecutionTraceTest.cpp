#define BOOST_TEST_MODULE ExecutionTraceTest 
#include <boost/test/included/unit_test.hpp> 
#include <libethploit/ExecutionTrace.h>

int subtract(int i, int j) {
  return i-j;
}

BOOST_AUTO_TEST_CASE(first_test)
{
  int i = 1;
  BOOST_TEST(i);
  BOOST_TEST(i == 2);
}

BOOST_AUTO_TEST_CASE(ExecutionTraceTest)
{
  BOOST_CHECK(subtract(3, 1) == 2);
}