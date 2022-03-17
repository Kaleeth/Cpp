#include <future>
#include <iostream>
#include <limits>
#include <stdexcept>

void foo(int c) {
    if (c > std::numeric_limits<char>::max())
        // throw std::invalid_argument("foo argument c too large");
        throw 5;
}

int main() {
    try {
        foo(256);
    } catch (const std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return -1;
    } catch (const std::exception& e) {
        std::cerr << e.what() << "a\n";
        throw; // re-throw the exception
    } catch (...) {
        // what if throw std::string, int or something more obscure
        // this catch may be used for last-resort error logging or special clean-up before terminating
        auto fut = std::async(std::launch::async, [] () { throw std::runtime_error("Async sunk.."); });
        fut.get();
    }
    // ...
    return 0;
}