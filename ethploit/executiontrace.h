#pragma once

#include <cstdint>
// #include <intx/intx.hpp>

// #include <evmc/evmc.h>
#include "libdevcore/Address.h"
#include "libevm/Instruction.h"
#include "libevm/ExtVMFace.h"

namespace dev 
{
namespace eth
{



struct ExecutionTrace 
{

    /**
     * contains:
     * char const* const name;
     * int const args; 
     * int const ret;
     * Tier const gasPriceTier
     */     
    InstructionInfo instructionInfo;

    /**
     * contains
     * Address senderAddress
     * Address codeAddress
     * Address receiveAddress
     * u256 valueTransfer
     * u256 apparentValue
     * u256 gas
     * bytesConstRef data
     * bool staticCall 
     * OnOpFunc onOp
     */
    CallParameters callParams;

    uint64_t m_PC;  // program counter
    uint64_t m_PC_post = 0; // returning program counter for delegate call
    u256* m_SP;    // stack pointer
    u256* m_SPP;    // stack pointer


    ExecutionTrace(Instruction _inst,
                    CallParameters _callParams,
                    uint64_t _m_PC, 
                    u256* _m_SP,
                    u256* _m_SPP);

    setReturningPC(uint64_t _m_PC);

}



}
}