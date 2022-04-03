#include <cassert>

#include "header_file.hpp"

int main() {
    assert(&Pi == get_pi());
    assert(Pi == 3);
    
    assert(&get_PI == get_f());
    assert(get_PI() == 3);
}