#include "ExecutionTrace.h"

namespace dev 
{
    namespace eth 
    {

        ExecutionTrace::ExecutionTrace(Instruction _instruction, 
                                        Address _senderAddress,
                                        Address _receiveAddress,
                                        u256 _valueTransfer)
        {
            instruction = instructionInfo(_instruction).name;
            senderAddress = _senderAddress.hex();
            receiveAddress = _receiveAddress.hex();
            valueTransfer = _valueTransfer;
        }

        void ExecutionTrace::print() {
            std::cout << instruction << " ";
            std::cout << "Sender: " << senderAddress << " ";
            std::cout << "Receiver: " << receiveAddress << " ";
            std::cout << "valueTransfer: " << valueTransfer << " ";
        }

    }
}// LCOV_EXCL_LINE
