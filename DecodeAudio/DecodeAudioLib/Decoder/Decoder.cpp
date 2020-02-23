#include "BitStreamDecoder.hpp"
#include "../Utility.hpp"
#include <cmath>

namespace decode_audio
{
bool Decoder::IsZeroBitReceived(const int64_t& value)const
{
    return Utility::IsWithin(lower_audio_samples_for_bit_0_, upper_audio_samples_for_bit_0_, value);
}

bool Decoder::IsOneBitReceived(const int64_t& value)const
{
    return Utility::IsWithin(lower_audio_samples_for_bit_1_, upper_audio_samples_for_bit_1_, value);
}

void Decoder::CalculateLimit(const uint64_t& sample_rate)noexcept
{
    auto audio_samples_for_bit_1 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ONE / ONE_MICRO_SEC * 1.0F);
    auto audio_samples_for_bit_0 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ZERO / ONE_MICRO_SEC * 1.0F);

    upper_audio_samples_for_bit_1_ = audio_samples_for_bit_1 + error_correction_;
    lower_audio_samples_for_bit_1_ = audio_samples_for_bit_1 - error_correction_;
    
    upper_audio_samples_for_bit_0_ = audio_samples_for_bit_0 + error_correction_;
    lower_audio_samples_for_bit_0_ = audio_samples_for_bit_0 - error_correction_;
}

void Decoder::SetErrorCorrection(const uint16_t& error_correction) noexcept
{
    error_correction_ = error_correction;
}
} // decode_audio