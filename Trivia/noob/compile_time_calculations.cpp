
// name of source file says it all --> constexpr
constexpr int sum_of_1_to_n(const int n) {
    return n * (n + 1) / 2;
}

void uses_sum() {
    const int limit = 1000;
    auto triangle_n = sum_of_1_to_n(limit);
}