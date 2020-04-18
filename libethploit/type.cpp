#include "type.h"

#include <string>
#include <boost/algorithm/string.hpp>

namespace dev {

u256 toU256(std::string str) {
    u256 ret = 0;
    for (char ch : str) {
        ret += ch - '0';
        ret *= 10;
    }
    ret /= 10;
    
    return ret;
}
}