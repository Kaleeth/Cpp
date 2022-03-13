
void default_vs_value_initialization() {
    // default (garbage) init
    int x;
    int *x2 = new int;

    // value (guaranteed 0) init
    int y{};
    int *y2 = new int{};
    int *y3 = new int();

    // the same for aggregate (like structs) or array types
    // but std::string will get initialized as empty string regardless
    // bc if default constructor is defined, in case of both initialization types it will be called
}