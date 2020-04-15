pragma solidity ^0.4.8;


contract TestParity {
  
  function delegate (address _e, address _owner) {
    _e.delegatecall(bytes4(keccak256("addOwner(address)")), _owner);
  }

}