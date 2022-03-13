#include <algorithm>
#include <vector>

void know_your_algorithms() {
    const std::vector<int> data = {-1, -3, -5, 8, 15, -1};

    const auto is_positive = [](const auto &x) { return x > 0; };
    auto first_pos_it 
                    = std::find_if(data.cbegin(), data.cend(), is_positive);
                    // = std::find_if(begin(data), end(data), is_positive);
}