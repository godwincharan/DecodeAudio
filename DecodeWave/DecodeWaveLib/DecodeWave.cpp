#include "DecodeWave.hpp"
#include "ReaderFactory.hpp"
#include "Utility.hpp"
#include "Logger.hpp"
#include <string>
#include <vector>
#include <cmath>

namespace decode_wave
{
 DecodeWave::DecodeWave() noexcept
 {
 }

DecodeWave::~DecodeWave()
{
    audio_reader_ = nullptr;
}

void DecodeWave::CalculateLimit()noexcept
{
    if(audio_reader_)
    {
        const auto sample_rate = audio_reader_->SampleRate();
        auto audio_samples_for_bit_1 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ONE / ONE_MICRO_SEC * 1.0F);
        auto audio_samples_for_bit_0 = std::floor(sample_rate * MICRO_SEC_FOR_BIT_ZERO / ONE_MICRO_SEC * 1.0F);

        upper_audio_samples_for_bit_1_ = audio_samples_for_bit_1 + ERROR_THRESHOULD;
        lower_audio_samples_for_bit_1_ = audio_samples_for_bit_1 - ERROR_THRESHOULD;
        
        upper_audio_samples_for_bit_0_ = audio_samples_for_bit_0 + ERROR_THRESHOULD;
        lower_audio_samples_for_bit_0_ = audio_samples_for_bit_0 - ERROR_THRESHOULD;
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
            return nullptr;;
        }
        else
        {
            return sample_data;
        }
    }
    return nullptr;
}

std::string DecodeWave::Decode(const int8_t& channel) const noexcept
{
    std::string result{""};
     if(audio_reader_)
    {
        int16_t* sample_data = GetData();
        auto channels = audio_reader_->Channels();
        auto overall_samples = audio_reader_->OverallSamples();
        
        auto fill_message_func = [&](const int8_t& channel, std::string& message , std::string& checksum_message)
        {
        };
        std::string message{""};
        std::string checksum_message{""};
        fill_message_func(channel,message, checksum_message);
        result += message;
        result += std::string("\\n") + checksum_message;
        delete[] sample_data;
    }
    return result;
}

uint16_t DecodeWave::Process(std::vector<bool>& bit_values) const
{
    uint16_t result = 0x00;
    if (bit_values.size() == BIT_STREAM_LENGHT)
    {
        auto false_lambda = [](const bool& value)
        {
            return !value;
        };

        auto true_lambda = [](const bool& value)
        {
            return value;
        };

        if( false_lambda(bit_values[0]) && 
            true_lambda(bit_values[BIT_STREAM_LENGHT-1]) &&
            true_lambda(bit_values[BIT_STREAM_LENGHT-2]))
        {
            for( int i = 1; i < BIT_STREAM_LENGHT-2; i++)
            {
                result |= bit_values[i] << (i-1);
            }
        }
        bit_values.clear();
    }
    return result;
}
} // decode_wave