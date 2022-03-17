#include <algorithm>
#include <iostream>
#include <list>
#include <memory>
#include <stdexcept>
#include <vector>

auto lessThenFive(std::vector<int>& v) {
    return std::none_of(v.begin(), v.end(), [](const int e){ return e<5; });
}

struct Resource  {
    void use(char N) {
        if (N == 'd')
            throw std::logic_error("d prohibited");
    }
};

struct ThrowingObject {
    ~ThrowingObject() noexcept(false) {
        throw std::runtime_error("error in destructor");
    }
};

void foo() {
    throw std::runtime_error("error in foo");
}

int main() {
    std::vector<int> v = {1, 2, 5245, 32, 43};
    std::sort(v.begin(), v.end());
    for (auto n : v) {
        std::cout << n << '\n';
    }
    std::cout << lessThenFive(v) << '\n';

    const std::list<int> list;
    auto& d = list;

    int* arr = new int[10];
    delete [] arr;
    arr = nullptr;
    delete arr;

    try {
        auto rsc = std::make_unique<Resource>();
        rsc->use('d');
    } catch (std::logic_error& e) {
        std::cout << e.what() << '\n';
    }

    try {
        foo(); // if we flip the lines we get a case when noexcept(false) won't help bc of two propagating exceptions
        ThrowingObject t;
    } catch (std::exception& e) {
        std::cout << "std::exception" << '\n';
    }
    //  catch (std::runtime_error& e) {
    //     std::cout << "std::runtime_exception" << '\n';
    // }
}