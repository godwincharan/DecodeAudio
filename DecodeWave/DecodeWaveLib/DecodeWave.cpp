#include "DecodeWave.hpp"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

namespace decode_wave
{
 DecodeWave::DecodeWave() noexcept
 {
 }

DecodeWave::~DecodeWave()
{
}

bool DecodeWave::OpenFile(std::string& file_name)
{
    if(!file_name.empty())
    {
        drwav wav_;
        if (drwav_init_file(&wav_, file_name.c_str(), nullptr)) {
        }
    }
    return false;
}
} // decode_wave