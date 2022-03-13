#include <cstdlib>
#include <memory>

// allocated with malloc, must be freed using free

int *some_c_function();

struct FreeDeleter {
    void operator()(void* x) { free(x); }
};

void do_work() {
    auto data = std::unique_ptr<int, FreeDeleter>(some_c_function());
}