//
// Created by demon1999 on 06.06.18.
//
#include "dictionary.h"
#include "symbol_code.h"
#include <set>
#include <cassert>
#include <iostream>

void dictionary::dfs(int nu, unsigned long long s, int szz) {
    if (is_term[nu]) {
        huffman_dictionary[term[nu]] = {s, szz};
        return;
    }
    for (int j = 0; j < 2; j++)
        if (go[j][nu] != -1) {
            s <<= 1;
            s += j;
            dfs(go[j][nu], s, szz + 1);
            s >>= 1;
        }

}

void dictionary::add_vertex() {
    term.push_back(' ');
    is_term.push_back(false);
    for (auto &j : go)
        j.push_back(-1);
}

void dictionary::make_dictionary(unsigned long long frequencies[ALPHABET]) {
    add_vertex();
    std::set<std::pair<unsigned long long, int> > huffman;
    for (auto j = 0; j < ALPHABET; j++) {
        if (frequencies[j] == 0) continue;
        huffman.insert({frequencies[j], static_cast<int> (term.size())});
        add_vertex();
        is_term.back() = true;
        term.back() = j;
    }
    if (huffman.size() == 1) {
        go[0][0] = 1;
    }
    while (huffman.size() > 1) {
        auto a = (*huffman.begin());
        huffman.erase(huffman.begin());
        auto b = (*huffman.begin());
        huffman.erase(huffman.begin());
        if (huffman.empty()) {
            go[0][0] = a.second;
            go[1][0] = b.second;
            break;
        }
        add_vertex();
        go[0][term.size() - 1] = a.second;
        go[1][term.size() - 1] = b.second;
        a.second = static_cast<int>(term.size() - 1);
        a.first += b.first;
        huffman.insert(a);
    }
    dfs(0, 0, 0);
}

symbol_code dictionary::get_symbol(int c) {
    return huffman_dictionary[c];
}

void dictionary::zero_pos() {
    pos = 0;
}

int dictionary::get_pos() {
    return pos;
}

void dictionary::make_step(bool c) {
    if (pos == -1) return;
    pos = go[c][pos];
}

bool dictionary::is_terminal() {
    if (pos == -1) return false;
    return is_term[pos];
}

int dictionary::get_terminal_char() {
    if (pos == -1 || !is_terminal()) assert(false);
    return term[pos];
}