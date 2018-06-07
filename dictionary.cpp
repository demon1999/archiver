//
// Created by demon1999 on 06.06.18.
//
#include "dictionary.h"
#include "symbol_code.h"
#include <limits>
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

void dictionary::check_sum() {
    if (my_frequencies.size() != ALPHABET || check_frequencies.size() != ALPHABET) {
        assert(false);
    }
    for (int i = 0; i < ALPHABET - 1; i++) {
        if (my_frequencies[i] != check_frequencies[i]) {
            std::cout << "user data is wrong\n";
            exit(0);
        }
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
    my_frequencies.resize(ALPHABET);
    check_frequencies.assign(ALPHABET, 0);
    std::copy(frequencies, frequencies + ALPHABET, my_frequencies.begin());
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
        if (a.first > std::numeric_limits<unsigned long long>::max() - b.first) {
            std::cout << "bad frequencies\n";
            exit(0);
        }
        a.first += b.first;
        huffman.insert(a);
    }
    dfs(0, 0, 0);
}

symbol_code dictionary::get_symbol(int c) {
    return huffman_dictionary[c];
}

void dictionary::is_bad_pos() {
    if (pos == -1) {
        std::cout << "something wrong while decoding data\n";
        exit(0);
    }
}
void dictionary::zero_pos() {
    pos = 0;
}

void dictionary::make_step(bool c) {
    pos = go[c][pos];
    is_bad_pos();
}

bool dictionary::is_terminal() {
    return is_term[pos];
}

int dictionary::get_terminal_char() {
    if (!is_terminal()) assert(false);
    check_frequencies[term[pos]]++;
    return term[pos];
}
