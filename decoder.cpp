//
// Created by demon1999 on 05.06.18.
//

#include <set>
#include <iostream>
#include <functional>
#include "decoder.h"

std::string decoder::decode_text(const std::string_view &s) {
    for (char c : s) {
        last_piece.push({static_cast<unsigned long long> ((unsigned char) c), 8});
    }
    if (!has_all_frequencies) {
        if (last_piece.size() < LEN * ALPHABET) return "";
        has_all_frequencies = true;
        for (auto &frequencie : frequencies) {
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
            int ch = my_dictionary.get_terminal_char();
            if (ch < ALPHABET - 1)
                ans += static_cast<char>(ch);
            my_dictionary.zero_pos();
        }
    }
    return ans;
}

void decoder::decoder_check_sum() {
    my_dictionary.check_sum();
}

void decoder::decode_from_files(std::ifstream &fin, std::ofstream &fout) {
    my_stream.my_reader(fin, [&fout, this](const std::string_view &s) {
        std::string t = decode_text(s);
        my_stream.my_writer(t, fout);
    });
    decoder_check_sum();
}

std::string decoder::decode_string(const std::string &s) {
    return my_stream.my_string(s, [this](std::ifstream &fin, std::ofstream &fout) {
        decode_from_files(fin, fout);
    });
}
