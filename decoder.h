//
// Created by demon1999 on 05.06.18.
//

#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include "dictionary.h"
#include "bit_queue.h"

#ifndef ARCHIVER_DECODER_H
#define ARCHIVER_DECODER_H


struct decoder {
    static const int ALPHABET = 257; // it's realy strange size of alphabet
                                     // maybe you want to init your frequencies with (ALPHABET + 1) ?
    static const int LEN = 64;

    decoder() {
        // std::fill
        for (unsigned long long &frequencie : frequencies) {
            frequencie = 0;
        }
        has_all_frequencies = false;
    }

    void decoder_check_sum();

    ~decoder() = default;

    std::string decode_text(const char *begin, const char *end);

private:
    unsigned long long frequencies[ALPHABET];
    bool has_all_frequencies;
    bit_queue last_piece;
    dictionary my_dictionary;
};

#endif //ARCHIVER_DECODER_H
