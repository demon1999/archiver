//
// Created by demon1999 on 14.06.18.
//

#ifndef ARCHIVER_FILE_LIB_H
#define ARCHIVER_FILE_LIB_H


#include <fstream>
#include <functional>
#include <iostream>

struct file_lib {
    static const size_t SIZE = (1 << 20);
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
};


#endif //ARCHIVER_FILE_LIB_H
