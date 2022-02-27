#include <cassert>

class FileSystem {
public:
    FileSystem() {
        assert(!instantiated_);
        instantiated_ = true;
    }
    ~FileSystem() { instantiated_ = false; }
private:
    static bool instantiated_;
};

bool FileSystem::instantiated_ = false;