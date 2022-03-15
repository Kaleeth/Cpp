
// dynamic delegation of inheriting potential attributes from parent

class Breed {
public:
    Breed(Breed* parent, int health, const char* attack)
    : parent_(parent), health_(health), attack_(attack) {}

    int getHealth();
    const char* getAttack();

private:
    Breed* parent_;
    int health_; // Starting health.
    const char* attack_;
};

int Breed::getHealth() {
    // Override.
    if (health_ != 0 || parent_ == nullptr) return health_;

    // Inherit.
    return parent_->getHealth();
}
const char* Breed::getAttack() {
    // Override.
    if (attack_ != nullptr || parent_ == nullptr) return attack_;

    // Inherit.
    return parent_->getAttack();
}

// copy-down delegation; at construction time
// if dynamic change of attributes at runtime not predicted

Breed::Breed(Breed* parent, int health, const char* attack)
: health_(health), attack_(attack) {
    // Inherit non-overridden attributes.
    if (parent != nullptr) {
        if (health == 0) health_ = parent->getHealth();
        if (attack == nullptr) attack_ = parent->getAttack();
    }
}