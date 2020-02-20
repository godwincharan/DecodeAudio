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

TEST(DecodeWaveLibTests, Decode_ProperFile){
    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    std::string file_path("/Users/Charan/Documents/GitHub/DecodeWave/ProblemStatement/Decoding_WaveFiles/file_1.wav");
    auto return_value = decode_wave->OpenFile(file_path);

    std::string result = decode_wave->DecodeToMessage(0);
    EXPECT_EQ(std::string("It was the White Rabbit, trotting slowly back again, and looking anxiously about as it went, as if it had lost something; \
and she heard it muttering to itself `The Duchess! The Duchess! Oh my dear paws! Oh my fur and whiskers! She'll get me executed, as sure as ferrets are ferrets! \
Where can I have dropped them, I wonder?' Alice guessed in a moment that it was looking for the fan and the pair of white kid gloves, and she very good-naturedly \
began hunting about for them, but they were nowhere to be seen--everything seemed to have changed since her swim in the pool, and the great hall, with the glass \
table and the little door, had vanished completely.\nVery soon the Rabbit noticed Alice, as she went hunting about, and called out to her in an angry tone, \
`Why, Mary Ann, what are you doing out here? Run home this moment, and fetch me a pair of gloves and a fan! Quick, now!' And Alice was so much frightened \
that she ran off at once in the direction it pointed to, without trying to explain the mistake it had made.\n\n`He took me for his housemaid,' she said to herself as she ran. \
`How surprised he'll be when he finds out who I am! But I'd better take him his fan and gloves--that is, if I can find them.' As she said this, \
she came upon a neat little house, on the door of which was a bright brass plate with the name `W. RABBIT' engraved upon it. She went in without knocking, \
and hurried upstairs, in great fear lest she should meet the real Mary Ann, and be turned out of the house before she had found the fan and gloves.\n\n`How queer \
it seems,' Alice said to herself, `to be going messages for a rabbit! I suppose Dinah'll be sending me on messages next!' And she began fancying the sort of thing \
that would happen: `\"Miss Alice! Come here directly, and get ready for your walk!\" \"Coming in a minute, nurse! But I've got to see that the mouse doesn't get out.\" \
Only I don't think,' Alice went on, `that they"),result);
}

TEST(DecodeWaveLibTests, Decode_ProperFile_BitStream){
    std::shared_ptr<decode_wave::DecodeWave> decode_wave = std::make_shared<decode_wave::DecodeWave>();
    std::string file_path("/Users/Charan/Documents/GitHub/DecodeWave/ProblemStatement/Decoding_WaveFiles/file_1.wav");
    auto return_value = decode_wave->OpenFile(file_path);
    std::string result = decode_wave->DecodeToBitStream(0);
    EXPECT_EQ(std::string(""),result);
}