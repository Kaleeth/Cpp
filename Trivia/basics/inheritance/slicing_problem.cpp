// mind you, the best solution is to avoid the issue at all
#include <stdexcept>

// potential solution to slicing problem
class A {
public:
  virtual A& operator= (const A& a) {
    assign(a);
    return *this;
  }

protected:
  void assign(const A& a) {
    // copy members of A from a to this
  }
};

class B : public A {
public:
  virtual B& operator= (const A& a) {
    if (const B* b = dynamic_cast<const B*>(&a))
      assign(*b);
    else
      throw std::logic_error("Could not dynamic_cast argument to declared class.");
    return *this;
  }

  protected:
  void assign(const B& b) {
    A::assign(b); // Let A's assign() copy members of A from b to this
    // copy members of B from b to this
  }
};

int main() {
    // Slicing problem (assuming the solution above is not present)
    // Benign case
    B b;
    A a = b;

    // Treacherous case
    B b1;
    B b2;
    A& a_ref = b1;
    a_ref = b2; // b1 becomes a mix of b1 own members and inherited A members copied from b2 

}