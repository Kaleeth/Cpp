#include <vector>
#include <iostream>

void not_always_emplace_back() {
    std::vector<std::vector<int>> vec1, vec2;
    // vec1.push_back(1000000);  // compile error, good!
    vec2.emplace_back(1000000); // but this creates a vector of 1kk elements?
    std::cout << "Vector Size = " << vec2.at(0).size() << std::endl;
    // Vector Size = 1000000

    // also potential memory leakage in case of error for emplace_back, use push_back
    std::vector<std::unique_ptr<int>> v;
    v.push_back(std::make_unique<int>(new int{}));

    // be aware of emplacing raw pointers, emplace unique_ptr so it deletes itself even in case of exception before emplacement
}