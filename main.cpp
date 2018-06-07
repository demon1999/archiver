#include <iostream>
#include <functional>
#include "encoder.h"
#include "decoder.h"
const size_t SIZE = (1 << 20);

void out_help() {
    std::cout << "help: ./archiver (-e | -d) source target" << std::endl;
    exit(0);
}

void my_writer(const std::string &s, FILE * fout) {
    size_t cnt = 0;
    while (cnt < s.size()) {
        cnt += std::fwrite(s.data() + cnt, sizeof s[0], s.size() - cnt, fout);
    }
}

void my_reader(FILE * fin, const std::function<void(const char*, const char*)>& callback) {
    static char buffer[SIZE];
    while (!(std::feof(fin))) {
        auto cnt = std::fread(buffer, sizeof buffer[0], SIZE, fin);
        callback(buffer, buffer + cnt);
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
        my_reader(fin, [&my_encoder](const char *begin, const char *end) {
            my_encoder.count_frequencies(begin, end);
        });
        my_encoder.put_dictionary();
        fclose(fin);
        fin = std::fopen(argv[2], "rb");
        my_reader(fin, [&my_encoder, &fout](const char *begin, const char *end) {
            std::string s = my_encoder.encode_text(begin, end);
            my_writer(s, fout);
        });
        auto ss = my_encoder.encode_end();
        my_writer(ss, fout);
    } else if (option == "-d") {
        decoder my_decoder;
        my_reader(fin, [&fout, &my_decoder](const char *begin, const char *end) {
            std::string s = my_decoder.decode_text(begin, end);
            my_writer(s, fout);
        });
    } else {
        out_help();
    }
    std::fclose(fin);
    std::fclose(fout);
    return 0;
}