#include <DecodeWave.hpp>
#include <string>
#include <iostream>
#include <sstream>

static void show_usage(std::string applicaton_name)
{
    std::cerr << "Usage: " <<std::endl
                << "    " << applicaton_name << " -a audio_file.wav -c channel_number<optional>" << std::endl
                << "Options:" << std::endl
                << "    -h,--help       Show this help message" << std::endl
                << "    -a,--audio      <path to .wav audio file>" << std::endl
                << "    -c,--channel    channel to decode"
                << std::endl;
}

int main(int argc, char* argv[])
{
    if (argc < 3) {
        show_usage(argv[0]);
        return 1;
    }

    std::string file_path{};
    uint16_t channel{0};
    bool is_channel_provided = false;
    for (int i = 1; i < argc; ++i)
    {
        std::string arg = argv[i];
        if ((arg == "-h") || (arg == "--help"))
        {
            show_usage(argv[0]);
            return 0;
        } 
        else if ((arg == "-a") || (arg == "--audio"))
        {
            if (i + 1 < argc)
            { 
                file_path = argv[++i];
            }
            else
            { 
                std::cerr << "-a,--audio option requires one argument." << std::endl;
                return 1;
            }  
        }
        else if ((arg == "-c") || (arg == "--channel"))
        {
            if (i + 1 < argc)
            { 
                std::istringstream(argv[++i]) >> channel;
                is_channel_provided = true;
            }
            else
            { 
                std::cerr << "-c,--channel option requires one argument." << std::endl;
                return 1;
            }  
        }
        else
        {
            show_usage(argv[0]);
            return 1;
        }
    }

    using namespace decode_wave;
    std::shared_ptr<DecodeWave> decode_wave = std::make_shared<DecodeWave>();
    auto return_value = decode_wave->OpenFile(file_path);
    if ( return_value)
    {
        std::cout << "==========================Audio file infromation.==========================" <<std::endl;
        decode_wave->DumpAudioInfo();
        if ( is_channel_provided)
        {
            if (decode_wave->GetReader()->HasChannel(channel))
            {
                std::cout << "==================================Message==================================" <<std::endl;
                std::string result = decode_wave->DecodeToMessage(channel);
                std::cout << result <<std::endl;
            }
            else
            {
                std::cerr << "==================================Error==================================" <<std::endl;
                std::cerr << "Channel " << channel << " is not present in the audio file. Possible range is [" << 0 << " - " << decode_wave->GetReader()->Channels() - 1 << "]" << std::endl;
            }
        }
    }
    else
    {
        std::cerr << "Cannot open audio file. Please check the file and its contents." <<std::endl;
    }
    return 0;
}