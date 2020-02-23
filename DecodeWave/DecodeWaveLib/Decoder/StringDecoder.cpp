#include "StringDecoder.hpp"
#include "../Utility.hpp"

#include <Logger.hpp>

namespace decode_wave
{
std::string StringDecoder::Decode(const int16_t* sample_data, const int16_t& channels, const int64_t& overall_samples, const int8_t& channel) const noexcept
{
    std::string result{""};
    if(sample_data == nullptr)
    {
        return result;
    }

    auto fill_message_func = [&](const int8_t& channel, std::string& message)
    {
        std::deque<bool> bit_values;
        int64_t sample_count = 0;
        int64_t last_sample_count = 0;
        
        bool old_sign = false;
        int64_t leader_count = 0;

        uint16_t id_byte_count = 0;
        uint8_t byte_count = 0;
        uint8_t message_count = 0;
        uint16_t checksum = 0;
        bool is_all_received = false;
        auto reset_counter_func = [&]
        {
            logger::Log::Get().log_info(std::string("All ") + std::to_string(message_count) + " messages received. Reset the counters.");
            id_byte_count = 0;
            byte_count = 0;
            message_count = 0;
            is_all_received= false;
        };
        for(int64_t sample_index = channel ; sample_index < overall_samples; sample_index += channels)
        {
            auto sample_value = sample_data[sample_index];
            bool new_sign = (sample_value & 0x8000) == 0x8000;
            if (old_sign != new_sign)
            {
                old_sign = new_sign;

                auto samples_between_sign_change = sample_count - last_sample_count;
                last_sample_count = sample_count;
                if( IsZeroBitReceived(samples_between_sign_change)) 
                {
                    bit_values.push_back(false);
                }
                else if( IsOneBitReceived(samples_between_sign_change))
                {
                    bit_values.push_back(true);
                }

                if (bit_values.size() == BIT_STREAM_LENGHT)
                {
                    uint16_t value = Process(bit_values);
                    if ( IS_LEADER_RECEIVED(leader_count))
                    {
                        if(message_count == MESSAGE_COUNT)
                        {
                            is_all_received = true;
                        }
                        else if (is_all_received)
                        {
                            if (value == END_ID_VALUE){
                                reset_counter_func();
                            }
                            else
                            {
                                logger::Log::Get().log_error(std::string("End ID is not received."));
                            }
                        }
                        else if( id_byte_count != ID_BYTE_COUNT )
                        {
                            if( value == START_ID_ONE_VALUE || value == START_ID_TWO_VALUE)
                            {
                                id_byte_count++;
                            }
                        }
                        else if ( ++byte_count == BYTE_COUNT)
                        {
                            if ( value != (checksum & 0x0ff) )
                            {
                                logger::Log::Get().log_error("Checksum Mismatch. (Checksum:" + Utility::GetHexString(value) + "!= Cal Checksum:" + Utility::GetHexString(checksum) + ")");
                            }
                            byte_count = 0;
                            checksum = 0;
                            message_count++;
                        }
                        else
                        {
                            char char_value = value;
                            message += char_value;
                            checksum += value;
                        }
                    }
                    else if (value == 0xFF)
                    {
                        leader_count++;
                    }
                }
            }
            sample_count++;
        }
    };
    std::string message{""};
    fill_message_func(channel, message);
    result += message;

    return result;
}

uint16_t StringDecoder::Process(std::deque<bool>& bit_values) const
{
    uint16_t result = 0x00;
    if (bit_values.size() == BIT_STREAM_LENGHT)
    {
        if( !bit_values[0] && bit_values[BIT_STREAM_LENGHT-1] && bit_values[BIT_STREAM_LENGHT-2])
        {
            for( int i = 1; i < BIT_STREAM_LENGHT-2; i++)
            {
                result |= bit_values[i] << (i-1);
            }
            bit_values.clear();
        }
        else
        {
            bit_values.pop_front();
        }
    }
    return result;
}
} // decode_wave