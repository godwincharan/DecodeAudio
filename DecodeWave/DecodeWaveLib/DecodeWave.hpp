#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include "IReader.hpp"

namespace decode_wave
{
    constexpr uint8_t BIT_STREAM_LENGHT = 11;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ZERO = 640;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ONE = 320;
    constexpr uint64_t ONE_MICRO_SEC = 1000000;
    constexpr uint8_t ERROR_THRESHOULD = 3;
class DecodeWave final
{
private:
    IReader::Ptr audio_reader_{nullptr};
    int64_t upper_audio_samples_for_bit_1_{0}; //Ideal Value 19
    int64_t lower_audio_samples_for_bit_1_{0}; //Ideal Value 13
    int64_t upper_audio_samples_for_bit_0_{0}; //Ideal Value 33
    int64_t lower_audio_samples_for_bit_0_{0}; //Ideal Value 27
public:
    explicit DecodeWave() noexcept;
    ~DecodeWave();

    bool IsReaderCreated() const noexcept;
    bool OpenFile(std::string& file_name) noexcept;

    void DumpAudioInfo() const noexcept;

    std::string Decode(const int8_t& channel) const noexcept;
private:
    void CreateReaderFor(std::string& extension);
    void CalculateLimit()noexcept;

};
} // decode_wave
#endif //DECODE_WAVE_HPP