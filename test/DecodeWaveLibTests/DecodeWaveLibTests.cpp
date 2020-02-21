#include <gtest/gtest.h>
#include <DecodeWave.hpp>
#include <iostream>
#include <fstream>

TEST(DecodeWaveLibTests, OpenFile_Empty){
    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    std::string file_path("");
    auto return_value = decode_wave->OpenFile(file_path);
    EXPECT_EQ(false,return_value);
}

TEST(DecodeWaveLibTests, OpenFile_DummyFile){
    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    std::string file_path("myFile.wav");
    auto return_value = decode_wave->OpenFile(file_path);
    EXPECT_EQ(false,return_value);

    return_value = decode_wave->IsReaderCreated();
    EXPECT_EQ(true,return_value);
}

TEST(DecodeWaveLibTests, OpenFile_ProperFile){
    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    std::string file_path("/Users/Charan/Documents/GitHub/DecodeWave/ProblemStatement/Decoding_WaveFiles/file_1.wav");
    auto return_value = decode_wave->OpenFile(file_path);
    EXPECT_EQ(true,return_value);

    return_value = decode_wave->IsReaderCreated();
    EXPECT_EQ(true,return_value);
}

TEST(DecodeWaveLibTests, Decode_ProperFile1){
    std::string wav_file_path{"file_1.wav"};
    std::string message_file_path{"file_1_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);

    std::string result = decode_wave->DecodeToMessage(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile2){
    std::string wav_file_path{"file_2.wav"};
    std::string message_file_path{"file_2_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);

    std::string result = decode_wave->DecodeToMessage(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile3){
    std::string wav_file_path{"file_3.wav"};
    std::string message_file_path{"file_3_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);

    std::string result = decode_wave->DecodeToMessage(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile_BitStream1){
     std::string wav_file_path{"file_1.wav"};
    std::string bit_stream_file_path{"file_1_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);
    std::string result = decode_wave->DecodeToBitStream(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile_BitStream2){
     std::string wav_file_path{"file_2.wav"};
    std::string bit_stream_file_path{"file_2_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);
    std::string result = decode_wave->DecodeToBitStream(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile_BitStream3){
     std::string wav_file_path{"file_3.wav"};
    std::string bit_stream_file_path{"file_3_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    auto return_value = decode_wave->OpenFile(wav_file_path);
    std::string result = decode_wave->DecodeToBitStream(0);

    EXPECT_EQ(buffer.str(),result);
}