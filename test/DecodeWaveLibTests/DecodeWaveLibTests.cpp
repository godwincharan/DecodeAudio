#include <gtest/gtest.h>
#include <DecodeWave.hpp>
#include <iostream>

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
}