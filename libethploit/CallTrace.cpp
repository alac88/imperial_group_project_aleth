#include "CallTrace.h"

namespace dev 
{
    namespace eth 
    {

        CallTrace::CallTrace(Instruction _instruction, 
                                        Address _senderAddress,
                                        Address _receiveAddress,
                                        u256 _valueTransfer)
        {
            instruction = instructionInfo(_instruction).name;
            senderAddress = _senderAddress.hex();
            receiveAddress = _receiveAddress.hex();
            valueTransfer = _valueTransfer;
        }

    }
}// LCOV_EXCL_LINE
