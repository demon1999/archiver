#include <iostream>
#include <functional>
#include "encoder.h"
#include "decoder.h"

void out_help() {
    std::cout << "help: ./archiver (-e | -d) source target" << std::endl;
    exit(0);
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

    if (option == "-e") {
        encoder my_encoder;
        my_encoder.encode_from_files(fin, fout);
    } else if (option == "-d") {
        decoder my_decoder;
        my_decoder.decode_from_files(fin, fout);
    } else {
        out_help();
    }
    return 0;
}