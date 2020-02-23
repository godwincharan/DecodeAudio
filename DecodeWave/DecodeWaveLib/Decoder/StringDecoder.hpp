#ifndef STRING_DECODER_HPP
#define STRING_DECODER_HPP

#include "Decoder.hpp"
#include <deque>

namespace decode_wave
{
    constexpr uint8_t START_ID_ONE_VALUE = 0x42;
    constexpr uint8_t START_ID_TWO_VALUE = 0x03;
    constexpr uint8_t END_ID_VALUE = 0x00;
    constexpr uint8_t ID_BYTE_COUNT = 0x02;
    constexpr uint8_t MESSAGE_COUNT = 64;
    constexpr uint8_t BYTE_COUNT = 31;

    constexpr uint64_t LEADER_MICRO_SEC = 2500000;
    constexpr uint64_t LEADER_MICRO_SEC_ERROR_CORRECTION = 200;
    constexpr uint8_t BIT_STREAM_LENGHT = 11;


    constexpr uint64_t COUNT_LEADER_MICRO_SEC( const uint64_t& leader_count)
    {
        return leader_count * (BIT_STREAM_LENGHT-1) * MICRO_SEC_FOR_BIT_ONE +
            leader_count * MICRO_SEC_FOR_BIT_ZERO;
    }

    constexpr bool IS_LEADER_RECEIVED( const uint64_t& leader_count)
    {
        return (COUNT_LEADER_MICRO_SEC(leader_count) + LEADER_MICRO_SEC_ERROR_CORRECTION) > LEADER_MICRO_SEC;
    }
class StringDecoder final : public Decoder
{
public:
    explicit StringDecoder()noexcept = default;
    ~StringDecoder() = default;
    StringDecoder(const StringDecoder& bit_stream_decoder) noexcept = delete;
    StringDecoder& operator=(const StringDecoder& other) = delete;
    StringDecoder(StringDecoder&& decoder) noexcept = delete;
    StringDecoder& operator=(StringDecoder&& other) = delete;

    std::string Decode(const int16_t* sample_data, const int16_t& channels, const int64_t& overall_samples, const int8_t& channel) const noexcept override;
private:
    uint16_t Process(std::deque<bool>& bit_values)const;
};
} // decode_wave
#endif //STRING_DECODER_HPP