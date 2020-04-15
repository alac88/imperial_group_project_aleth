pragma solidity ^0.4.8;

contract UnhandledException {

    mapping (address => uint) public balances;

    function getAmount(address account) public returns (uint){
        return balances[account];
    }

    function withdraw(address account) public {
        uint amount = getAmount(account);
        balances[account] -= amount;
        account.send(amount);
    }

}

