#include <string>

class Log { public: void write(std::string message); };

class GameObject { 
protected:
    Log& getLog() { return log_; }
private:
    static Log& log_; // for not involving base class too much
    // consider providing an initialization function instead to pass Log in 
    // (or using Service Locator pattern)
};

class Enemy : public GameObject {
    void doSomething() {
        getLog().write("I can log!");
    }
};