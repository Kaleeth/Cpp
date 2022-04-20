// #include <chrono>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <thread>

int main() {
    using namespace std::chrono_literals;
    std::srand(std::time(nullptr));
    // auto start = std::chrono::high_resolution_clock::now();

    while(true) {
        std:: cout << (int) (70 + std::rand() % 36) << std::endl;
        std::this_thread::sleep_for(2000ms);
    }
}
