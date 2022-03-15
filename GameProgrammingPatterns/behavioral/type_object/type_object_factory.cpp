
class Breed { // type object
public:
    Breed(int health, const char* attack)
    : health_(health), attack_(attack) {}

    Monster* newMonster() { return new Monster(*this); } // factory method

    int getHealth() { return health_; }
    const char* getAttack() { return attack_; }

private:
    int health_; // Starting health.
    const char* attack_;
};

class Monster {
    friend class Breed;
    
public:
    const char* getAttack() { return breed_.getAttack(); }

private:
    Monster(Breed& breed)
    : health_(breed.getHealth()), breed_(breed) {}

    int health_;
    Breed& breed_;
};