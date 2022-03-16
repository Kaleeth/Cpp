#include <iostream>
class Base {
public:
    static void baseA() { std::cout << 'A'; }
private:
    static void baseB() { std::cout << 'B'; }
protected:
    static void baseC() { std::cout << 'C'; }
};
class Derived : public Base {
public:
    Derived() {
        // Base::baseB();
        Base::baseC();
    }
};
class Derived2 : private Base {
public:
    Derived2() {
        // Base::baseB();
        Base::baseC();
    }
};
class Derived3 : protected Base {
public:
    Derived3() {
        // Base::baseB();
        Base::baseC();
    }
};
class Derived4 : Base {
public:
    Derived4() {
        // Base::baseB();
        Base::baseC();
    }
};
class DerDerived : public Derived4 {
    DerDerived() {
        // Derived4::baseA();
    }
};

int main() {
    Base::baseA();
    // Base::baseB();
    // Base::baseC();
    Derived::baseA();
    // Derived::baseC();
    // Derived2::baseA();
    // Derived2::baseB();
    // Derived3::baseA();
    // Derived3::baseC();
    // Derived4::baseA();
}