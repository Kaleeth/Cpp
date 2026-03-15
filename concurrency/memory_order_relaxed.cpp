#include <atomic>
#include <thread>
#include <iostream>

std::atomic<int> x{0}, y{0};

int main() {
    long long both_zero = 0;
    long long iterations = 1000000;

    for (long long i = 0; i < iterations; ++i) {
        x.store(0, std::memory_order_relaxed);
        y.store(0, std::memory_order_relaxed);

        int r1 = -1, r2 = -1;

        std::thread t1([&] {
            x.store(1, std::memory_order_relaxed);
            r1 = y.load(std::memory_order_relaxed);
        });

        std::thread t2([&] {
            y.store(1, std::memory_order_relaxed);
            r2 = x.load(std::memory_order_relaxed);
        });

        t1.join();
        t2.join();

        if (r1 == 0 && r2 == 0) {
            ++both_zero;
            std::cout << "Both zeros hit" << '\n';
        }
            std::cout << "Is ok" << '\n';
    }

    std::cout << "r1 = 0, r2 = 0 seen " << both_zero << " times\n";
}