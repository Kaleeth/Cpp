#include "__generator.hpp"
#include <chrono>
#include <iostream>
#include <utility>
#include <ranges>

std::generator<int> fibonacci() {
    int a = 0;
    int b = 1;
    co_yield a;
    while (true) {
        co_yield a = std::exchange(b, a + b);
    }
}

using std::chrono::system_clock;

std::generator<int> GetSequenceGenerator(
	int startValue, size_t numberOfValues)
{
	for (int i { startValue }; i < startValue + numberOfValues; ++i)
	{
		time_t t { system_clock::to_time_t(system_clock::now()) };
		std::cout << std::ctime(&t);
		co_yield i;
	}
}
int main() {
    for (auto const& v: fibonacci() | std::views::take(10)) {
        std::cout << v << ' ';
    }
    std::cout << '\n';

	auto gen {GetSequenceGenerator(10, 5) };
	for (const auto& value : gen)
	{
		std::cout << value << " (Press enter)" << std::endl;
		std::cin.ignore();
	}
}
