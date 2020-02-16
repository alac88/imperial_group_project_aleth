#include "Executiontrace.h"

namespace dev 
{
namespace eth 
{

ExecutionTrace::ExecutionTrace(Instruction _inst, 
                                CallParameter _callParams,
                                uint64_t _m_PC, 
                                u256* _m_SP,
                                u256* _m_SPP)
{
    instructionInfo = InstructionInfo(_inst);
    callParams = _callParams;
    m_PC = _m_PC;
    m_SP = _m_SP;
    m_SPP = _m_SPP;
}

setReturningPC(uint64_t _m_PC) 
{
    m_PC_post = _m_PC;
}


}
}