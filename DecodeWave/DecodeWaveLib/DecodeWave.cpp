#include "DecodeWave.hpp"
#include "ReaderFactory.hpp"
#include <string>
#include <vector>

namespace decode_wave
{
 DecodeWave::DecodeWave() noexcept
 {
 }

DecodeWave::~DecodeWave()
{
    audio_reader_ = nullptr;
}

void DecodeWave::CreateReaderFor(std::string& extension)
{
    audio_reader_ = ReaderFactory::Get().GetReader(extension);
}
 
bool DecodeWave::IsReaderCreated() const noexcept
{
    return audio_reader_ != nullptr;
}

bool DecodeWave::OpenFile(std::string& file_name) noexcept
{
    audio_reader_ = nullptr;
    auto pos = file_name.find_last_of(".");
    if(std::string::npos != pos)
    {
        auto extension = file_name.substr(pos);
        CreateReaderFor(extension);
    }

    if(audio_reader_)
    {
        return audio_reader_->OpenFile(file_name);
    }
    return false;
}

void DecodeWave::DumpAudioInfo() const noexcept
{
    if(audio_reader_)
    {
        return audio_reader_->Info();
    }
}

std::string DecodeWave::Decode(const int8_t& channel) const noexcept
{
    std::string result{""};
    if(audio_reader_)
    {
        audio_reader_->Info();
        auto overall_samples = audio_reader_->OverallSamples();
        int16_t* sample_data = new int16_t[overall_samples];
        auto read = audio_reader_->GetSamples16(overall_samples, sample_data);

        if (read == overall_samples)
        {
            auto fill_message_func = [&sample_data](const int8_t& channel, std::string& message)
            {
            };
            std::string message{""};
            fill_message_func(channel,message);
            result += message;
        }
        delete[] sample_data;
    }
    return result;
}
} // decode_wave