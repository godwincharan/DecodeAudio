#ifndef READER_FACTORY_HPP
#define READER_FACTORY_HPP

#include "IReader.hpp"

namespace decode_audio
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
} // decode_audio
#endif //READER_FACTORY_HPP

