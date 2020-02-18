#include "DecodeWave.hpp"
#include "ReaderFactory.hpp"
#include <string>

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

std::string DecodeWave::Decode() noexcept
{
    std::string result{""};
    if(audio_reader_)
    {
        auto total_data = audio_reader_->TotalSamples() * audio_reader_->Channels();
        int16_t* sample_data = (int16_t*)malloc((size_t)total_data * sizeof(int16_t));
        auto read = audio_reader_->GetSamples16(audio_reader_->TotalSamples(), sample_data);
    }
    return result;
}
} // decode_wave