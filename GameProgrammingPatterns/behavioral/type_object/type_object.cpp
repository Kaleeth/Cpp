
class Breed { // type object
public:
  Breed(int health, const char* attack)
  : health_(health), attack_(attack) {}

  int getHealth() { return health_; }
  const char* getAttack() { return attack_; }

private:
  int health_; // Starting health.
  const char* attack_;
};

class Monster { // typed object
public:
    Monster(Breed& breed)
    : health_(breed.getHealth()), breed_(breed) {}

    const char* getAttack() {
        return breed_.getAttack();
    }

private:
    int health_; // current health
    Breed& breed_;
};