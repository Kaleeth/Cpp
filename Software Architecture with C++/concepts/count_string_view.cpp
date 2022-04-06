#include <algorithm>
#include <string>

int count_dots(std::string_view str) {
    return std::count(std::begin(str), std::end(str), '.');
}

// advantage of using of string_view over const reference to string is
// string view is a slice of buffer passed by value which avoids additional allocation
// while string being const, having full information on the string