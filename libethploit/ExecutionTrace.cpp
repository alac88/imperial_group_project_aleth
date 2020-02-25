#include "ExecutionTrace.h"

namespace dev 
{
    namespace eth 
    {

        ExecutionTrace::ExecutionTrace(Instruction _instruction, 
                                        Address _senderAddress,
                                        Address _receiveAddress,
                                        u256 _gas,
                                        uint64_t _m_PC, 
                                        u256* _m_SP,
                                        u256* _m_SPP)
        {
            instruction = _instruction;
            senderAddress = _senderAddress;
            receiveAddress = _receiveAddress;
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

            InstructionInfo info = instructionInfo(instruction);
            std::cout << info.name << std::endl;
            // std::cout << instruction << std::endl;
            // std::cout << senderAddress << std::endl;
            // std::cout << receiveAddress << std::endl;
            // std::cout << gas << std::endl;
            // std::cout << m_PC << std::endl;
            // std::cout << m_SP << std::endl;
            // std::cout << m_SPP << std::endl;

        }
    }
} // LCOV_EXCL_LINE
