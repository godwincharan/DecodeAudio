#include "BitStreamDecoder.hpp"

namespace decode_wave
{
std::string BitStreamDecoder::Decode(const int16_t* sample_data, const int16_t& channels, const int64_t& overall_samples, const int8_t& channel) const noexcept
{
    std::string result{""};
    if(sample_data == nullptr)
    {
        return result;
    }
    auto fill_bit_stream_func = [&](const int8_t& channel, std::string& bit_message)
    {
        int64_t sample_count = 0;
        int64_t last_sample_count = 0;
        bool old_sign = false;
        for(int64_t sample_index = channel ; sample_index < overall_samples; sample_index += channels)
        {
            auto sample_value = sample_data[sample_index];
            bool new_sign = (sample_value & 0x8000) == 0x8000;
            //logger::Log::Get().log( std::to_string(sample_count) + std::string(" : ")+ Utility::GetHexString(sample_value) + std::string(": new_sign->") + std::to_string(new_sign) );
            if (old_sign != new_sign)
            {
                old_sign = new_sign;
                auto samples_between_sign_change = sample_count - last_sample_count;
                last_sample_count = sample_count;
                //logger::Log::Get().log(std::string("Sample Changing to :") +  std::to_string(sample_value) + std::string("<---->Samples Between Sign Change : ")+std::to_string(samples_between_sign_change));
                if( IsZeroBitReceived(samples_between_sign_change)) 
                {
                    bit_message += std::string("0");
                }
                else if( IsOneBitReceived(samples_between_sign_change))
                {
                    bit_message += std::string("1");
                }
            }
            sample_count++;
        }
    };
    std::string bit_message{""};
    fill_bit_stream_func(channel, bit_message);
    result += bit_message;
    return result;
}
} // decode_wave