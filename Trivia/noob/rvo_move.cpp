#include <vector>

std::vector<int> make_vector(const int n) {
    std::vector v{1, 2, 3, 4};

    // do whatever

    // return std::move(v); // no need to move local vector this bc of RVO
    return v;
}

// implementation of std::move.. it doesn't move
template<typename T>
constexpr std::remove_reference_t<T> &&
move(T &&value) noexcept {
    return static_cast<std::remove_reference_t<T> &&>(value);
}
// int case
// takes an int lvalue reference, static cast it to an rvalue reference and returns it
constexpr int &&
move(int &value) noexcept {
// move(int &&value) noexcept { // rvalue overload
    return static_cast<int &&>(value);
}