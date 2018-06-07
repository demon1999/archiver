//
// Created by demon1999 on 06.06.18.
//

#ifndef ARCHIVER_BIT_QUEUE_H
#define ARCHIVER_BIT_QUEUE_H

#include <deque>
#include "symbol_code.h"

struct bit_queue {
    const int LEN = 64;
    bit_queue() {
        start = finish = 0;
        data.push_back(0);
    }
    int size();
    char pop_char();
    void push(symbol_code c);
private:
    std::deque<unsigned long long> data;
    int start, finish;
};
#endif //ARCHIVER_BIT_QUEUE_H
