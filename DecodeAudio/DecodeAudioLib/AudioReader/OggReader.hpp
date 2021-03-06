#ifndef OGG_READER_HPP
#define OGG_READER_HPP

#include "IReader.hpp"

namespace decode_audio
{
class OggReader final: public IReader
{
private:
    bool is_valid_{false};
public:
    using Ptr = std::shared_ptr<OggReader>;
    explicit OggReader() noexcept = default;
    ~OggReader() = default;
    OggReader(const OggReader& ) = delete;
    OggReader& operator = (const OggReader& ) = delete;

    bool OpenFile(const std::string& file_name) override final;

    uint64_t GetSamples(const uint64_t& no_of_samples, int16_t* sample_data) override final;
    
    void Info() const noexcept override final;
    uint64_t TotalSamples() const noexcept override final;
    int16_t Channels() const noexcept override final;
    uint64_t SampleRate() const noexcept override final;
    uint64_t OverallSamples() const noexcept override final;

    bool HasChannel(const uint16_t& channel) const noexcept override final;
    bool SeekZero() noexcept override final;

};
} // decode_audio
#endif //OGG_READER_HPP

