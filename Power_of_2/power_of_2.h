#include <type_traits>
#include <cmath>

// pre C20: template <typename T, std::enable_if_t<std::is_floating_point_v<T>, void*> = nullptr>
template <typename T> requires std::floating_point<T>
static bool power_of_2(T i) {
	// conflict of signatures: static_assert(std::is_floating_point_v<T>);
	int exponent;
	const T mantissa = std::frexp(i, &exponent);	// decomposes floating point number into mantissa and exponent
	return mantissa == T(0.5);
}

// pre C20: template <typename T, std::enable_if_t<std::is_integral_v<T>, void*> = nullptr>
// template <typename T> requires std::integral<T> // g++ -std=c++20 power_of_2.h
// template <std::integral T>
// static bool power_of_2(T i) {
static bool power_of_2(std::integral auto i) {
	// conflict of signatures: static_assert(std::is_integral_v<T>);
	return i > 0 && (i & (i - 1)) == 0;
}
