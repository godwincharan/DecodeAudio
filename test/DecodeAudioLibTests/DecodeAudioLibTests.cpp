#include <gtest/gtest.h>
#include <DecodeAudio.hpp>
#include <Decoder/StringDecoder.hpp>
#include <Decoder/BitStreamDecoder.hpp>
#include <iostream>
#include <fstream>

using namespace decode_audio;
TEST(DecodeAudioLibTests, OpenFile_Empty){
    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    std::string file_path("");
    auto return_value = decode_audio->OpenFile(file_path);
    EXPECT_EQ(false,return_value);
}

TEST(DecodeAudioLibTests, OpenFile_DummyFile){
    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    std::string file_path("myFile.wav");
    auto return_value = decode_audio->OpenFile(file_path);
    EXPECT_EQ(false,return_value);

    return_value = decode_audio->IsReaderCreated();
    EXPECT_EQ(true,return_value);
}

TEST(DecodeAudioLibTests, OpenFile_ProperFile){
    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    std::string file_path("file_1.wav");
    auto return_value = decode_audio->OpenFile(file_path);
    EXPECT_EQ(true,return_value);

    return_value = decode_audio->IsReaderCreated();
    EXPECT_EQ(true,return_value);
}

TEST(DecodeAudioLibTests, Decode_ProperFile1){
    std::string wav_file_path{"file_1.wav"};
    std::string message_file_path{"file_1_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);

    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeAudioLibTests, Decode_ProperFile2){
    std::string wav_file_path{"file_2.wav"};
    std::string message_file_path{"file_2_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);
    EXPECT_EQ(true,return_value);

    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeAudioLibTests, Decode_ProperFile3){
    std::string wav_file_path{"file_3.wav"};
    std::string message_file_path{"file_3_message.txt"};
    
    std::ifstream message_file;
    message_file.open(message_file_path);
    std::stringstream buffer;
    buffer << message_file.rdbuf();

    std::shared_ptr<DecodeAudio<StringDecoder>> decode_audio = std::make_shared<DecodeAudio<StringDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);
    EXPECT_EQ(true,return_value);

    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeAudioLibTests, Decode_ProperFile_BitStream1){
     std::string wav_file_path{"file_1.wav"};
    std::string bit_stream_file_path{"file_1_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<DecodeAudio<BitStreamDecoder>> decode_audio = std::make_shared<DecodeAudio<BitStreamDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);
    EXPECT_EQ(true,return_value);
    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeAudioLibTests, Decode_ProperFile_BitStream2){
     std::string wav_file_path{"file_2.wav"};
    std::string bit_stream_file_path{"file_2_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<DecodeAudio<BitStreamDecoder>> decode_audio = std::make_shared<DecodeAudio<BitStreamDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);
    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}

TEST(DecodeAudioLibTests, Decode_ProperFile_BitStream3){
     std::string wav_file_path{"file_3.wav"};
    std::string bit_stream_file_path{"file_3_bit_stream.txt"};
    
    std::ifstream bit_stream_file;
    bit_stream_file.open(bit_stream_file_path);
    std::stringstream buffer;
    buffer << bit_stream_file.rdbuf();

    std::shared_ptr<DecodeAudio<BitStreamDecoder>> decode_audio = std::make_shared<DecodeAudio<BitStreamDecoder>>();
    auto return_value = decode_audio->OpenFile(wav_file_path);
    EXPECT_EQ(true,return_value);
    std::string result = decode_audio->Decode(0);

    EXPECT_EQ(buffer.str(),result);
}