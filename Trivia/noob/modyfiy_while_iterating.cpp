#include <iostream>
#include <vector>

void modify_while_iterating() {
    std::vector<int> v{1, 2, 3, 4};

    // for (auto x: v)
    //     v.push_back(x);
    // for (auto it = v.begin(), end = v.end(); it != end; ++it)
    //     v.push_back(*it);
    // PROBLEM: modifying the vector may require it to resize
    // and move all the elements to a new location, thus invalidating the iterator pointers
    const std::size_t size = v.size();
    for (std::size_t i = 0; i < size; ++i)
        v.push_back(v[i]);

    for (auto x: v)
        std::cout << x;
    std::cout << '\n';
}