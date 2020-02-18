#include "ReaderFactory.hpp"
#include "WaveReader.hpp"
#include <string>
namespace decode_wave
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
    return nullptr;
}
} // decode_wave