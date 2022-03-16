#include <iostream>
#include <stdexcept>

class CustomException : public std::exception {
public:
    const char* what() const noexcept {
        return "Custom error detected!";
    }
};

class AdvancedCustomException : public std::exception {
public:
    AdvancedCustomException(const char* msg, const char* file, const int line, const char* func, const char* info)
    : std::exception(msg), file_(file), line_(line), func_(func), info_(info) {}

    const char* what() const noexcept {
        return "Advanced custom error detected!";
    }

    const char* get_file() const { return file_; }
    int get_line() const { return line_; }
    const char* get_func() const { return func_; }
    const char* get_info() const { return info_; }
private:
    const char* file_;
    const int line_;
    const char* func_;
    const char* info_;
};

int main() {
    try {
        throw CustomException();
    } catch (CustomException& e) {
        std::cerr << e.what() << '\n';
    }
}