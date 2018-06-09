//
// Created by demon1999 on 06.06.18.
//

#include <limits>
#include <iostream>
#include "bit_queue.h"

void bit_queue::push(symbol_code c) {
    if (finish + c.size_of_code < LEN) {
        finish += c.size_of_code;
        if (LEN - finish < 64)
            data.back() |= (c.binary_code << (LEN - finish));
    } else {
        data.back() |= (c.binary_code >> (finish + c.size_of_code - LEN));
        data.push_back(0);
        finish = (finish + c.size_of_code) - LEN;
        if (finish != 0)
            data.back() |= (c.binary_code << (LEN - finish));
    }
}

int bit_queue::size() {
    return static_cast<int>(data.size() * LEN) - start - (LEN - finish);
}


char bit_queue::pop_char() {
    if (start + 8 >= LEN) {
        auto ans = static_cast<char>(((1ULL << (LEN - start)) - 1) & data.front());
        data.pop_front();
        auto cnt = 8 - (LEN - start);
        if (cnt > 0)
            ans = static_cast<char>((ans << cnt) | (data.front() >> (LEN - cnt)));
        start = cnt;
        return ans;
    }
    auto ans = static_cast<char>(data.front() >> (LEN - start - 8));
    start += 8;
    return ans;
}

bool bit_queue::pop_bit() {
    auto ans = (data.front() & (1ULL << (LEN - start - 1))) != 0;
    if (start + 1 >= LEN) {
        data.pop_front();
        start = 0;
        return ans;
    }
    start++;
    return ans;
}

unsigned long long bit_queue::pop_long() {
    auto ans = data.front();
    if (start) {
        ans = data.front() << start;
    }
    data.pop_front();
    if (start) {
        ans |= (data.front() >> (LEN - start));
    }
    return ans;
}
