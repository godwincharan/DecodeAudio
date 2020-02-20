#define DR_WAV_IMPLEMENTATION
#include "WaveReader.hpp"
#include <Logger.hpp>
#include <string>
#include "Utility.hpp"

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

uint64_t WaveReader::GetSamples16(const uint64_t& no_of_samples, int16_t* sample_data)
{
    if (is_valid_)
    {
        return drwav_read_pcm_frames_s16(&wav_, no_of_samples, sample_data);
    }
    return 0;
}

uint64_t WaveReader::GetSamples24(const uint64_t& no_of_samples, int32_t* sample_data) 
{
    return 0;
}

uint64_t WaveReader::GetSamples32(const uint64_t& no_of_samples, int32_t* sample_data)
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

uint64_t WaveReader::TotalSamples() const noexcept
{
    if (is_valid_)
    {
        return wav_.totalPCMFrameCount;
    }
    return 0;
}

int16_t WaveReader::Channels() const noexcept
{
    if (is_valid_)
    {
        return wav_.channels;
    }
    return -1;
}

uint64_t WaveReader::SampleRate() const noexcept
{
    if (is_valid_)
    {
        return wav_.sampleRate;
    }
    return 0;
}

uint64_t WaveReader::OverallSamples() const noexcept
{
    if (is_valid_)
    {
        return wav_.totalPCMFrameCount * wav_.channels;
    }
    return 0;
}

bool WaveReader::HasChannel(const uint16_t& channel) const noexcept
{
    if (is_valid_)
    {
        return Utility::IsWithin(static_cast<uint16_t>(0),static_cast<uint16_t>(wav_.channels-1),channel);
    }
    return false;
}

bool WaveReader::SeekZero() noexcept
{
    if (is_valid_)
    {
        return drwav_seek_to_pcm_frame(&wav_, 0);
    }
    return true;
}

} // decode_wave