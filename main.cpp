#include <iostream>
#include <functional>
#include <fstream>
#include "encoder.h"
#include "decoder.h"
const size_t SIZE = (1 << 20);

void out_help() {
    std::cout << "help: ./archiver (-e | -d) source target" << std::endl;
    exit(0);
}

void my_writer(const std::string &s, std::ofstream& fout) {
    fout.write(s.data(), s.size());
    if (!fout) {
        std::cout << "can't write into file\n";
        exit(0);
    }
}

void my_reader(std::ifstream& fin, const std::function<void(const char*, const char*)>& callback) {
    static char buffer[SIZE];
    while (!fin.eof()) {
        fin.read(buffer, SIZE);
        auto cnt = fin.gcount();
        callback(buffer, buffer + cnt);
        if (!fin.eof() && !fin) {
            std::cout << "can't read from file\n";
            exit(0);
        }
    }
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        out_help();
    }
    auto option = std::string(argv[1]);
    std::ifstream fin{argv[2], std::ifstream::binary};
    if (!fin) {
        std::cout << "can't open input file\n";
        return 0;
    }
    std::ofstream fout(argv[3], std::ofstream::binary);
    if (!fout) {
        std::cout << "can't open output file\n";
        return 0;
    }
    encoder my_encoder;
    if (option == "-e") {
        my_reader(fin, [&my_encoder](const char *begin, const char *end) {
            my_encoder.count_frequencies(begin, end);
        });
        my_encoder.put_dictionary();
        fin.close();
        std::ifstream fin2{argv[2], std::ios::binary};
        my_reader(fin2, [&my_encoder, &fout](const char *begin, const char *end) {
            std::string s = my_encoder.encode_text(begin, end);
            my_writer(s, fout);
        });
        auto ss = my_encoder.encode_end();
        my_writer(ss, fout);
        fin2.close();
    } else if (option == "-d") {
        decoder my_decoder;
        my_reader(fin, [&fout, &my_decoder](const char *begin, const char *end) {
            std::string s = my_decoder.decode_text(begin, end);
            my_writer(s, fout);
        });
        my_decoder.decoder_check_sum();
    } else {
        out_help();
        fin.close();
    }
    fout.close();
    return 0;
}