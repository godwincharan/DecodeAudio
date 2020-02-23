#ifndef BIT_STREAM_DECODER_HPP
#define BIT_STREAM_DECODER_HPP

#include "Decoder.hpp"

namespace decode_wave
{
class BitStreamDecoder final : public Decoder
{
public:
    explicit BitStreamDecoder()noexcept = default;
    ~BitStreamDecoder() = default;
    BitStreamDecoder(const BitStreamDecoder& bit_stream_decoder) noexcept = delete;
    BitStreamDecoder& operator=(const BitStreamDecoder& other) = delete;
    BitStreamDecoder(BitStreamDecoder&& bit_stream_decoder) noexcept = delete;
    BitStreamDecoder& operator=(BitStreamDecoder&& other) = delete;

    std::string Decode(const int16_t* sample_data, const int16_t& channels, const int64_t& overall_samples, const int8_t& channel) const noexcept override;
};
} // decode_wave
#endif //BIT_STREAM_DECODER_HPP