#include <iostream>
#include <limits>
#include <stdexcept>

void foo(int c) {
    if (c > std::numeric_limits<char>::max())
        throw std::invalid_argument("foo argument c too large");
}

int main() {
    try {
        foo(256);
    } catch (std::invalid_argument& e) {
        std::cerr << e.what() << '\n';
        return -1;
    }
    // ...
    return 0;
}