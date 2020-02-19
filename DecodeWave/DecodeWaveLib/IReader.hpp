#ifndef I_READER_HPP
#define I_READER_HPP

#include <memory>

namespace decode_wave
{
class IReader
{
public:
    using Ptr = std::shared_ptr<IReader>;
    explicit IReader() noexcept {}
    virtual ~IReader(){}

    virtual bool OpenFile(const std::string& file_name) = 0;

    virtual uint64_t GetSamples16(const uint64_t& no_of_samples, int16_t* sample_data) = 0;
    virtual uint64_t GetSamples24(const uint64_t& no_of_samples, int32_t* sample_data) = 0;
    virtual uint64_t GetSamples32(const uint64_t& no_of_samples, int32_t* sample_data) = 0;

    virtual void Info() const noexcept = 0;
    virtual uint64_t TotalSamples() const noexcept = 0;
    virtual uint16_t Channels() const noexcept = 0;
    virtual uint64_t SampleRate() const noexcept =0;
    virtual uint64_t OverallSamples() const noexcept = 0;
};
} // decode_wave
#endif //I_READER_HPP

