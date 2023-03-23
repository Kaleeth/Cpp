// Mandatory RVO and Copy Elision for unnamed returns (since C++17)

#include<atomic>
#include<array>

class NoCpMv
{
public:
    NoCpMv() = default;
    NoCpMv(const NoCpMv&) = delete;
    NoCpMv(NoCpMv&&) = delete;
};

void foo(NoCpMv obj) {}

NoCpMv bar()
{
    return NoCpMv{};
}

int main()
{
    foo(NoCpMv{});
    NoCpMv x{bar()};
    foo(bar());
    const NoCpMv& n{bar()}; // temporary materialization (since C++17)


    auto&& a = std::atomic<int>(9); // possible since 17
    auto&& r = std::array{9}; // fast since 17
}
