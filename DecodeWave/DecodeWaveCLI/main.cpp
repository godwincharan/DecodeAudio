#include <DecodeWave.hpp>
#include <string>
#include <iostream>

static void show_usage(std::string applicaton_name)
{
    std::cerr << "Usage: " <<std::endl
                << "    " << applicaton_name << " -a audio_file.wav <optional>-c channel_number" << std::endl
                << "Options:" << std::endl
                << "    -h,--help       Show this help message" << std::endl
                << "    -a,--audio      <path to .wav audio file>" << std::endl
                << "    -c,--channel    channel to decode"
                << std::endl;
}

int main(int argc, char* argv[])
{
    using namespace decode_wave;
    std::shared_ptr<DecodeWave> decode_wave = std::make_shared<DecodeWave>();
    std::string file_path("/Users/Charan/Documents/GitHub/DecodeWave/ProblemStatement/Decoding_WaveFiles/file_3.wav");
    auto return_value = decode_wave->OpenFile(file_path);
    if ( return_value)
    {
        std::string result = decode_wave->DecodeToMessage(0);
        std::cout << result <<std::endl;
    }
    return 0;
}