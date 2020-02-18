#define DR_WAV_IMPLEMENTATION
#include "WaveReader.hpp"
#include <Logger.hpp>
#include <string>

namespace decode_wave
{
 WaveReader::WaveReader() noexcept
 {
 }

WaveReader::~WaveReader()
{
    drwav_uninit(&wav_);
}

bool WaveReader::OpenFile(const std::string& file_name)
{
    if(!file_name.empty())
    {
        return drwav_init_file(&wav_, file_name.c_str(), nullptr);
    }
    return false;
}

uint64_t WaveReader::GetSamples16(const int64_t& no_of_samples, uint16_t* sample_data)
{
    return 0;
}
uint64_t WaveReader::GetSamples24(const int64_t& no_of_samples, uint32_t* sample_data) 
{
    return 0;
}
uint64_t WaveReader::GetSamples32(const int64_t& no_of_samples, uint32_t* sample_data)
{
    return 0;
}
} // decode_wave