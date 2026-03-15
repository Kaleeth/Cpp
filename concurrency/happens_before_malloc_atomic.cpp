#include <cstdlib>
#include <thread>
#include <atomic>
#include <iostream>

std::atomic<void*> published = nullptr;

std::size_t allocationBlock = 1024;

void producer()
{
    void *p = std::malloc(allocationBlock);

    // ...

    std::free(p);

    published.store((void*)1);
}

void consumer()
{
    while (published.load() == nullptr) {};

    void* q = malloc(allocationBlock);

    std::cout << q <<"\n";

    std::free(q);
}

int main()
{
    std::thread t1(producer);
    std::thread t2(consumer);
    t1.join(); t2.join();
}
