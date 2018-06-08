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
    std::string try_division(const std::string& s, const std::vector<size_t>& div, int c) {
        encoder my_encoder;
        decoder my_decoder;
        std::string ans;
        size_t sum = 0;
        if (c == 0)
            for (auto v : div) {
                my_encoder.count_frequencies(s.data() + sum, s.data() + sum + v);
                sum += v;
            }
        sum = 0;
        if (c == 0)
            my_encoder.put_dictionary();
        for (auto v : div) {
            if (c == 0)
                ans += my_encoder.encode_text(s.data() + sum, s.data() + sum + v);
            else
                ans += my_decoder.decode_text(s.data() + sum, s.data() + sum + v);
            sum += v;
        }
        if (c == 0)
            ans += my_encoder.encode_end();
        else
            my_decoder.decoder_check_sum();
        return ans;
    }

    std::vector<std::string> get_divisions(const std::string& s, int c) {
        srand(228);
        std::vector<size_t> div;
        std::vector<std::string> code;
        for (size_t i = 1; i <= 10; i++) {
            for (size_t j = 0; j < s.size(); j += i) {
                div.push_back(std::min(s.size() - j, i));
            }
            code.push_back(try_division(s, div, c));
            div.resize(0);
        }
        for (size_t j = 0; j < s.size(); j += 256) {
            div.push_back(std::min(s.size() - j, size_t(256)));
        }
        code.push_back(try_division(s, div, c));
        div.resize(0);
        size_t sum = 0;
        while (sum < s.size()) {
            size_t k = rand() % (s.size() - sum) + 1;
            div.push_back(k);
            sum += k;
        }
        code.push_back(try_division(s, div, c));
        div.resize(0);
        return code;
    }
};

TEST(correctness, empty_string)
{
    std::string s;
    std::vector<std::string> encode = get_divisions(s, 0);
    for (auto v : encode)
        EXPECT_EQ(v, encode[0]);
    std::vector<std::string> decode = get_divisions(encode[0], 1);
    for (auto v : decode)
        EXPECT_EQ(v, s);
}

TEST(correctness, string_with_same_symbols)
{
    for (size_t len = 1; len <= 256; len++) {
        std::string s = "";
        char ch = static_cast<char>((char)rand() % 256);
        for (size_t j = 0; j < len; j++)
            s += ch;
        std::vector<std::string> encode = get_divisions(s, 0);
        for (auto v : encode)
            EXPECT_EQ(v, encode[0]);
        std::vector<std::string> decode = get_divisions(encode[0], 1);
        for (auto v : decode)
            EXPECT_EQ(v, s);
        std::cout << s << "\n";
    }
}
