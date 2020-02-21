#ifndef OGG_READER_HPP
#define OGG_READER_HPP

#include "IReader.hpp"

namespace decode_wave
{
class OggReader final: public IReader
{
private:
    bool is_valid_{false};
public:
    using Ptr = std::shared_ptr<OggReader>;
    explicit OggReader() noexcept;
    ~OggReader();

    bool OpenFile(const std::string& file_name) override;

    uint64_t GetSamples(const uint64_t& no_of_samples, int16_t* sample_data) override;
    
    void Info() const noexcept override;
    uint64_t TotalSamples() const noexcept override;
    int16_t Channels() const noexcept override;
    uint64_t SampleRate() const noexcept override;
    uint64_t OverallSamples() const noexcept override;

    bool HasChannel(const uint16_t& channel) const noexcept override;
    bool SeekZero() noexcept override;

};
} // decode_wave
#endif //OGG_READER_HPP

