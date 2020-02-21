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
#endif //WAVE_READER_HPP

