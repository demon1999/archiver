#include <iostream>
#include "encoder.h"
#include "decoder.h"
const size_t SIZE = (1 << 20);
char buffer[SIZE];


void out_help() {
    std::cout << "help: ./archiver (-e | -d) source target" << std::endl;
    exit(0);
}

void my_writer(const std::string &s, FILE * fout) {
    std::fwrite(s.data(), sizeof s[0], s.size(), fout);
}

void my_reader(FILE * fin, FILE * fout, int r, encoder& my_encoder) {
    std::string s;
    decoder my_decoder;
    while (!(std::feof(fin))) {
        auto cnt = std::fread(buffer, sizeof buffer[0], SIZE, fin);
        std::string ss;
        if (r == 0) {
            my_encoder.count_frequencies(buffer, buffer + cnt);
        }
        if (r == 2) {
            ss = my_decoder.decode_text(buffer, buffer + cnt);
        }
        if (r == 1) {
            ss = my_encoder.encode_text(buffer, buffer + cnt);
        }
        if (r > 0) {
            my_writer(ss, fout);
        }
    }
    if (r == 0) {
        my_encoder.put_dictionary();
    }
    if (r == 1) {
        auto ss = my_encoder.encode_end();
        my_writer(ss, fout);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        out_help();
    }
    auto option = std::string(argv[1]);
    FILE* fin = std::fopen(argv[2], "rb");
    FILE* fout = std::fopen(argv[3], "wb");
    encoder my_encoder;
    if (option == "-e") {
        my_reader(fin, fout, 0, my_encoder);
        fclose(fin);
        fin = std::fopen(argv[2], "rb");
        my_reader(fin, fout, 1, my_encoder);
    } else if (option == "-d") {
        my_reader(fin, fout, 2, my_encoder);
    } else {
        out_help();
    }
    std::fclose(fin);
    std::fclose(fout);
    return 0;
}