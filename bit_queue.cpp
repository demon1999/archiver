//
// Created by demon1999 on 06.06.18.
//

#include <limits>
#include <iostream>
#include "bit_queue.h"

void bit_queue::push(symbol_code c) {
    if (finish + c.second < LEN) {
        finish += c.second;
        if (LEN - finish < 64)
            data.back() |= (c.first << (LEN - finish));
//        printf("%x %x", data.back(), c.first);
//        std::cout << " " << finish <<  " " << c.second << "\n";
    } else {
        data.back() |= (c.first >> (finish + c.second - LEN));
        data.push_back(0);
        finish = (finish + c.second) - LEN;
        if (finish != 0)
            data.back() |= (c.first << (LEN - finish));
    }
}

int bit_queue::size() {
    return static_cast<int>(data.size() * LEN) - start - (LEN - finish);
}

char bit_queue::pop_char() {
    if (start + 8 >= LEN) {
        auto ans = static_cast<char>(((1 << (LEN - start)) - 1) & data.front());
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