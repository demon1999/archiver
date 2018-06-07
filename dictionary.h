//
// Created by demon1999 on 06.06.18.
//

#ifndef ARCHIVER_DICTIONARY_H
#define ARCHIVER_DICTIONARY_H

#include <vector>
#include "symbol_code.h"

struct dictionary {
    static const int ALPHABET = 257, LEN = 64;
    void make_dictionary(unsigned long long frequencies[ALPHABET]);
    symbol_code get_symbol(int c);
    void zero_pos();
    void make_step(bool c);
    bool is_terminal();
    int get_terminal_char();
private:
    void add_vertex();
    void dfs(int nu, unsigned long long s, int szz);
    int pos;
    std::vector<int> term;
    std::vector<bool> is_term;
    std::vector<int> go[2];
    symbol_code huffman_dictionary[ALPHABET];
};
#endif //ARCHIVER_DICTIONARY_H
