
int a();
int b();
int c();
int g(int, int, int);

void function_evaluation_order_not_guaranteed() {
    g(a(), b(), c()); // even in C++20
}

// prior to C++17 compiler was allowed to compute any sub-expression in any order 
// e.g. s.replace(0, 4, "").replace(s.find("even"), 4, "only") 
// find function could be computed even before first replace function thus changing the behaviour away from intended