#include "DecodeWave.hpp"
#include "Logger.hpp"
#define DR_WAV_IMPLEMENTATION
#include "dr_wav.h"

namespace decode_wave
{
 DecodeWave::DecodeWave() noexcept
 {
 }

DecodeWave::~DecodeWave()
{
}

bool DecodeWave::OpenFile(std::string& file_name)
{
    bool result = false;
    if(!file_name.empty())
    {
        drwav wav_;
        if (drwav_init_file(&wav_, file_name.c_str(), nullptr)) 
        {
            logger::Log::Get().log(std::string("Channels: ") + std::to_string(wav_.channels));
            logger::Log::Get().log(std::string("Sample Rate: ") + std::to_string(wav_.sampleRate));
            logger::Log::Get().log(std::string("Total Samples: ") + std::to_string(wav_.totalPCMFrameCount));
            if (2 == wav_.channels)
            {
               

                auto total_data = wav_.totalPCMFrameCount * wav_.channels;
                int32_t* pSampleData = (int32_t*)malloc((size_t)total_data * sizeof(int32_t));
                drwav_read_pcm_frames_s32(&wav_, wav_.totalPCMFrameCount, pSampleData);

                for(int64_t index = 0, count =0 ; index < total_data; index+= 2, count++)
                {
                    //if ( index )

                }
                // At this point pSampleData contains every decoded sample as signed 32-bit PCM.
                result = false;
            }
            drwav_uninit(&wav_);
        }
    }
    return result;
}
} // decode_wave