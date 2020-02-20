pragma solidity >0.4.6;

import "../contracts/Contract2.sol";

contract Contract1 {
    function someAction() public returns(uint) {
        Contract2 c = new Contract2();
        return c.getBalance();
    }

    function storeAction(uint value) public returns(uint) {
        Contract2 c = new Contract2();
        c.storeValue(value);
        return c.getBalance();
    }
}