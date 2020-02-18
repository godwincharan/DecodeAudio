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

    virtual uint64_t GetSamples16(const int64_t& no_of_samples, uint16_t* sample_data) = 0;
    virtual uint64_t GetSamples24(const int64_t& no_of_samples, uint32_t* sample_data) = 0;
    virtual uint64_t GetSamples32(const int64_t& no_of_samples, uint32_t* sample_data) = 0;

    virtual void Info() const noexcept = 0;
};
} // decode_wave
#endif //I_READER_HPP

