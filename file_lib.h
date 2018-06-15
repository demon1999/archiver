//
// Created by demon1999 on 14.06.18.
//

#ifndef ARCHIVER_FILE_LIB_H
#define ARCHIVER_FILE_LIB_H


#include <fstream>
#include <functional>
#include <iostream>
#include <string_view>

struct file_lib {
    static const size_t SIZE = (1 << 20);
    void my_writer(const std::string &s, std::ofstream& fout) {
        fout.write(s.data(), s.size());
        if (!fout) {
            std::cout << "can't write into file\n";
            exit(0);
        }
    }

    std::string my_string(const std::string& s, const std::function<void(std::ifstream&, std::ofstream&)>& callback) {
        std::string q, t;
        std::ofstream f("test.txt", std::ofstream::binary);
        f.clear();
        f << s;
        f.close();
        std::ifstream fin{"test.txt", std::ifstream::binary};
        std::ofstream fout{"testout.txt", std::ofstream::binary};
        fout.clear();
        callback(fin, fout);
        fin.close();
        fout.close();
        std::ifstream fin2("testout.txt", std::ifstream::binary);
        while (getline(fin2, q)) {
            t += q;
            t += "\n";
        }
        if (!t.empty())
            t.pop_back();
        return t;
    }

    void my_reader(std::ifstream& fin, const std::function<void(std::string_view)>& callback) {
        static char buffer[SIZE];
        while (!fin.eof()) {
            fin.read(buffer, SIZE);
            auto cnt = fin.gcount();
            callback(std::string_view (buffer, cnt));
            if (!fin.eof() && !fin) {
                std::cout << "can't read from file\n";
                exit(0);
            }
        }
    }
};


#endif //ARCHIVER_FILE_LIB_H
