pragma solidity >0.4.6;

import "truffle/Assert.sol";
import "truffle/DeployedAddresses.sol";
import "../contracts/Contract1.sol";
import "../contracts/Contract2.sol";

contract TestContracts {
  function testInitialBalanceContract2() public {
    Contract2 c = new Contract2();

    uint expected = 0;

    Assert.equal(c.getBalance(), expected, "Contract2 should have an initial balance of 0");
  }

  function testBalanceOfContract2FromContract1() public {
    Contract1 c = new Contract1();

    uint expected = 0;

    Assert.equal(c.someAction(), expected, "This should return 0");
  }

  function testUpdateBalanceOfContract2FromContract1() public {
    Contract1 c = new Contract1();

    uint expected = 10000;

    Assert.equal(c.storeAction(expected), expected, "This should return 10000");
  }

}