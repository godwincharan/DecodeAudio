#ifndef DECODER_HPP
#define DECODER_HPP

#include <string>

namespace decode_audio
{
    constexpr uint64_t ONE_MICRO_SEC = 1000000;
    constexpr uint16_t SAMPLE_ERROR_CORRECTION = 6;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ZERO = 640;
    constexpr uint64_t MICRO_SEC_FOR_BIT_ONE = 320;
class Decoder
{
protected:
    int64_t upper_audio_samples_for_bit_1_{0}; //Ideal Value 19
    int64_t lower_audio_samples_for_bit_1_{0}; //Ideal Value 13
    int64_t upper_audio_samples_for_bit_0_{0}; //Ideal Value 33
    int64_t lower_audio_samples_for_bit_0_{0}; //Ideal Value 27

    uint16_t error_correction_{SAMPLE_ERROR_CORRECTION};

public:
    explicit Decoder()noexcept = default;
    ~Decoder() = default;
    Decoder(const Decoder& bit_stream_decoder) noexcept = delete;
    Decoder& operator=(const Decoder& other) = delete;
    Decoder(Decoder&& decoder) noexcept = delete;
    Decoder& operator=(Decoder&& other) = delete;

    bool IsZeroBitReceived(const int64_t& value)const;
    bool IsOneBitReceived(const int64_t& value)const;

    virtual void CalculateLimit(const uint64_t& sample_rate)noexcept;

    void SetErrorCorrection(const uint16_t& error_correction) noexcept;
    virtual std::string Decode(const int16_t* sample_data, const int16_t& channels, const int64_t& overall_samples, const int8_t& channel) const noexcept = 0;
};
} // decode_audio
#endif //DECODER_HPP