#include "ReaderFactory.hpp"
#include "WaveReader.hpp"
#include "OggReader.hpp"
#include "FlacReader.hpp"
#include <string>

namespace decode_audio
{
ReaderFactory::ReaderFactory() noexcept{
}

ReaderFactory::~ReaderFactory()
{
}

ReaderFactory& ReaderFactory::Get()
{
    static ReaderFactory reader_factory;
    return reader_factory;
}

IReader::Ptr ReaderFactory::GetReader(const std::string& extension)
{
    if(std::string(".wav") == extension)
    {
        return std::make_shared<WaveReader>();
    }
    else if(std::string(".ogg") == extension)
    {
        return std::make_shared<OggReader>();
    }
    else if(std::string(".flac") == extension)
    {
        return std::make_shared<FlacReader>();
    }
    
    return nullptr;
}
} // decode_audio