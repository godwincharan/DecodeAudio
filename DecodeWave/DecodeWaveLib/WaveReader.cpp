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
    is_valid_ = false;
    if(!file_name.empty())
    {
        is_valid_ = drwav_init_file(&wav_, file_name.c_str(), nullptr);
    }
    return is_valid_;
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

void WaveReader::Info() const noexcept
{
    if (is_valid_)
    {
        logger::Log::Get().log(std::string("Channels: ") + std::to_string(wav_.channels));
        logger::Log::Get().log(std::string("Sample Rate: ") + std::to_string(wav_.sampleRate));
        logger::Log::Get().log(std::string("Total Samples: ") + std::to_string(wav_.totalPCMFrameCount));
        logger::Log::Get().log(std::string("Bit Depth: ") + std::to_string(wav_.bitsPerSample));
    }
}
} // decode_wave