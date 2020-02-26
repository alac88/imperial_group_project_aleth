#include "ExecutionTrace.h"
namespace dev 
{
    namespace eth 
    {

        ExecutionTrace::ExecutionTrace(Instruction _instruction, 
                                        Address _senderAddress,
                                        Address _receiveAddress,
                                        u256 _valueTransfer,
                                        u256 _gas,
                                        uint64_t _m_PC, 
                                        u256* _m_SP,
                                        u256* _m_SPP)
        {
            instruction = instructionInfo(_instruction).name;
            senderAddress = _senderAddress.hex();
            receiveAddress = _receiveAddress.hex();
            valueTransfer = _valueTransfer;
            gas = _gas;
            m_PC = _m_PC;
            m_SP = _m_SP;
            m_SPP = _m_SPP;
        }

        void ExecutionTrace::setReturningPC(uint64_t _m_PC) 
        {
            m_PC_post = _m_PC;
        }

        void ExecutionTrace::print() {
            std::cout << instruction << std::endl;
        }

    }
}// LCOV_EXCL_LINE
