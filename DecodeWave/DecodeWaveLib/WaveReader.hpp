#ifndef WAVE_READER_HPP
#define WAVE_READER_HPP

#include "IReader.hpp"
#include "dr_wav.h"

namespace decode_wave
{
class WaveReader final: public IReader
{
private:
    drwav wav_;
    bool is_valid_{false};
public:
    using Ptr = std::shared_ptr<WaveReader>;
    explicit WaveReader() noexcept;
    ~WaveReader();

    bool OpenFile(const std::string& file_name) override;

    uint64_t GetSamples16(const int64_t& no_of_samples, int16_t* sample_data) override;
    uint64_t GetSamples24(const int64_t& no_of_samples, int32_t* sample_data) override;
    uint64_t GetSamples32(const int64_t& no_of_samples, int32_t* sample_data) override;
    
    void Info() const noexcept override;
    uint64_t TotalSamples() const noexcept override;
    uint16_t Channels() const noexcept override;
};
} // decode_wave
#endif //WAVE_READER_HPP

