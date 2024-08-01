#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

struct User
{
	std::string name;
	int age;
};

const std::vector<User> users = { {"Sash", 15}, {"Rogger", 21} /* ... */ };

bool underage(const User& user) { return user.age < 18; };

int main()
{
	auto result = users
		| std::views::filter(std::not_fn(underage))
		| std::views::transform([] (const User& user) { return user.age; });
	std::ranges::copy(result, std::ostream_iterator<int>(std::cout, "\n"));
}
