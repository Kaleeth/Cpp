// since C++11
#include <algorithm>
#include <iostream>
#include <random>

// class RandomNumberBetween { // alternative for randomNumberBetween lambda
// public:
//     RandomNumberBetween(int low, int high)
//     : random_engine_{std::random_device{}()}, distribution_{low, high} {}

//     int operator()() {
//         return distribution_(random_engine_);
//     }
// private:
//     std::mt19937 random_engine_;
//     std::uniform_int_distribution<int> distribution_;
// };

auto randomNumberBetween = [](int low, int high) {
    return [distribution_ = std::uniform_int_distribution<int> (low, high),
            random_engine_ = std::mt19937{ std::random_device{}() }]() mutable {
                return distribution_(random_engine_);
            };
};

namespace ranges
{
   template<typename Range, typename Generator>
   void generate(Range& range, Generator generator) {
       std::generate(begin(range), end(range), generator);
   } 
} // namespace ranges


int main() {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_int_distribution<int> distribution_1_100(1, 100);
    const auto randNum = distribution_1_100(random_engine);
    std::cout << randNum << '\n';

    std::vector<int> vec(10, 1);
    ranges::generate(vec, randomNumberBetween(1, 100));
    for (auto& val : vec)
        std::cout << val << ' ';
    std::cout << '\n';

    std::vector<int> empty_vec;
    empty_vec.reserve(10);
    std::generate_n(std::back_inserter(empty_vec), empty_vec.capacity(), randomNumberBetween(1, 100));
    for (auto& val : empty_vec)
        std::cout << val << ' ';
    std::cout << '\n';

}