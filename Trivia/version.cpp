#include <iostream>
#include <thread>

int main(int argc, char const *argv[])
{
    // Std C++ version used
    std::cout << __cplusplus << '\n';

    // maximum possible number of concurrent threads
    // std::cout << std::jthread::hardware_concurrency() << '\n';
    return 0;
}
