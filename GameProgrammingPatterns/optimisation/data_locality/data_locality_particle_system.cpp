#include <cassert>

class Particle {
public:
    void update() { /* Gravity, etc. ... */ }
        // Position, velocity, etc. ...
};

class ParticleSystem {
public:
    ParticleSystem()
    : numParticles_(0), numActive_(0)
    {}

    void update();
    void activateParticle(int index);
    void deactivateParticle(int index);

private:
    static const int MAX_PARTICLES = 100000;
    int numParticles_;
    int numActive_;
    Particle particles_[MAX_PARTICLES];
};

void ParticleSystem::update() {
    for (int i = 0; i < numActive_; i++) {
        particles_[i].update();
    }
}

void ParticleSystem::activateParticle(int index) {
    // Shouldn't already be active!
    assert(index >= numActive_);
    
    // Swap it with the first inactive particle
    // right after the active ones.
    Particle temp = particles_[numActive_];
    particles_[numActive_] = particles_[index];
    particles_[index] = temp;

    // Now there's one more.
    numActive_++;
}

void ParticleSystem::deactivateParticle(int index)
{
    // Shouldn't already be inactive!
    assert(index < numActive_);
    
    // There's one fewer.
    numActive_--;
    
    // Swap it with the last active particle
    // right before the inactive ones.
    Particle temp = particles_[numActive_];
    particles_[numActive_] = particles_[index];
    particles_[index] = temp;
}