#include <csignal>
#include <cassert>
#include <iostream>

volatile sig_atomic_t flag = 0;

void handler(int)
{
    flag = 1;
}

// (fencing) blocking compiler reordering around inline assembly 
// int x = 1;
// std::atomic_signal_fence(std::memory_order_seq_cst);
// asm volatile("" ::: "memory");

int main()
{
    std::signal(SIGINT, handler);


    while(!flag) {
        std::cout << "once";
        std::raise(SIGINT);
    }
    assert(flag == 1);
}