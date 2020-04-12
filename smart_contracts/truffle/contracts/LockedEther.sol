pragma solidity ^0.4.8;

import "./Library.sol";

contract LockedEther {

  Library public lib;
  
  function delegate (address _e, uint _n) {
    _e.delegatecall(bytes4(keccak256("setN(uint256)")), _n);
  }

}