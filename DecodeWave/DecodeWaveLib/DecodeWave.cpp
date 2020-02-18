#define DR_WAV_IMPLEMENTATION
#include "DecodeWave.hpp"
#include "Logger.hpp"
#include <sstream>
#include <iomanip>
#include <cstdint>

namespace decode_wave
{
 DecodeWave::DecodeWave() noexcept
 {
 }

DecodeWave::~DecodeWave()
{
    drwav_uninit(&wav_);
}

bool DecodeWave::OpenFile(std::string& file_name)
{
    if(!file_name.empty())
    {
        return drwav_init_file(&wav_, file_name.c_str(), nullptr);
    }
    return false;
}
} // decode_wave