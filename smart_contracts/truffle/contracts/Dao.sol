pragma solidity ^0.4.8;

contract Dao {
    
    mapping (address => uint) public credit;

    function donate(address to){
        credit[to] += msg.value;
    }

    function queryCredit(address to) returns (uint){
        return credit[to];
    }

    function withdraw(uint amount) {
        if (credit [msg.sender] >= amount) {
            msg.sender.call.value(amount)();
            credit[msg.sender] -= amount;
        }
    }
}