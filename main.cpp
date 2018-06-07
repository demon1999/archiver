#include <iostream>
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

void for_frequencies(encoder& my_encoder, decoder& my_decoder, const char* begin, const char* end, FILE * fout) {
    my_encoder.count_frequencies(begin, end);
}

void for_encoding(encoder& my_encoder, decoder& my_decoder, const char* begin, const char* end, FILE * fout) {
    std::string s = my_encoder.encode_text(begin, end);
    my_writer(s, fout);
}

void for_decoding(encoder& my_encoder, decoder& my_decoder, const char* begin, const char* end, FILE * fout) {
    std::string s = my_decoder.decode_text(begin, end);
    my_writer(s, fout);
}

void my_reader(FILE * fin, FILE * fout, void (*callback)(encoder&, decoder&, const char*, const char* , FILE *), encoder& my_encoder) {
    static char buffer[SIZE];
    decoder my_decoder;
    while (!(std::feof(fin))) {
        auto cnt = std::fread(buffer, sizeof buffer[0], SIZE, fin);
        callback(my_encoder, my_decoder, buffer, buffer + cnt, fout);
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
        my_reader(fin, fout, for_frequencies, my_encoder);
        my_encoder.put_dictionary();
        fclose(fin);
        fin = std::fopen(argv[2], "rb");
        my_reader(fin, fout, for_encoding, my_encoder);
        auto ss = my_encoder.encode_end();
        my_writer(ss, fout);
    } else if (option == "-d") {
        my_reader(fin, fout, for_decoding, my_encoder);
    } else {
        out_help();
    }
    std::fclose(fin);
    std::fclose(fout);
    return 0;
}