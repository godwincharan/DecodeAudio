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

    bool IsReaderCreated();
    bool OpenFile(std::string& file_name);

private:
    void CreateReaderFor(std::string& extension);
};
} // decode_wave
#endif //DECODE_WAVE_HPP