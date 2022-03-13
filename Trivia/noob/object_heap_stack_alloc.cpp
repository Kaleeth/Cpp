#include <string>
#include <memory>

struct Record {
    int id;
    std::string name;
};

void unnecessary_heap_allocation() {
    // stack allocation is quicker
    Record customer{0, "James"};
    Record other{1, "Someone"};

    // do stuff...
    // no need for destruction
}

void necessary_heap_allocation() {
    // in case the objects are too big, etc.
    // use unique_pointer if the objects are destructed at the end anyway
    auto customer = std::unique_ptr<Record>(new Record{0, "James"});
    auto customer = std::make_unique<Record>(1, "Someone"); // explicit constructor not needed since C++202
    // do stuff...
    // no explicit destruction needed
}

// no need for explicit new and delete anymore
struct SomeResource {};

class Widget {
public:
    Widget() : meta(std::make_unique<SomeResource>()) {
        // init stuff..
    }
private:
    std::unique_ptr<SomeResource> meta;
};