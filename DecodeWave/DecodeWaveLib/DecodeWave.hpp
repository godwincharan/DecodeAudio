#ifndef DECODE_WAVE_HPP
#define DECODE_WAVE_HPP

#include "AudioReader/ReaderFactory.hpp"
#include <string>
#include <Logger.hpp>

namespace decode_wave
{
template<class T>
class DecodeWave final
{
private:
    IReader::Ptr audio_reader_{nullptr};
    std::unique_ptr<T> decoder_{nullptr};
public:
    explicit DecodeWave() noexcept;
    ~DecodeWave();
    DecodeWave(const DecodeWave& decode_wave) noexcept = delete;
    DecodeWave& operator=(const DecodeWave& other) = delete;
    DecodeWave(DecodeWave&& decode_wave) noexcept;
    DecodeWave& operator=(DecodeWave&& other);

    IReader::Ptr GetReader() const;

    bool IsReaderCreated() const noexcept;
    bool OpenFile(std::string& file_name) noexcept;

    void DumpAudioInfo() const noexcept;

    void SetErrorCorrection(const uint16_t& error_correction) noexcept;
    std::string Decode(const int8_t& channel) const noexcept;
private:
    void CreateReaderFor(std::string& extension);

    inline bool IsZeroBitReceived(const int64_t& value)const;
    inline bool IsOneBitReceived(const int64_t& value)const;

    int16_t* GetData() const;
};

template<class T>
DecodeWave<T>::DecodeWave() noexcept
{
    decoder_ = std::make_unique<T>();
}

template<class T>
DecodeWave<T>::~DecodeWave()
{
    audio_reader_ = nullptr;
    decoder_ = nullptr;
}

template<class T>
DecodeWave<T>::DecodeWave(DecodeWave&& other) noexcept:
audio_reader_{std::move(other.audio_reader_)},
decoder_{std::move(other.decoder_)}
{
}

template<class T>
DecodeWave<T>& DecodeWave<T>::operator=(DecodeWave&& other)
{
    audio_reader_ = std::move(other.audio_reader_);
    decoder_ = std::move(other.decoder_);
    return *this;
}

template<class T>
IReader::Ptr DecodeWave<T>::GetReader() const
{
    return audio_reader_;
}

template<class T>
void DecodeWave<T>::CreateReaderFor(std::string& extension)
{
    audio_reader_ = ReaderFactory::Get().GetReader(extension);
}
 
template<class T>
bool DecodeWave<T>::IsReaderCreated() const noexcept
{
    return audio_reader_ != nullptr;
}

template<class T>
bool DecodeWave<T>::OpenFile(std::string& file_name) noexcept
{
    bool return_value = false;
    
    audio_reader_ = nullptr;
    auto pos = file_name.find_last_of(".");
    if(std::string::npos != pos)
    {
        auto extension = file_name.substr(pos);
        CreateReaderFor(extension);
    }

    if(audio_reader_ && decoder_)
    {
        return_value = audio_reader_->OpenFile(file_name);
        if(return_value)
        {
            decoder_->CalculateLimit(audio_reader_->SampleRate());
        }
    }
    return return_value;
}

template<class T>
void DecodeWave<T>::DumpAudioInfo() const noexcept
{
    if(audio_reader_)
    {
        return audio_reader_->Info();
    }
}

template<class T>
int16_t* DecodeWave<T>::GetData() const
{
    if(audio_reader_)
    {
        auto overall_samples = audio_reader_->OverallSamples();
        auto total_samples = audio_reader_->TotalSamples();
        int16_t* sample_data = new int16_t[overall_samples];
        auto read = audio_reader_->GetSamples(total_samples, sample_data);
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

template<class T>
void DecodeWave<T>::SetErrorCorrection(const uint16_t& error_correction) noexcept
{
    if (decoder_)
    {
        decoder_->SetErrorCorrection(error_correction);
    }

}

template<class T>
std::string DecodeWave<T>::Decode(const int8_t& channel) const noexcept
{
    std::string result{""};
    if( decoder_ && audio_reader_ && audio_reader_->HasChannel(channel))
    {
        int16_t* sample_data = GetData();
        auto channels = audio_reader_->Channels();
        auto overall_samples = audio_reader_->OverallSamples();
        
        result+= decoder_->Decode(sample_data,channels,overall_samples,channel);
        delete[] sample_data;
    }
    return result;
}
} // decode_wave
#endif //DECODE_WAVE_HPP