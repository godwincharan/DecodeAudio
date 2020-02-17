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
    if(!file_name.empty())
    {
        drwav wav_;
        if (drwav_init_file(&wav_, file_name.c_str(), nullptr)) 
        {
            std::cout << "Channels: " << wav_.channels << std::endl;
            if (2 == wav_.channels)
            {
                return true;
            }
            
        }
    }
    return false;
}
} // decode_wave