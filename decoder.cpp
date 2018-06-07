//
// Created by demon1999 on 05.06.18.
//

#include <set>
#include <iostream>
#include "decoder.h"

std::string decoder::decode_text(const char* begin, const char* end) {
    for (auto c = begin; c != end; c++) {
        last_piece.push({static_cast<unsigned long long> ((unsigned char)(*c)), 8});
    }
    if (!has_all_frequencies) {
        if (last_piece.size() < LEN * ALPHABET) return "";
        has_all_frequencies = true;
        for (unsigned long long &frequencie : frequencies) {
            frequencie = last_piece.pop_long();
        }
        my_dictionary.make_dictionary(frequencies);
        my_dictionary.zero_pos();
    }
    std::string ans;
    ans = "";
    while (last_piece.size()) {
        auto v = last_piece.pop_bit();
        my_dictionary.make_step(v);
        if (my_dictionary.is_terminal()) {
            if (my_dictionary.get_terminal_char() < ALPHABET - 1)
                ans += (char) my_dictionary.get_terminal_char();
            my_dictionary.zero_pos();
        }
    }
    return ans;
}

std::string decoder::decoder_check_sum() {
    my_dictionary.check_sum();
}