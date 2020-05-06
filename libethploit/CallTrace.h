#pragma once

#include <cstdint>
#include <string>
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



struct CallTrace 
{

    std::string instruction;
    std::string senderAddress;
    std::string receiveAddress;
    u256 valueTransfer;

    CallTrace() {}; // Add a default constructor for the convenience of test
    CallTrace(Instruction _instruction,
                    Address _senderAddress,
                    Address _receiveAddres,
                    u256 _valueTransfer);

};



}
}
