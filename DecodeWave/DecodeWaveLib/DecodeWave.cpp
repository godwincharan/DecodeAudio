#include "DecodeWave.hpp"
#include "ReaderFactory.hpp"
#include "Utility.hpp"
#include "Logger.hpp"
#include <string>
#include <cmath>

namespace decode_wave
{
 DecodeWave::DecodeWave(const uint16_t error_correction) noexcept
 :error_correction_{error_correction}
 {
 }

DecodeWave::~DecodeWave()
{
    audio_reader_ = nullptr;
}

IReader::Ptr DecodeWave::GetReader() const
{
    return audio_reader_;
}

void DecodeWave::CalculateLimit()noexcept
{
    if(audio_reader_)
    {
        const auto sample_rate = audio_reader_->SampleRate();
        auto audio_samples_for_bit_1 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ONE / ONE_MICRO_SEC * 1.0F);
        auto audio_samples_for_bit_0 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ZERO / ONE_MICRO_SEC * 1.0F);

        upper_audio_samples_for_bit_1_ = audio_samples_for_bit_1 + error_correction_;
        lower_audio_samples_for_bit_1_ = audio_samples_for_bit_1 - error_correction_;
        
        upper_audio_samples_for_bit_0_ = audio_samples_for_bit_0 + error_correction_;
        lower_audio_samples_for_bit_0_ = audio_samples_for_bit_0 - error_correction_;
    }
}

bool DecodeWave::IsZeroBitReceived(const int64_t& value)const
{
    return Utility::IsWithin(lower_audio_samples_for_bit_0_, upper_audio_samples_for_bit_0_, value);
}

bool DecodeWave::IsOneBitReceived(const int64_t& value)const
{
    return Utility::IsWithin(lower_audio_samples_for_bit_1_, upper_audio_samples_for_bit_1_, value);
}

void DecodeWave::CreateReaderFor(std::string& extension)
{
    audio_reader_ = ReaderFactory::Get().GetReader(extension);
}
 
bool DecodeWave::IsReaderCreated() const noexcept
{
    return audio_reader_ != nullptr;
}

bool DecodeWave::OpenFile(std::string& file_name) noexcept
{
    bool return_value = false;
    
    audio_reader_ = nullptr;
    auto pos = file_name.find_last_of(".");
    if(std::string::npos != pos)
    {
        auto extension = file_name.substr(pos);
        CreateReaderFor(extension);
    }

    if(audio_reader_)
    {
        return_value = audio_reader_->OpenFile(file_name);
        if(return_value)
        {
            CalculateLimit();
        }
    }
    return return_value;
}

void DecodeWave::DumpAudioInfo() const noexcept
{
    if(audio_reader_)
    {
        return audio_reader_->Info();
    }
}

int16_t* DecodeWave::GetData() const
{
    if(audio_reader_)
    {
        auto overall_samples = audio_reader_->OverallSamples();
        auto total_samples = audio_reader_->TotalSamples();
        int16_t* sample_data = new int16_t[overall_samples];
        auto read = audio_reader_->GetSamples16(total_samples, sample_data);
        if (read != total_samples)
        {
            logger::Log::Get().log(std::string("Not able to read all data.") + 
                std::string("To Read:") + std::to_string(total_samples) + std::string(" ") + 
                std::string("Read:") + std::to_string(read));
            delete[] sample_data;
            return nullptr;
        }
        else
        {
            return sample_data;
        }
    }
    return nullptr;
}

std::string DecodeWave::DecodeToMessage(const int8_t& channel) const noexcept
{
    std::string result{""};
    if(audio_reader_ && audio_reader_->HasChannel(channel))
    {
        int16_t* sample_data = GetData();
        auto channels = audio_reader_->Channels();
        auto overall_samples = audio_reader_->OverallSamples();
        
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
        delete[] sample_data;
    }
    return result;
}

std::string DecodeWave::DecodeToBitStream(const int8_t& channel) const noexcept
{
    std::string result{""};
    if(audio_reader_ && audio_reader_->HasChannel(channel))
    {
        int16_t* sample_data = GetData();
        auto channels = audio_reader_->Channels();
        auto overall_samples = audio_reader_->OverallSamples();
        
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
        delete[] sample_data;
    }
    return result;
}

uint16_t DecodeWave::Process(std::deque<bool>& bit_values) const
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