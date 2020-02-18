#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include "IReader.hpp"

namespace decode_wave
{
class DecodeWave final
{
private:
    IReader::Ptr audio_reader_{nullptr};
public:
    explicit DecodeWave() noexcept;
    ~DecodeWave();

    bool CreateReaderFor(std::string& file_name);
    bool OpenFile(std::string& file_name);
};
} // decode_wave
#endif //DECODE_WAVE_HPP

