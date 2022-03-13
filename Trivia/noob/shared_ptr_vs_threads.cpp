#include <memory>
#include <thread>
#include <iostream>

// it's only the reference count in shared_ptr that's atomic

struct Resource {
    int x{};
};

void worker(std::shared_ptr<Resource> noisy) {
    for (int i = 0; i < 50000; ++i)
        noisy->x++;
}

void shared_ptr_is_NOT_threadsafe() {
    auto r = std::make_shared<Resource>();
    // std::jthread not really supported by gcc yet
    std::thread t1(worker, r);
    std::thread t2(worker, r);
    t1.join();
    t2.join();
    // std::cout << r->x; // not always 50000+50000=100000
    // plain ol' data race, fix with mutex/lock/atomic/etc.
    r.reset();
}

// int main() {
//     shared_ptr_is_NOT_threadsafe();
// }