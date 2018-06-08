//
// Created by demon1999 on 05.06.18.
//
#include <set>
#include <iostream>
#include <cassert>
#include "encoder.h"

void encoder::count_frequencies(const char* begin, const char* end) {
    if (has_been[1] || has_been[2] || has_been[3]) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    for (auto i = begin; i != end; i++) {
        frequencies[(unsigned char) (*i)]++;
    }
    has_been[0] = true;
}
void encoder::put_dictionary() {
    if (has_been[2] || has_been[3]) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    my_dictionary.make_dictionary(frequencies);
    for (unsigned long long int frequencie : frequencies) {
        last_piece.push({frequencie, 64});
    }
    has_been[1] = true;
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
};

std::string encoder::encode_end() {
    has_been[3] = true;
    size_t pos = 0;
    auto v = my_dictionary.get_symbol(ALPHABET - 1);
    while (last_piece.size() % 8) {
        unsigned long long c = 0;
        if (v.first & (1ULL << (v.second - 1 - pos)))
            c = 1;
        last_piece.push({c, 1});
        pos = (pos + 1) % v.second;
    }
    auto ans = full_pieces();
    my_dictionary.check_sum();
    return ans;
}

std::string encoder::encode_text(const char* begin, const char* end) {
    if (has_been[3]) {
        std::cout << "wrong order of calls\n";
        exit(0);
    }
    has_been[2] = true;
    for (auto c = begin; c != end; c++) {
        my_dictionary.plus_(*c);
        last_piece.push(my_dictionary.get_symbol((unsigned char)(*c)));
    }
    return full_pieces();
}
