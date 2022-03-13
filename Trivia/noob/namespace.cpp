#include <iostream>

// using std::cout, std::string, std::endl; // <-- consider specifying the exact names

void using_namespace_std() {
    using namespace std; // better than global

    string s{"hello world"};
    cout << s << endl;

}