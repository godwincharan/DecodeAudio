#include "DecodeWave.hpp"
#include "Logger.hpp"
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
    bool result = false;
    if(!file_name.empty())
    {
        drwav wav_;
        if (drwav_init_file(&wav_, file_name.c_str(), nullptr)) 
        {
            logger::Log::Get().log(std::string("Channels: ") + std::to_string(wav_.channels));
            if (2 == wav_.channels)
            {
                result = true;
            }
            drwav_uninit(&wav_);
        }
    }
    return result;
}
} // decode_wave