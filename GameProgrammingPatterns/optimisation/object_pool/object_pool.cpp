
class Particle {
public:
    Particle()
    : framesLeft(0) {}

    void init(double x, double y, double xVel, double yVel, int lifetime) {
        state_.live.x = x; state_.live.y = y;
        state_.live.xVel = xVel; state_.live.yVel = yVel;
        state_.live.framesLeft = lifetime;
    }
    void animate() {
        if (!inUse()) return;
        state_.live.framesLeft--;
        state_.live.x += state_.live.xVel;
        state_.live.y += state_.live.yVel;
    }
    bool inUse() const { return state_.live.framesLeft > 0; }

    Particle* getNext() const { return state_.next; }
    void setNext(Particle* next) { state_.next = next; }

private:
    union {
        struct {
            int framesLeft;
            double x, y;
            double xVel, yVel;
        } live;
        Particle* next;
    } state_;
};

class ParticlePool{
public:
    void create(double x, double y, double xVel, double yVel, int lifetime);
    
    void animate() {
        for (int i = 0; i < POOL_SIZE; i++) {
            particles_[i].animate();
        }
    }
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
    particles_[POOL_SIZE - 1].setNext(NULL);
}

void ParticlePool::create(double x, double y, double xVel, double yVel, int lifetime) {
    // Find an available particle.
    for (int i = 0; i < POOL_SIZE; i++) {
        if (!particles_[i].inUse()) {
            particles_[i].init(x, y, xVel, yVel, lifetime);
            return;
        }
    }
}