# DecodeWave

blogger::Log::Get().log(std::string("Channels: ") + std::to_string(wav_.channels));
logger::Log::Get().log(std::string("Sample Rate: ") + std::to_string(wav_.sampleRate));
logger::Log::Get().log(std::string("Total Samples: ") + std::to_string(wav_.totalPCMFrameCount));
logger::Log::Get().log(std::string("Bit Depth: ") + std::to_string(wav_.bitsPerSample));
if (2 == wav_.channels)
{
// auto samples_in_320_micro_sec = wav_.sampleRate * 320.0 / 1000000.0;
// logger::Log::Get().log(std::string("samples_in_320_micro_sec: ") + std::to_string(samples_in_320_micro_sec));

auto total_data = wav_.totalPCMFrameCount * wav_.channels;
int16_t* pSampleData = (int16_t*)malloc((size_t)total_data * sizeof(int16_t));
drwav_read_pcm_frames_s16(&wav_, wav_.totalPCMFrameCount, pSampleData);

int16_t sample_value = 0;
int64_t old_count = 0;
int64_t old_value_logged = 0;
int64_t change_count =0;
for(int64_t index = 0, count =0 ; index < total_data; index+=2, count++)
{
    if (sample_value != pSampleData[index])
    {
        // logger::Log::Get().log(std::string("Changing from :") + std::to_string(sample_value) + std::string(" to : ")+ std::to_string(pSampleData[index]) + std
        // ::string(" count diff : ")+std::to_string(count-old_count));
        if( count-old_count == 28) 
        {
            if ( old_value_logged != 0){
                logger::Log::Get().log(std::string("Change Count : ") + std::to_string(change_count));
                old_value_logged = 0;
                change_count++;
            }
            logger::Log::Get().logcontinous(std::string("0"));
            
        }
        else if( count-old_count == 14) 
        {
            if ( old_value_logged != 1){
                // logger::Log::Get().log(std::string(" Change Count : ") + std::to_string(change_count));
                old_value_logged = 1;
                //change_count++;
            }
            logger::Log::Get().logcontinous(std::string("1"));
            
        }
        sample_value = pSampleData[index];
        old_count = count;
    }
    //std::stringstream stream;
    //stream << std::dec << pSampleData[index];
    //stream << "0x" << std::setfill ('0') << std::setw(sizeof(int16_t)*2) << std::hex << pSampleData[index];
    //logger::Log::Get().log(std::to_string(count) + std::string(" : ")+ stream.str());

    // //if ( count == 7813 )
    // if ( count == 8000 )
    // {
    //     break;

    // }
}
// At this point pSampleData contains every decoded sample as signed 32-bit PCM.