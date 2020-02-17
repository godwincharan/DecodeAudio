#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include <iostream>

namespace decode_wave
{
class DecodeWave final
{
public:
    explicit DecodeWave() noexcept;
    ~DecodeWave();

    bool OpenFile(std::string& file_name);
};
} // decode_wave
#endif //DECODE_WAVE_HPP

