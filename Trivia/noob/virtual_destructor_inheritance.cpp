#include <memory>

class BaseClass {
public:
    virtual void foo() {}
    // If destructor is not virtual, then while using polymorphism with derived class
    // its (appropriate) destructor will not be called, only base class destructor
    virtual ~BaseClass() {}
};

class DerivedClass : public BaseClass {
    ~DerivedClass() override {} // override keyword as matter of practice; explicit
};

void consume_object(std::unique_ptr<BaseClass> p) {
    p->foo();
    // unique_ptr deletes object automatically
};