//
// Created by demon1999 on 07.06.18.
//
#include <string>
#include <cstring>
#include <gtest/gtest.h>

#include "encoder.h"
#include "decoder.h"

TEST(correctness, empty_string)
{
    std::string s;
    encoder my_encoder;
    for (int i = 0; i < 10; i++)
        my_encoder.count_frequencies(s.data(), s.data() + s.size());
    my_encoder.put_dictionary();
    std::string code = my_encoder.encode_text(s.data(), s.data() + s.size());
    for (int i = 0; i < 10; i++)
        code += my_encoder.encode_text(s.data(), s.data() + s.size());
    decoder my_decoder;
    std::string decode;
    for (int i = 0; i < code.size(); i++) {
        decode += my_decoder.decode_text(code.data() + i, code.data() + i + 1);
    }
    EXPECT_EQ(decode, s);
}

/*
namespace
{
    unsigned const number_of_iterations = 10;
    size_t const number_of_multipliers = 1000;

    int myrand()
    {
        int val = rand() - RAND_MAX / 2;
        if (val != 0)
            return val;
        else
            return 1;
    }
}

TEST(correctness, mul_div_randomized)
{
    for (unsigned itn = 0; itn != number_of_iterations; ++itn)
    {
        std::vector<int> multipliers;

        for (size_t i = 0; i != number_of_multipliers; ++i)
            multipliers.push_back(myrand());

        big_integer accumulator = 1;

        for (size_t i = 0; i != number_of_multipliers; ++i)
            accumulator *= multipliers[i];

        std::random_shuffle(multipliers.begin(), multipliers.end());

        for (size_t i = 1; i != number_of_multipliers; ++i)
            accumulator /= multipliers[i];

        EXPECT_TRUE(accumulator == multipliers[0]);
    }
}
*/