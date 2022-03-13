#include <iostream>
#include <unordered_map>

void loop_many_times() {
    std::unordered_map<std::string, std::string> colors = {
        {"RED", "#FF0000"},
        {"GREEN", "#00FF00"},
        {"BLUE", "#0000FF"},
    };

    for(const auto&[name, hex]: colors)
        std::cout << "name: " << name << ", hex: " << hex << '\n';
}

// also..

struct S {
    int a;
    std::string s;
};

S get_S();

void use_S() {
    const auto [a, s] = get_S();
}

// also.. when having multiple outputs from one function

struct Values { // dummy struct
    int x, y;
};

Values
get_values_return_struct(const int n) {
    return {n, n + 1};
}

void use_values() {
    auto [x, y] = get_values_return_struct(2);
}