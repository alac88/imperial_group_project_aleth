pragma solidity >0.4.6;


contract Contract2 {
    uint public balance = 0;
    // address public addr;

    // constructor(address _addr) public {
    //     addr = _addr;
    // }

    function getBalance() public view returns(uint){
        return balance;
    }

    function storeValue(uint value) public {
        balance = value;
    }
}