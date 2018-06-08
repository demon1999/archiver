//
// Created by demon1999 on 05.06.18.
//

#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include "dictionary.h"
#include "bit_queue.h"

#ifndef ARCHIVER_ARCHIEVER_H
#define ARCHIVER_ARCHIEVER_H

struct encoder {
    static const int ALPHABET = 257;

    encoder() {
        // std::fill
        for (unsigned long long &frequencie : frequencies) {
            frequencie = 0;
        }
        frequencies[ALPHABET - 1] = 1;
    }

    ~encoder() = default;

    void put_dictionary();

    std::string encode_end();

    void count_frequencies(const char *begin, const char *end);

    std::string encode_text(const char *begin, const char *end);

private:
    std::string full_pieces();

    bool has_been[4] = {false, false, false, false};
    unsigned long long frequencies[ALPHABET]{};
    dictionary my_dictionary;
    bit_queue last_piece;
};


#endif //ARCHIVER_ARCHIEVER_H
