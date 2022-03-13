
template<typename T>
void print_bytes(const T &input) {
    // auto *bytes = reinterpret_cast<const std::byte *>(&input); // <-- until C++20
    using bytearray = std::array<std::byte, sizeof(T)>;
    const auto &bytes = std::bit_cast<bytearray, T>(input);

    // Print out bytes one by one...
}