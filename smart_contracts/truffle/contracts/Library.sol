pragma solidity ^0.4.8;

contract Library {

    uint private n;
    address private sender;

  function kill () {
    suicide(msg.sender);
  }
  
  function setN(uint _n) public {
    n = _n;
    sender = msg.sender;
  }
  
  function () payable {
  }

}