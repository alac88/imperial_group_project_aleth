#pragma once

#include <cstdint>
#include <memory>
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
    Instruction instruction;

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
    // CallParameters callParams;
    Address senderAddress;
    Address receiveAddress;
    u256 gas;

    uint64_t m_PC;  // program counter
    uint64_t m_PC_post = 0; // returning program counter for delegate call
    u256* m_SP;    // stack pointer
    u256* m_SPP;    // stack pointer


    ExecutionTrace(Instruction _instruction,
                    Address _senderAddress,
                    Address _receiveAddres,
                    u256 gas,
                    uint64_t _m_PC, 
                    u256* _m_SP,
                    u256* _m_SPP);

    void setReturningPC(uint64_t _m_PC);

    void print();

};



}
}