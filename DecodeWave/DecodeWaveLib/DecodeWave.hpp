#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include <iostream>
#include "dr_wav.h"

namespace decode_wave
{
class DecodeWave final
{
private:
    drwav wav_;
public:
    explicit DecodeWave() noexcept;
    ~DecodeWave();

    bool OpenFile(std::string& file_name);
};
} // decode_wave
#endif //DECODE_WAVE_HPP

