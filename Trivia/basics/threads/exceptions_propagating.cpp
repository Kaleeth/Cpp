#include <future>
#include <stdexcept>
#include <thread>

// void foo(std::exception_ptr& eptr) {
//     try {
//         throw std::runtime_error{"Somethin' ain't well.."};
//     } catch (...) {
//         eptr = std::current_exception();
//     }
// }

void foo() {
    throw std::runtime_error{"Somethin' really ain't well.."};
}

int main() {
    // std::exception_ptr eptr{};
    // std::thread t(foo, std::ref(eptr));

    // try {
    //     // Do stuff...
    // } catch(...) {
    //     t.join();
    //     throw;
    // }
    // t.join();

    // if (eptr)
    //     std::rethrow_exception(eptr);

    std::packaged_task<void()> task{foo};
    auto future = task.get_future();

    std::jthread t{std::move(task)}; // remember to set up std=c++20

    future.get();
}