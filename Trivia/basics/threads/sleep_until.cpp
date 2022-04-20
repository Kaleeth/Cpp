#include <chrono>
#include <format> // c++20 + MSVC
#include <iostream>
#include <thread>

auto now() { return std::chrono::steady_clock::now(); }

auto wait_time() {
    using std::chrono::operator""ms;
    // or
    // using namespace std::chrono_literals;
    return now() + 2000ms;
}

int main() {
    std::cout << "Hello, waiter!" << std::endl;
    const auto start{now()};
    std::this_thread::sleep_until(wait_time());
    std::chrono::duration<double, std::milli> elapsed {now() - start};
    std::cout << std::format("Waited {} ms.", elapsed); // use cl /std:latest from msvc for formatting or change
}