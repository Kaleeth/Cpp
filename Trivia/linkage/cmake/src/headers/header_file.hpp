#ifndef HEADER_FILE
#define HEADER_FILE

typedef int (*fptr)();
// typedef fptr (*fptrptr)();

inline constexpr int Pi = 3;
const int* get_pi();

constexpr int get_PI() { return 3; }
const fptr get_f();

// constexpr int x = 1;

#endif //HEADER_FILE
