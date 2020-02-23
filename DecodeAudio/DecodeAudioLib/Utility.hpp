#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <sstream>
#include <iomanip>

namespace decode_audio
{
class Utility
{
public:
    template<typename T>
    static const std::string GetHexString(const T& value)
    {
        std::stringstream stream;
        stream << "0x" << std::setfill ('0') << std::setw(sizeof(T)) << std::hex << value;
        return stream.str();
    }

    template<typename T>
    static bool IsWithin(const T& min, const T& max, const T& value) 
    { 
        return (0 >=  (value - max) * (value - min)); 
    }
};
} // decode_audio
#endif //UTILITY_HPP

