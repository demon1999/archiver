//
// Created by demon1999 on 07.06.18.
//
#include <string>
#include <cstring>
#include <vector>
#include <gtest/gtest.h>

#include "encoder.h"
#include "decoder.h"

namespace {
    void try_string(const std::string &s) {
        encoder my_encoder;
        decoder my_decoder;
        std::string t = my_encoder.encode_string(s);
        t = my_decoder.decode_string(t);
        EXPECT_EQ(s, t);
    }
}

TEST(correctness, empty_string) {
    std::string empty_string;
    try_string(empty_string);

}

TEST(correctness, string_with_same_symbols) {
    std::string string_with_same_symbols = "AAAAAAAAAAAA";
    try_string(string_with_same_symbols);
}

TEST(correctness, string_with_random_symbols) {
    std::string string_with_same_symbols = "My mother is wonderful";
    try_string(string_with_same_symbols);
}

TEST(correctness, big_string_pow_two) {
    std::string big_string_pow_two;
    for (int i = 0; i < 256; i++)
        big_string_pow_two += char('q');
    try_string(big_string_pow_two);
}

TEST(correctness, big_string) {
    std::string big_string;
    for (int i = 0; i < 1000; i++)
        big_string += char(rand() % 128 + 1);
    try_string(big_string);
}