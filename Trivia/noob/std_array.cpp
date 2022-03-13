#include <cstddef>

template<std::size_t size>
void better_f(std::array<int, size> &arr) {
    
}

void using_c_array() {
    const int n = 256;
    std::array<int, n> arr{};

    better_f(arr);
}