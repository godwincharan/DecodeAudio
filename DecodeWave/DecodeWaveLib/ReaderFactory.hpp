#ifndef READER_FACTORY_HPP
#define READER_FACTORY_HPP

#include "IReader.hpp"

namespace decode_wave
{
class ReaderFactory final
{
private:
    explicit ReaderFactory() noexcept;
    ~ReaderFactory();
public:
    static ReaderFactory& Get();
    
    IReader::Ptr GetReader(const std::string& extension);
};
} // decode_wave
#endif //READER_FACTORY_HPP

