#include <cassert>

class Particle {
public:
    Particle()
    : framesLeft_(0) {}

    void init(double x, double y, double xVel, double yVel, int lifetime) {
        state_.live_.x_ = x; state_.live_.y_ = y;
        state_.live_.xVel_ = xVel; state_.live_.yVel_ = yVel;
        framesLeft_ = lifetime;
    }

    bool animate();

    bool inUse() const { return framesLeft_ > 0; }

    Particle* getNext() const { return state_.next_; }
    void setNext(Particle* next) { state_.next_ = next; }

private:
    int framesLeft_;

    union {
        struct {
            double x_, y_;
            double xVel_, yVel_;
        } live_;
        Particle* next_;
    } state_;
};

bool Particle::animate() {
    if (!inUse()) return false;

    framesLeft_--;
    state_.live_.x_ += state_.live_.xVel_;
    state_.live_.y_ += state_.live_.yVel_;
    return framesLeft_ == 0;
} 

class ParticlePool{
public:
    void create(double x, double y, double xVel, double yVel, int lifetime);
    
    void animate();
    
private:
    static const int POOL_SIZE = 100;
    Particle particles_[POOL_SIZE];
    Particle* firstAvailable_;
};

ParticlePool::ParticlePool()
{
    // The first one is available.
    firstAvailable_ = &particles_[0];
    // Each particle points to the next.
    for (int i = 0; i < POOL_SIZE - 1; i++) {
    particles_[i].setNext(&particles_[i + 1]);
    }
    // The last one terminates the list.
    particles_[POOL_SIZE - 1].setNext(nullptr);
}

void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
    // Make sure the pool isn't full.
    assert(firstAvailable_ != nullptr);

    // Remove it from the available list.
    Particle* newParticle = firstAvailable_;
    firstAvailable_ = newParticle->getNext();
    newParticle->init(x, y, xVel, yVel, lifetime);
}

void ParticlePool::animate() {
    for (int i = 0; i < POOL_SIZE; i++) {
        if (particles_[i].animate()) {
            // Add this particle to the front of the list.
            particles_[i].setNext(firstAvailable_);
            firstAvailable_ = &particles_[i];
        }
    }
}
