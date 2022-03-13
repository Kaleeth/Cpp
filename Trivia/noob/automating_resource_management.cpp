// #include <cstdio>
#include <fstream>

void read_from_a_file(char *name) {
    std::ifstream input{name}; // RAII

    // do stuff..

    // FILE *fp = fopen(name, "r"); // nah
    // fclose(fp); // nah
}