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
        std::string q = s, t;
        std::ofstream f("test.txt", std::ofstream::binary);
        f.clear();
        f << q;
        f.close();
        std::ifstream fin{"test.txt", std::ifstream::binary};
        std::ofstream fout{"testout.txt", std::ofstream::binary};
        fout.clear();
        my_encoder.encode_from_files(fin, fout);
        fin.close();
        fout.close();
        std::ifstream fin2{"testout.txt", std::ifstream::binary};
        std::ofstream fout2{"test.txt", std::ofstream::binary};
        fout2.clear();
        my_decoder.decode_from_files(fin2, fout2);
        fin2.close();
        fout2.close();
        std::ifstream ff("test.txt", std::ifstream::binary);
        while (getline(ff, q)) {
            t += q;
            t += "\n";
        }
        if (!t.empty())
            t.pop_back();
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