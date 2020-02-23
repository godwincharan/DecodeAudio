#include "FlacReader.hpp"
#include <Logger.hpp>
#include <string>

namespace decode_audio
{
 FlacReader::FlacReader() noexcept
 {
 }

FlacReader::~FlacReader()
{
}

bool FlacReader::OpenFile(const std::string& file_name)
{
    is_valid_ = false;
    if(!file_name.empty())
    {
        logger::Log::Get().log(std::string("Implementation pending."));
        is_valid_ = true;
    }
    return is_valid_;
}

uint64_t FlacReader::GetSamples(const uint64_t& no_of_samples, int16_t* sample_data)
{
    return 0;
}

void FlacReader::Info() const noexcept
{
    if (is_valid_)
    {
        logger::Log::Get().log(std::string("Channels: ") + std::to_string(0));
        logger::Log::Get().log(std::string("Sample Rate: ") + std::to_string(0));
        logger::Log::Get().log(std::string("Total Samples: ") + std::to_string(0));
        logger::Log::Get().log(std::string("Bit Depth: ") + std::to_string(0));
    }
}

uint64_t FlacReader::TotalSamples() const noexcept
{
    return 0;
}

int16_t FlacReader::Channels() const noexcept
{
    return -1;
}

uint64_t FlacReader::SampleRate() const noexcept
{
    return 0;
}

uint64_t FlacReader::OverallSamples() const noexcept
{
    return 0;
}

bool FlacReader::HasChannel(const uint16_t& channel) const noexcept
{
    return false;
}

bool FlacReader::SeekZero() noexcept
{
    return true;
}

} // decode_audio