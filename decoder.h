//
// Created by demon1999 on 05.06.18.
//

#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include "dictionary.h"
#include "bit_queue.h"
#include "file_lib.h"

#ifndef ARCHIVER_DECODER_H
#define ARCHIVER_DECODER_H


struct decoder {
    static const int ALPHABET = 257;
    static const int LEN = 64;

    decoder() {
        std::fill(frequencies, frequencies + ALPHABET, 0);
        has_all_frequencies = false;
    }
    void decode_from_files(std::ifstream &fin, std::ofstream &fout);

    ~decoder() = default;

private:
    void decoder_check_sum();
    std::string decode_text(const std::basic_string_view<char> &s);
    unsigned long long frequencies[ALPHABET];
    bool has_all_frequencies;
    file_lib my_stream;
    bit_queue last_piece;
    dictionary my_dictionary;
};

#endif //ARCHIVER_DECODER_H
