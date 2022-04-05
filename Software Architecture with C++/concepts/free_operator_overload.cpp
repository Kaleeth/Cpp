#include <iostream>

template<typename T, typename U>
class MyPair {
    friend std::ostream& operator<<(std::ostream& stream, const MyPair<T, U>& mp);
public:
    T first_;
    U second_;
private:
    int secretThird_;
};

std::ostream& operator<<(std::ostream& stream, const MyPair<int, int>& mp) {
    stream << mp.first_ << ", ";
    stream << mp.second_ << ", ";
    stream << mp.secretThird_;
    return stream;
}