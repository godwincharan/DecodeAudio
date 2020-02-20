#include <DecodeWave.hpp>
#include <string>
#include <iostream>

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