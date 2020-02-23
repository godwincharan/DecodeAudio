#include "StringDecoder.hpp"
#include "../Utility.hpp"

#include <Logger.hpp>

namespace decode_audio
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

        MessageStructure message_structure{};

        for(int64_t sample_index = channel ; sample_index < overall_samples; sample_index += channels)
        {
            auto sample_value = sample_data[sample_index];
            if (IsSignFlipped(old_sign,sample_value))
            {
                if (IsQueueReady(bit_values, (sample_count - last_sample_count) ))
                {
                    uint16_t value = Process(bit_values);
                    if ( message_structure.IsLeaderReceived(value))
                    {
                        if(message_structure.IsAllMessagesReceived())
                        {
                            message_structure.is_all_received_ = true;
                        }
                        else if (message_structure.is_all_received_)
                        {
                            if (value == END_ID_VALUE){
                                message_structure.reset();
                            }
                            else
                            {
                                logger::Log::Get().log_error(std::string("End ID is not received."));
                            }
                        }
                        else if ( message_structure.IsStartIdReceived(value) && !message_structure.IsAllBytesReceived())
                        {
                            char char_value = value;
                            message += char_value;
                            message_structure.UpdateChecksum(value);
                        }
                        else
                        {
                            message_structure.VerifyChecksum(value);
                        }
                    }
                }
                last_sample_count = sample_count;
            }
            sample_count++;
        }
    };
    std::string message{""};
    fill_message_func(channel, message);
    result += message;

    return result;
}

bool StringDecoder::IsSignFlipped(bool& old_sign, const int16_t& sample_value) const
{
    bool new_sign = (sample_value & 0x8000) == 0x8000;
    if (old_sign  != new_sign)
    {
        old_sign = new_sign;
        return true;
    }
    return false;
}

bool StringDecoder::IsQueueReady(std::deque<bool>& bit_values, const int64_t& sample_change_count)const
{
    auto bit_received = WhichBitReceived(sample_change_count);
    if( BitReceived::BIT_ZERO == bit_received ) 
    {
        bit_values.push_back(false);
    }
    else if( BitReceived::BIT_ONE == bit_received)
    {
        bit_values.push_back(true);
    }

    return (bit_values.size() == BIT_STREAM_LENGHT);
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

void MessageStructure::reset()
{
    logger::Log::Get().log_info(std::string("All ") + std::to_string(message_count_) + " messages received. Reset the counters.");
    leader_count_ = 0;
    id_byte_count_ = 0;
    received_byte_count_ = 0;
    message_count_ = 0;
    checksum_ = 0;
    is_all_received_ = false;
}

bool MessageStructure::IsLeaderReceived(const uint16_t& value)
{
    if ( IS_LEADER_RECEIVED(leader_count_))
    {
        return true;
    }
    else if (value == 0xFF)
    {
        leader_count_++;
    }
    return false;
}

bool MessageStructure::VerifyChecksum(const uint16_t& value)
{
    if( received_byte_count_ == BYTE_COUNT_TO_RECEIVE)
    {
        if( value != (checksum_ & 0x0ff))
        {
            logger::Log::Get().log_error("Checksum Mismatch. (Checksum:" + Utility::GetHexString(value) + "!= Cal Checksum:" + Utility::GetHexString(checksum_) + ")");
        }
        received_byte_count_ = 0;
        checksum_ = 0;
        message_count_++;
        return true;
    }
    return false;
}

void MessageStructure::UpdateChecksum(const uint16_t& value )
{
    checksum_ += value;
    received_byte_count_++;
}

bool MessageStructure::IsAllBytesReceived() const
{
    return (received_byte_count_ == BYTE_COUNT_TO_RECEIVE);
}

bool MessageStructure::IsAllMessagesReceived() const
{
    return (message_count_ == MESSAGE_COUNT_TO_RECEIVE);
}

bool MessageStructure::IsStartIdReceived(const uint16_t& value )
{
    if( id_byte_count_ != ID_BYTE_COUNT_TO_RECEIVE )
    {
        if( value == START_ID_ONE_VALUE || value == START_ID_TWO_VALUE)
        {
            id_byte_count_++;
        }
        return false;
    }
    return true;
}

} // decode_audio