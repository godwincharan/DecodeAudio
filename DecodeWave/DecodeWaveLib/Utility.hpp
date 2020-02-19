#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <sstream>
#include <iomanip>

namespace decode_wave
{
class Utility
{
public:
    template<typename T>
    static bool IsWithin(const T& min, const T& max, const T& value) 
    { 
        return (0 >=  (value - max) * (value - min)); 
    }
};
} // decode_wave
#endif //UTILITY_HPP

