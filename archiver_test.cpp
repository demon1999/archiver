//
// Created by demon1999 on 07.06.18.
//
#include <string>
#include <cstring>
#include <vector>
#include <gtest/gtest.h>

#include "encoder.h"
#include "decoder.h"

TEST(correctness, emptyString) {
    encoder my_encoder;
    decoder my_decoder;
    std::string emptyString;
    std::string encoded = my_encoder.encode_string(emptyString);
    std::string decoded = my_decoder.decode_string(encoded);
    ASSERT_EQ(decoded, emptyString);
}

TEST(correctness, stringOfSameSymbolsTwelveTimesA) {
    std::string stringOfSameSymbolsTwelveTimesA = "AAAAAAAAAAAA";
    encoder my_encoder;
    decoder my_decoder;
    std::string encoded = my_encoder.encode_string(stringOfSameSymbolsTwelveTimesA);
    std::string decoded = my_decoder.decode_string(encoded);
    ASSERT_EQ(decoded, stringOfSameSymbolsTwelveTimesA);
}

TEST(correctness, stringOneSentence) {
    std::string stringOneSentence = "My mother is wonderful";
    encoder my_encoder;
    decoder my_decoder;
    std::string encoded = my_encoder.encode_string(stringOneSentence);
    std::string decoded = my_decoder.decode_string(encoded);
    ASSERT_EQ(decoded, stringOneSentence);
}

TEST(correctness, bigStringOfFixedSymbolsPow2Length) {
    std::string bigStringOfFixedSymbolsPow2Length;
    for (int i = 0; i < 256; i++)
        bigStringOfFixedSymbolsPow2Length += char('q');
    encoder my_encoder;
    decoder my_decoder;
    std::string encoded = my_encoder.encode_string(bigStringOfFixedSymbolsPow2Length);
    std::string decoded = my_decoder.decode_string(encoded);
    ASSERT_EQ(decoded, bigStringOfFixedSymbolsPow2Length);
}

TEST(correctness, bigStringOfRandomSymbols) {
    std::string bigStringOfRandomSymbols;
    for (int i = 0; i < 1000; i++)
        bigStringOfRandomSymbols += char(rand() % 128 + 1);
    encoder my_encoder;
    decoder my_decoder;
    std::string encoded = my_encoder.encode_string(bigStringOfRandomSymbols);
    std::string decoded = my_decoder.decode_string(encoded);
    ASSERT_EQ(decoded, bigStringOfRandomSymbols);
}