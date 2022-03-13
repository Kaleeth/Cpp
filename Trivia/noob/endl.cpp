#include <iostream>

void print_range(int start, int end) {
    for (auto i = start; i != end; ++i) 
        std::cout << i << '\n'; // instead of std::endl, because endl also flushes the buffer 
}