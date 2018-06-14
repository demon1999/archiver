//
// Created by demon1999 on 05.06.18.
//
#include <set>
#include <iostream>
#include <cassert>
#include <functional>
#include "encoder.h"

void encoder::count_frequencies(const std::string_view &s) {
    if (my_state != counting_freq && my_state != start) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    my_state = counting_freq;

    for (auto i : s) {
        frequencies[(unsigned char) i]++;
    }
}

void encoder::put_dictionary() {
    if (my_state != start && my_state != counting_freq) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    my_state = making_dict;
    my_dictionary.make_dictionary(frequencies);
    for (auto frequencie : frequencies) {
        last_piece.push({frequencie, 64});
    }
}

std::string encoder::full_pieces() {
    std::string ans;
    ans = "";
    while (last_piece.size() >= 8) {
        auto c = last_piece.size();
        ans += last_piece.pop_char();
        assert(c - last_piece.size() == 8);
    }
    return ans;
}

std::string encoder::encode_end() {
    if (my_state != encoding_text && my_state != making_dict) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    my_state = encoding_end;
    size_t pos = 0;
    auto v = my_dictionary.get_symbol(ALPHABET - 1);
    while (last_piece.size() % 8) {
        uint64_t c = 0;
        if (v.binary_code & (1ULL << (v.size_of_code - 1 - pos)))
            c = 1;
        last_piece.push({c, 1});
        pos = (pos + 1) % v.size_of_code;
    }
    auto ans = full_pieces();
    my_dictionary.check_sum();
    return ans;
}

std::string encoder::encode_text(const std::string_view &s) {
    if (my_state != encoding_text && my_state != making_dict) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    my_state = encoding_text;
    for (auto c : s) {
        my_dictionary.plus_(c);
        last_piece.push(my_dictionary.get_symbol((unsigned char) (c)));
    }
    return full_pieces();
}

void encoder::encode_from_files(std::ifstream &fin, std::ofstream &fout) {
    my_stream.my_reader(fin, [this](const std::string_view &s) {
        count_frequencies(s);
    });
    put_dictionary();

    fin.clear();
    fin.seekg(0, std::ios::beg);
    my_stream.my_reader(fin, [this, &fout](const std::string_view &s) {
        std::string t = encode_text(s);
        my_stream.my_writer(t, fout);
    });
    auto ss = encode_end();
    my_stream.my_writer(ss, fout);
}
