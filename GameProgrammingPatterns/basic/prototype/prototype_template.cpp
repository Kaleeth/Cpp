class Monster {
public:
    virtual ~Monster() {}
    // virtual Monster* clone() = 0;
    
    // Other stuff...
};
class Ghost : public Monster {
public:
    Ghost(int health, int speed) : health_(health), speed_(speed) {}
    // virtual Monster* clone() {
    //     return new Ghost(health_, speed_);
    // }
private:
    int health_;
    int speed_;
};

class Spawner { 
public:
    virtual ~Spawner() {}
    virtual Monster* spawnMonster() = 0;
};
template <class T>
class SpawnerFor : public Spawner { 
public:
    Monster* spawnMonster() { return new T(); }
};

int main(int argc, char const *argv[]) {
    Spawner* ghostSpawner = new SpawnerFor<Ghost>();
    return 0;
}