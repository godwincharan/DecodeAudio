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

bool DecodeWave::CreateReaderFor(std::string& file_name)
{
    auto pos = file_name.find_last_of(".");
    if(std::string::npos != pos)
    {
        auto extension = file_name.substr(pos);
        audio_reader_ = ReaderFactory::Get().GetReader(extension);
    }

    return audio_reader_ != nullptr;
}

bool DecodeWave::OpenFile(std::string& file_name)
{
    if(!audio_reader_)
    {
        return CreateReaderFor(file_name);
    }

    if(audio_reader_)
    {
        return audio_reader_->OpenFile(file_name);
    }
    return false;
}


} // decode_wave