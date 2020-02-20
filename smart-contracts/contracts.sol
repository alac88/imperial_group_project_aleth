pragma solidity >0.4.6;

contract Contract1 {
    function someAction(address addr) public view returns(uint) {
        Contract2 c = Contract2(addr);
        return c.getValue();
    }

    function storeAction(address addr) public returns(uint) {
        Contract2 c = Contract2(addr);
        c.storeValue(100);
        return c.getValue();
    }
}

contract Contract2 {
    uint public initialValue;

    function getValue() public view returns(uint){
        return initialValue;
    }

    function storeValue(uint value) public {
        initialValue = value;
    }
}