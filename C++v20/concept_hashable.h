#include <concepts>
#include <unordered_map>

// E.g. concept
template <typename T>
concept arithmetic = std::integral<T> || std::floating_point<T>;
template <typename T>
concept custom_number = arithmetic<T> && sizeof(T) <= 8;

template <typename T>
concept hashable = requires(T t) {
	{ std::hash<T>{}() } -> std::convertible_to<std::size_t>;
};

template <hashable T>
class hash_map;

