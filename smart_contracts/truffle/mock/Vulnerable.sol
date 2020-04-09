pragma solidity >0.4.6;
import “./Malicious.sol”;
contract Vulnerable {
    mapping (address => uint) public _balanceOf;
    uint private count = 0;
    function withdrawEquityVulnerable() public returns (bool){
        if (count < 5){
            count++;
            uint x = _balanceOf[msg.sender];
            (bool result, )= msg.sender.call.value(x)(“”);
            _balanceOf[msg.sender] = 0;
            return result;
        }
        return true;
    }
    function withdrawEquityCorrect() public{
        uint x = _balanceOf[msg.sender];
        _balanceOf[msg.sender] = 0;
        (bool result, )= msg.sender.call.value(x)(“”);
        require(result);
    }
}