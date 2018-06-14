//
// Created by demon1999 on 05.06.18.
//

#include <cstring>
#include <string>
#include <algorithm>
#include <vector>
#include <fstream>
#include "dictionary.h"
#include "bit_queue.h"
#include "file_lib.h"

#ifndef ARCHIVER_ARCHIEVER_H
#define ARCHIVER_ARCHIEVER_H

struct encoder {
    static const int ALPHABET = 257;
    encoder() {
        std::fill(frequencies, frequencies + ALPHABET, 0);
        frequencies[ALPHABET - 1] = 1;
    }

    ~encoder() = default;
    void encode_from_files(std::ifstream &fin, std::ofstream &fout);

private:
    void put_dictionary();

    std::string encode_end();

    void count_frequencies(const char *begin, const char *end);

    std::string encode_text(const char *begin, const char *end);

    std::string full_pieces();

    enum state {
        start,
        counting_freq,
        making_dict,
        encoding_text,
        encoding_end
    };
    file_lib my_stream;
    state my_state = start;
    unsigned long long frequencies[ALPHABET]{};
    dictionary my_dictionary;
    bit_queue last_piece;
};


#endif //ARCHIVER_ARCHIEVER_H
