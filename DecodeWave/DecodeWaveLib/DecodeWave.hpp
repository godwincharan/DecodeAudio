#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include "AudioReader/IReader.hpp"
#include <deque>

namespace decode_wave
{
    constexpr uint8_t BIT_STREAM_LENGHT = 11;
    constexpr uint8_t START_ID_ONE_VALUE = 0x42;
    constexpr uint8_t START_ID_TWO_VALUE = 0x03;
    constexpr uint8_t END_ID_VALUE = 0x00;
    constexpr uint8_t ID_BYTE_COUNT = 0x02;
    constexpr uint8_t MESSAGE_COUNT = 64;
    constexpr uint8_t BYTE_COUNT = 31;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ZERO = 640;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ONE = 320;
    constexpr uint64_t ONE_MICRO_SEC = 1000000;
    constexpr uint16_t SAMPLE_ERROR_CORRECTION = 6;
    constexpr uint64_t LEADER_MICRO_SEC = 2500000;
    constexpr uint64_t LEADER_MICRO_SEC_ERROR_CORRECTION = 200;

    constexpr uint64_t COUNT_LEADER_MICRO_SEC( const uint64_t& leader_count)
    {
        return leader_count * (BIT_STREAM_LENGHT-1) * MICRO_SEC_FOR_BIT_ONE +
            leader_count * MICRO_SEC_FOR_BIT_ZERO;
    }

    constexpr bool IS_LEADER_RECEIVED( const uint64_t& leader_count)
    {
        return (COUNT_LEADER_MICRO_SEC(leader_count) + LEADER_MICRO_SEC_ERROR_CORRECTION) > LEADER_MICRO_SEC;
    }
    
class DecodeWave final
{
private:
    IReader::Ptr audio_reader_{nullptr};
    int64_t upper_audio_samples_for_bit_1_{0}; //Ideal Value 19
    int64_t lower_audio_samples_for_bit_1_{0}; //Ideal Value 13
    int64_t upper_audio_samples_for_bit_0_{0}; //Ideal Value 33
    int64_t lower_audio_samples_for_bit_0_{0}; //Ideal Value 27

    uint16_t error_correction_{SAMPLE_ERROR_CORRECTION};
public:
    explicit DecodeWave(const uint16_t error_correction = SAMPLE_ERROR_CORRECTION ) noexcept;
    ~DecodeWave();
    DecodeWave(const DecodeWave& decode_wave) noexcept = delete;
    DecodeWave& operator=(const DecodeWave& other) = delete;
    DecodeWave(DecodeWave&& decode_wave) noexcept;
    DecodeWave& operator=(DecodeWave&& other);

    IReader::Ptr GetReader() const;

    bool IsReaderCreated() const noexcept;
    bool OpenFile(std::string& file_name) noexcept;

    void DumpAudioInfo() const noexcept;

    std::string DecodeToMessage(const int8_t& channel) const noexcept;
    std::string DecodeToBitStream(const int8_t& channel) const noexcept;
private:
    void CreateReaderFor(std::string& extension);
    uint16_t Process(std::deque<bool>& bit_values)const;

    void CalculateLimit()noexcept;

    inline bool IsZeroBitReceived(const int64_t& value)const;
    inline bool IsOneBitReceived(const int64_t& value)const;

    int16_t* GetData() const;
};
} // decode_wave
#endif //DECODE_WAVE_HPP